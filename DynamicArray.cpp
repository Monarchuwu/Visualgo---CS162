#include "DynamicArray.h"
#include "SceneNodeHolder.h"

DynamicArray::DynamicArray(Carrier& carrier)
    : mCarrier(carrier),
      mStaticLength(0),
      mCurrentLength(0),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                4, Constants::pi / 4,
                sf::Vector2f(Constants::CirleNodeRadius * 1.415f + Constants::NodeOutlineThinkness * 2, 0),
                false, Vector<int>(), true) {
}

// mCurrentLength must be adjusted manually
void DynamicArray::updateCarrier() {
    if (mCarrier.mOperationType == Constants::Operation::Init
        || (mCarrier.mOperationType == Constants::Operation::Insert
            && mCurrentLength == mStaticLength)) {
        mStaticLength = mCountNode;
    }
    mCarrier.mCountNode = mCurrentLength;
}

Animation DynamicArray::applyOperation() {
    mCarrier.mPlayIsPressed = false;
    while (!mStatesHolder.empty()) {
        mStatesHolder.back().apply();
        mStatesHolder.pop_back();
    }

    switch (mCarrier.mOperationType) {
        case Constants::Operation::Init: {
            // Get arr data
            Vector<int> arr = mCarrier.mArr;
            mCurrentLength  = arr.size();

            // allocate size to 2^x
            int sz = 1;
            while (sz < arr.size()) sz <<= 1;
            while (arr.size() < sz) arr.push_back(0);

            // update arr and Carrier
            updateArray(arr);
            updateCarrier();

            // change color of allocate element(s) to gray
            SceneNode* ptr = find(mCurrentLength);
            sf::Color gray = Constants::GrayColor;
            while (ptr != nullptr) {
                ptr->mNode.setFillColorBody(gray);
                ptr = ptr->mChildren;
            }

            return Animation();
            break;
        }

        case Constants::Operation::Insert: {
            Animation animation;

            //if (mCurrentLength < mStaticLength && mCarrier.mPos <= mCurrentLength) {
            //    SceneNode* ptr = find(mCarrier.mPos);
            //    // it should be find(mCurrentLength) and mTail->mChildren but ok
            //    SceneNode* mTail = find(mCurrentLength);

            //    animation = buildAnimationInsertStaticArray(ptr, mTail,
            //                                                sf::Color::Red,
            //                                                sf::Color::Red,
            //                                                sf::Color::White,
            //                                                Constants::OrangeColor,
            //                                                Constants::OrangeColor,
            //                                                sf::Color::White,
            //                                                mCarrier.mVal);
            //    ++mCurrentLength;
            //    updateCarrier();
            //}
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
            if (mCurrentLength == 0) break;

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
            if (mCurrentLength == 0) break;

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
            if (mCurrentLength == 0) break;

            SceneNode* ptr = search(mCarrier.mVal);
            SceneNode* mTail = find(mCurrentLength - 1);
            mStatesHolder  = holdColorAnimationFind(mHead, ptr);

            return buildAnimationFindWithoutTextBelow(mHead, ptr, mTail,
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
