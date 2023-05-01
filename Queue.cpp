#include "Queue.h"

#include "SinglyLinkedList.h"

Queue::Queue(Carrier& carrier)
    : mCarrier(carrier),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                30, 0,
                Constants::ShiftNode,
                false, Vector<int>(),
                "Front", "Back") {
}

void Queue::updateCarrier() {
    mCarrier.mCountNode = mCountNode;
}

Animation Queue::applyOperation() {
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

        case Constants::Operation::Add: {
            SceneNode* ptr = find(mCarrier.mPos);

            SceneNode* newPtr    = new SceneNode(BasicNode(mRadiusNode,
                                                           mOutlineThicknessNode,
                                                           mPointCountNode,
                                                           mInitAngleNode,
                                                           mCarrier.mVal),
                                                 mDoubleHeadedArrow,
                                                 false);
            Animation animation = buildAnimationInsert(ptr, mHead, newPtr,
                                                        sf::Color::Red,
                                                        sf::Color::Red,
                                                        sf::Color::White,
                                                        Constants::OrangeColor,
                                                        Constants::OrangeColor,
                                                        sf::Color::White,
                                                        mCarrier.mPos == 0,
                                                        mCarrier.mPos == mCarrier.mCountNode,
                                                        mShiftNode);

            ++mCountNode;
            // no need this because the head position will be update while animation
            // updateHeadPosition();
            updateCarrier();

            return animation;
            break;
        }

        case Constants::Operation::Remove: {
            SceneNode* ptr = find(mCarrier.mPos);

            if (ptr == mTail) return Animation();

            Animation animation = buildAnimationDelete(ptr, mHead,
                                                        sf::Color::Red,
                                                        sf::Color::Red,
                                                        sf::Color::White,
                                                        Constants::OrangeColor,
                                                        Constants::OrangeColor,
                                                        sf::Color::White,
                                                        mCarrier.mPos == 0,
                                                        mCarrier.mPos + 1 == mCarrier.mCountNode,
                                                        mShiftNode);

            --mCountNode;
            // no need this because the head position will be update while animation
            // updateHeadPosition();
            updateCarrier();

            return animation;
            break;
        }

        case Constants::Operation::Clear: {
            updateArray(Vector<int>());
            updateCarrier();

            return Animation();
            break;
        }

        default:
            return Animation();
            break;
    }
}
