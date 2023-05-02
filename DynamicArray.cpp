#include "DynamicArray.h"
#include "SceneNodeHolder.h"

DynamicArray::DynamicArray(Carrier& carrier)
    : mCarrier(carrier),
      mStaticLength(0),
      mCurrentLength(0),
      mHeadBonus(nullptr),
      BasicList(Constants::CirleNodeRadius,
                Constants::NodeOutlineThinkness,
                4, Constants::pi / 4,
                sf::Vector2f(Constants::CirleNodeRadius * 1.415f + Constants::NodeOutlineThinkness * 2, 0),
                false, Vector<int>(), true) {

    Vector<int> arr;
    arr.push_back(0);
    updateArray(arr);
    mCurrentLength = 0;
    updateCarrier();
    sf::Color gray = Constants::GrayColor;
    mHead->mNode.setFillColorBody(gray);
}
DynamicArray::~DynamicArray() { delete mHeadBonus; }

void DynamicArray::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    BasicList::draw(target, states);
    // i cant delete it so... i set the value to -100 instead of delete command
    if (mHeadBonus != nullptr && mHeadBonus->mNode.getValue() != -100) {
        mHeadBonus->drawArrow(target, states);
        mHeadBonus->draw(target, states);
    }
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
            while (arr.size() < sz) {
                arr.push_back(0);
            }
            // update arr and Carrier
            updateArray(arr);
            updateCarrier();

            //// change color of allocate element(s) to gray
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
            if (mCarrier.mPos > mCurrentLength) break;

            Animation animation;

            bool isAllocated = false;
            // Allocate before Insert
            if (mCurrentLength == mStaticLength && mStaticLength > 0) {
                isAllocated = true;

                // Create a copy (SceneNode and Vector<int>)
                std::pair<SceneNode*, int> mCopy = createACopyOfList();
                Vector<int> arr;

                // Double the size
                int sz = mCopy.second * 2;
                for (int i = 0; i < sz; ++i) arr.push_back(0);

                // update arr and Carrier
                updateArray(arr);
                updateCarrier();

                // change color of all element(s) to gray
                SceneNode* ptr = mHead;
                sf::Color gray = Constants::GrayColor;
                while (ptr != nullptr) {
                    ptr->mNode.setFillColorBody(gray);
                    ptr = ptr->mChildren;
                }

                // prep before buildAnimation
                delete mHeadBonus;
                mHeadBonus = mCopy.first;
                if (mHeadBonus != nullptr && mHead != nullptr) {
                    mHeadBonus->setPosition(mHead->getPosition() + sf::Vector2f(0, -Constants::ShiftNode.x));
                }

                animation.add(buildAnimationAllocateDynamicArray(mHead, mHeadBonus,
                                                                 sf::Color::Red,
                                                                 sf::Color::Red,
                                                                 sf::Color::White,
                                                                 Constants::OrangeColor,
                                                                 Constants::OrangeColor,
                                                                 sf::Color::White));
            }
            
            if (mCurrentLength < mStaticLength) { // Insert
                SceneNode* ptr = find(mCarrier.mPos);
                // it should be find(mCurrentLength) and mTail->mChildren but ok
                SceneNode* mTail = find(mCurrentLength);

                if (!isAllocated) {
                    animation.add(buildAnimationInsertStaticArray(ptr, mTail,
                                                                  sf::Color::Red,
                                                                  sf::Color::Red,
                                                                  sf::Color::White,
                                                                  Constants::OrangeColor,
                                                                  Constants::OrangeColor,
                                                                  sf::Color::White,
                                                                  mCarrier.mVal));
                }
                else {
                    SceneNode* mHeadBonusTail = mHeadBonus;
                    while (mHeadBonusTail != nullptr && mHeadBonusTail->mChildren != nullptr) {
                        mHeadBonusTail = mHeadBonusTail->mChildren;
                    }

                    animation.add(buildAnimationInsertStaticArrayAfterAllocate(
                        ptr, mTail, mHeadBonusTail,
                        sf::Color::Red,
                        sf::Color::Red,
                        sf::Color::White,
                        Constants::OrangeColor,
                        Constants::OrangeColor,
                        sf::Color::White,
                        mCarrier.mVal));
                }

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

std::pair<SceneNode*, int> DynamicArray::createACopyOfList() {
    SceneNode *newHead = nullptr, *newTail = nullptr;
    int sz = 0;

    SceneNode* ptr = mHead;
    while (ptr != nullptr) {
        SceneNode* copyPtr = new SceneNode(*ptr);
        copyPtr->mParent   = nullptr;
        copyPtr->mChildren = nullptr;

        if (newTail == nullptr) {
            newHead = newTail = copyPtr;
        }
        else {
            newTail->mChildren = copyPtr;
            copyPtr->mParent   = newTail;
            newTail            = copyPtr;
        }
        ++sz;

        ptr = ptr->mChildren;
    }
    return std::make_pair(newHead, sz);
}
