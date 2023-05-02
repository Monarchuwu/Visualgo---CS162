#include "StaticArray.h"
#include "SceneNodeHolder.h"

StaticArray::StaticArray(Carrier& carrier)
    : mCarrier(carrier),
      mStaticLength(0),
      mCurrentLength(0),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                4, Constants::pi / 4,
                sf::Vector2f(Constants::CirleNodeRadius * 1.415f + Constants::NodeOutlineThinkness * 2, 0),
                false, Vector<int>(), true) {
}

void StaticArray::updateCarrier() {
    if (mCarrier.mOperationType == Constants::Operation::Init) {
        mStaticLength = mCurrentLength = mCountNode;
    }
    mCarrier.mCountNode = mCurrentLength;
}

Animation StaticArray::applyOperation() {
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

            if (mCurrentLength < mStaticLength && mCarrier.mPos <= mCurrentLength) {
                SceneNode* ptr = find(mCarrier.mPos);
                // it should be find(mCurrentLength) and mTail->mChildren but ok
                SceneNode* mTail = find(mCurrentLength);

                 animation = buildAnimationInsertStaticArray(ptr, mTail,
                                                            sf::Color::Red,
                                                            sf::Color::Red,
                                                            sf::Color::White,
                                                            Constants::OrangeColor,
                                                            Constants::OrangeColor,
                                                            sf::Color::White,
                                                            mCarrier.mVal);
                ++mCurrentLength;
                 updateCarrier();
            }
            return animation;
            break;
        }

        case Constants::Operation::Delete: {
            Animation animation;

            if (mCurrentLength > 0 && mCarrier.mPos < mCurrentLength) {
                 SceneNode* ptr   = find(mCarrier.mPos);
                 SceneNode* mTail = find(mCurrentLength - 1);

                animation = buildAnimationDeleteStaticArray(ptr, mTail,
                                                            sf::Color::Red,
                                                            sf::Color::Red,
                                                            sf::Color::White,
                                                            Constants::OrangeColor,
                                                            Constants::OrangeColor,
                                                            sf::Color::White);
                --mCurrentLength;
                updateCarrier();
            }
            return animation;
            break;
        }

        case Constants::Operation::Update: {
            if (mCountNode == 0) break;

            SceneNode* ptr = find(mCarrier.mPos);
            mStatesHolder  = holdColorAnimationFind(ptr, ptr);

            Animation animation1 = buildAnimationAccess(ptr,
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

        case Constants::Operation::Access: {
            if (mCountNode == 0) break;

            SceneNode* ptr = find(mCarrier.mPos);
            mStatesHolder  = holdColorAnimationFind(ptr, ptr);

            Animation animation = buildAnimationAccess(ptr,
                                                       Constants::OrangeColor,
                                                       Constants::OrangeColor,
                                                       sf::Color::White);
            return animation;
            break;
        }

        case Constants::Operation::Search: {
            SceneNode* ptr = search(mCarrier.mVal);
            mStatesHolder  = holdColorAnimationFind(mHead, ptr);

            return buildAnimationFindWithoutTextBelow(mHead, ptr,
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