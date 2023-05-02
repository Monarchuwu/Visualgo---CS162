#include "CircularLinkedList.h"
#include "SceneNodeHolder.h"
#include "Arrow.h"

CircularLinkedList::CircularLinkedList(Carrier& carrier)
    : mCarrier(carrier),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                30, 0,
                Constants::ShiftNode,
                false, Vector<int>()) {
}

void CircularLinkedList::updateCarrier() {
    mCarrier.mCountNode = mCountNode;
}

void CircularLinkedList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (mHead == nullptr) return;

    { // draw a Rectangle Arrow
        /*
            ____3____
           |         |
          4|         |2
           `-->   ---'
             5     1
        */
        sf::Vector2f src = mHead->getPosition();
        sf::Vector2f dest;
        SceneNode* ptr = mHead;
        while (ptr != nullptr) {
            dest += ptr->getPosition();
            ptr = ptr->mChildren;
        }
        float thickness = Constants::NodeOutlineThinkness;

        sf::RectangleShape rect1(sf::Vector2f(mShiftNode.x, thickness));
        rect1.setFillColor(sf::Color::Black);
        rect1.setOrigin(0.f, thickness / 2);
        rect1.setPosition(dest);
        target.draw(rect1);

        sf::RectangleShape rect2(sf::Vector2f(mShiftNode.x, thickness));
        rect2.setFillColor(sf::Color::Black);
        rect2.setOrigin(0.f, thickness / 2);
        rect2.setPosition(dest + sf::Vector2f(mShiftNode.x, 0));
        rect2.setRotation(-90);
        target.draw(rect2);

        sf::RectangleShape rect3(sf::Vector2f(dest.x - src.x + mShiftNode.x * 2, thickness));
        rect3.setFillColor(sf::Color::Black);
        rect3.setOrigin(0.f, thickness / 2);
        rect3.setPosition(src + sf::Vector2f(-mShiftNode.x, -mShiftNode.x));
        target.draw(rect3);

        sf::RectangleShape rect4(sf::Vector2f(mShiftNode.x, thickness));
        rect4.setFillColor(sf::Color::Black);
        rect4.setOrigin(0.f, thickness / 2);
        rect4.setPosition(src - sf::Vector2f(mShiftNode.x, 0));
        rect4.setRotation(-90);
        target.draw(rect4);

        drawArrow2Point(src + sf::Vector2f(-mShiftNode.x, 0),
                        src + sf::Vector2f(-mRadiusNode - mOutlineThicknessNode, 0),
                        target);
    }

    BasicList::draw(target, states);
}

Animation CircularLinkedList::applyOperation() {
    mCarrier.mPlayIsPressed = false;
    while (!mStatesHolder.empty()) {
        mStatesHolder.back().apply();
        mStatesHolder.pop_back();
    }

    switch (mCarrier.mOperationType) {
        case Constants::Operation::Init: {
            updateArray(mCarrier.mArr);
            updateCarrier();
            return Animation();
            break;
        }

        case Constants::Operation::Insert: {
            Animation animation;
            if (mCountNode == 0) { // Just Insert = Init 1 element
                Vector<int> arr;
                arr.push_back(mCarrier.mVal);
                updateArray(arr);
                updateCarrier();
            }
            else if (mCarrier.mPos == 0) { // Insert At Beginning
                SceneNodeHolder::Holder31 = &mHead;
                SceneNode* newPtr         = new SceneNode(BasicNode(mRadiusNode,
                                                                    mOutlineThicknessNode,
                                                                    mPointCountNode,
                                                                    mInitAngleNode,
                                                                    mCarrier.mVal),
                                                          mDoubleHeadedArrow);

                animation = buildAnimationInsertAtBeginning(mHead, newPtr,
                                                            sf::Color::Red,
                                                            sf::Color::Red,
                                                            sf::Color::White,
                                                            Constants::OrangeColor,
                                                            Constants::OrangeColor,
                                                            sf::Color::White,
                                                            mShiftNode,
                                                            mHead->getPosition());

                ++mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            else if (mCarrier.mPos == mCountNode) { // Insert At End
                SceneNode* mTail = find(mCarrier.mPos - 1);

                mStatesHolder        = holdColorAnimationFind(mHead, mTail);
                Animation animation1 = buildAnimationFind(mHead, mTail,
                                                          Constants::OrangeColor,
                                                          Constants::OrangeColor,
                                                          sf::Color::White);
                if (mTail == nullptr) return animation1;

                SceneNode* newPtr    = new SceneNode(BasicNode(mRadiusNode,
                                                               mOutlineThicknessNode,
                                                               mPointCountNode,
                                                               mInitAngleNode,
                                                               mCarrier.mVal),
                                                     mDoubleHeadedArrow,
                                                     false);
                Animation animation2 = buildAnimationInsertAtEnd(mHead, mTail, newPtr,
                                                                 sf::Color::Red,
                                                                 sf::Color::Red,
                                                                 sf::Color::White,
                                                                 Constants::OrangeColor,
                                                                 Constants::OrangeColor,
                                                                 sf::Color::White,
                                                                 mShiftNode);

                animation.add(animation1);
                animation.add(animation2);

                ++mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            else { // Insert At Middle
                SceneNode* ptr = find(mCarrier.mPos - 1);

                mStatesHolder        = holdColorAnimationFind(mHead, ptr);
                Animation animation1 = buildAnimationFind(mHead, ptr,
                                                          Constants::OrangeColor,
                                                          Constants::OrangeColor,
                                                          sf::Color::White);
                if (ptr == nullptr) return animation1;

                SceneNode* newPtr    = new SceneNode(BasicNode(mRadiusNode,
                                                               mOutlineThicknessNode,
                                                               mPointCountNode,
                                                               mInitAngleNode,
                                                               mCarrier.mVal),
                                                     mDoubleHeadedArrow,
                                                     false);
                Animation animation2 = buildAnimationInsertAtMiddle(ptr, mHead, newPtr,
                                                                    sf::Color::Red,
                                                                    sf::Color::Red,
                                                                    sf::Color::White,
                                                                    Constants::OrangeColor,
                                                                    Constants::OrangeColor,
                                                                    sf::Color::White,
                                                                    mShiftNode);

                animation.add(animation1);
                animation.add(animation2);

                ++mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            return animation;
            break;
        }

        case Constants::Operation::Delete: {
            Animation animation;
            if (mCountNode == 0) break;
            if (mCountNode == 1) { // Just Delete = Init empty
                updateArray(Vector<int>());
                updateCarrier();
            }
            else if (mCarrier.mPos == 0) { // Delete At Beginning
                SceneNodeHolder::Holder21 = &mHead;

                animation = buildAnimationDeleteAtBeginning(mHead,
                                                            sf::Color::Red,
                                                            sf::Color::Red,
                                                            sf::Color::White,
                                                            Constants::OrangeColor,
                                                            Constants::OrangeColor,
                                                            sf::Color::White,
                                                            mShiftNode,
                                                            mHead->getPosition());

                --mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            else if (mCarrier.mPos == mCountNode - 1) { // Delete At End
                SceneNode* ptr = find(mCountNode - 2);

                mStatesHolder        = holdColorAnimationFind(mHead, ptr);
                Animation animation1 = buildAnimationFind(mHead, ptr,
                                                          Constants::OrangeColor,
                                                          Constants::OrangeColor,
                                                          sf::Color::White);
                if (ptr == nullptr) return animation1;
                animation.add(animation1);

                Animation animation2 = buildAnimationDeleteAtEnd(ptr->mChildren, mHead,
                                                                 sf::Color::Red,
                                                                 sf::Color::Red,
                                                                 sf::Color::White,
                                                                 Constants::OrangeColor,
                                                                 Constants::OrangeColor,
                                                                 sf::Color::White,
                                                                 mShiftNode);
                animation.add(animation2);

                --mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            else { // Delete At Middle
                SceneNode* ptr = find(mCarrier.mPos - 1);

                mStatesHolder        = holdColorAnimationFind(mHead, ptr);
                Animation animation1 = buildAnimationFind(mHead, ptr,
                                                          Constants::OrangeColor,
                                                          Constants::OrangeColor,
                                                          sf::Color::White);
                if (ptr == nullptr) return animation1;
                animation.add(animation1);

                Animation animation2 = buildAnimationDeleteAtMiddle(ptr, mHead,
                                                                    sf::Color::Red,
                                                                    sf::Color::Red,
                                                                    sf::Color::White,
                                                                    Constants::OrangeColor,
                                                                    Constants::OrangeColor,
                                                                    sf::Color::White,
                                                                    mShiftNode);
                animation.add(animation2);

                --mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            return animation;
            break;
        }

        case Constants::Operation::Update: {
            SceneNode* ptr       = find(mCarrier.mPos);
            mStatesHolder        = holdColorAnimationFind(mHead, ptr);
            Animation animation1 = buildAnimationFind(mHead, ptr,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White);
            if (ptr == nullptr) return animation1;

            Animation animation2 = buildAnimationUpdate(ptr,
                                                        mCarrier.mVal,
                                                        sf::Color::Red,
                                                        sf::Color::Red,
                                                        sf::Color::White);
            animation1.add(animation2);
            return animation1;
            break;
        }

        case Constants::Operation::Search: {
            SceneNode* ptr = search(mCarrier.mVal);
            mStatesHolder  = holdColorAnimationFind(mHead, ptr);
            return buildAnimationFind(mHead, ptr,
                                      Constants::OrangeColor,
                                      Constants::OrangeColor,
                                      sf::Color::White);
            break;
        }

        default:
            return Animation();
            break;
    }
    return Animation();
}