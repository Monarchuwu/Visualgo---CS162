#include "Queue.h"
#include "SceneNodeHolder.h"

Queue::Queue(Carrier& carrier)
    : mCarrier(carrier),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                30, 0,
                Constants::ShiftNode,
                false, Vector<int>()) {
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
            Animation animation;
            if (mCountNode == 0) { // Just Insert = Init 1 element
                Vector<int> arr;
                arr.push_back(mCarrier.mVal);
                updateArray(arr);
                updateCarrier();
            }
            else { // Insert At End
                SceneNode* mTail = find(mCarrier.mPos - 1);

                SceneNode* newPtr = new SceneNode(BasicNode(mRadiusNode,
                                                            mOutlineThicknessNode,
                                                            mPointCountNode,
                                                            mInitAngleNode,
                                                            mCarrier.mVal),
                                                  mDoubleHeadedArrow,
                                                  false);

                animation = buildAnimationInsertAtEnd(mHead, mTail, newPtr,
                                                      sf::Color::Red,
                                                      sf::Color::Red,
                                                      sf::Color::White,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White,
                                                      mShiftNode);

                ++mCountNode;
                // no need this because the head position will be update while animation
                // updateHeadPosition();
                updateCarrier();
            }
            return animation;
            break;
        }

        case Constants::Operation::Remove: {
            Animation animation;
            if (mCountNode == 0) break;
            if (mCountNode == 1) { // Just Delete = Init empty
                updateArray(Vector<int>());
                updateCarrier();
            }
            else { // Delete At Beginning
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
            return animation;
            break;
        }

        case Constants::Operation::Clear: {
            Animation animation = buildAnimationClearFromBeginning(mHead);

            mCountNode = 0;
            updateCarrier();
            return animation;
            break;
        }

        default:
            return Animation();
            break;
    }
    return Animation();
}
