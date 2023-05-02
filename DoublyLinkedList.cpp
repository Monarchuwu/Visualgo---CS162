#include "DoublyLinkedList.h"
#include "SceneNodeHolder.h"

DoublyLinkedList::DoublyLinkedList(Carrier& carrier)
    : mCarrier(carrier),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                30, 0,
                Constants::ShiftNode,
                true, Vector<int>()) {
}

void DoublyLinkedList::updateCarrier() {
    mCarrier.mCountNode = mCountNode;
}

Animation DoublyLinkedList::applyOperation() {
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