#include "DoublyLinkedList.h"

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
    /*
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
            SceneNode* ptr = find(mCarrier.mPos);

            mStatesHolder        = holdColorAnimationFind(mHead->mChildren[0], ptr);
            Animation animation1 = buildAnimationFind(mHead->mChildren[0], ptr,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White);

            SceneNode* newPtr    = new SceneNode(BasicNode(mRadiusNode,
                                                           mOutlineThicknessNode,
                                                           mPointCountNode,
                                                           mInitAngleNode,
                                                           mCarrier.mVal),
                                                 mDoubleHeadedArrow,
                                                 false);
            Animation animation2 = buildAnimationInsert(ptr, mHead, newPtr,
                                                        sf::Color::Red,
                                                        sf::Color::Red,
                                                        sf::Color::White,
                                                        Constants::OrangeColor,
                                                        Constants::OrangeColor,
                                                        sf::Color::White,
                                                        mCarrier.mPos == 0,
                                                        mCarrier.mPos == mCarrier.mCountNode,
                                                        mShiftNode);

            animation1.add(animation2);

            ++mCountNode;
            // no need this because the head position will be update while animation
            // updateHeadPosition();
            updateCarrier();

            return animation1;
            break;
        }

        case Constants::Operation::Delete: {
            SceneNode* ptr = find(mCarrier.mPos);

            mStatesHolder        = holdColorAnimationFind(mHead->mChildren[0], ptr);
            Animation animation1 = buildAnimationFind(mHead->mChildren[0], ptr,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White);

            if (ptr == mTail) return animation1;

            Animation animation2 = buildAnimationDelete(ptr, mHead,
                                                        sf::Color::Red,
                                                        sf::Color::Red,
                                                        sf::Color::White,
                                                        Constants::OrangeColor,
                                                        Constants::OrangeColor,
                                                        sf::Color::White,
                                                        mCarrier.mPos == 0,
                                                        mCarrier.mPos + 1 == mCarrier.mCountNode,
                                                        mShiftNode);

            animation1.add(animation2);

            --mCountNode;
            // no need this because the head position will be update while animation
            // updateHeadPosition();
            updateCarrier();

            return animation1;
            break;
        }

        case Constants::Operation::Update: {
            SceneNode* ptr       = find(mCarrier.mPos);
            mStatesHolder        = holdColorAnimationFind(mHead->mChildren[0], ptr);
            Animation animation1 = buildAnimationFind(mHead->mChildren[0], ptr,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White);

            if (ptr == mTail) return animation1;

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
            mStatesHolder  = holdColorAnimationFind(mHead->mChildren[0], ptr);
            return buildAnimationFind(mHead->mChildren[0], ptr,
                                      Constants::OrangeColor,
                                      Constants::OrangeColor,
                                      sf::Color::White);
            break;
        }

        default:
            return Animation();
            break;
    }
    */
    return Animation();
}
