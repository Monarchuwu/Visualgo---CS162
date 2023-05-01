#include "BasicList.h"
#include "Arrow.h"
#include "Constants.h"
#include "SceneNodeHolder.h"

BasicList::BasicList(float radiusNode,
                     float outlineThickness,
                     size_t pointCount,
                     float initAngle,
                     sf::Vector2f shiftNode,
                     Carrier& carrier,
                     Vector<int> arr)
    : mRadiusNode(radiusNode),
      mOutlineThicknessNode(outlineThickness),
      mPointCountNode(pointCount),
      mInitAngleNode(initAngle),
      mShiftNode(shiftNode),
      mCarrier(carrier),
      mArr(arr),
      mCountNode(arr.size()),
      mHead(nullptr),
      mTail(nullptr) {
    updateArray();
}

size_t BasicList::getCountNode() const { return mArr.size(); }
SceneNode* BasicList::find(const size_t index) const {
    return internalFind(index);
}
void BasicList::insertNodeBefore(SceneNode* ptr, int val) {
    SceneNode* temp = new SceneNode(BasicNode(mRadiusNode,
                                              mOutlineThicknessNode,
                                              mPointCountNode,
                                              mInitAngleNode,
                                              val));
    temp->setPosition(mShiftNode);

    SceneNode* parent = ptr->mParent;
    ptr               = parent->detachChild(*ptr);
    
    parent->attachChild(temp);
    temp->attachChild(ptr);

    ++mCountNode;
    updateHeadPosition();
    updateCarrier();
}
void BasicList::deleteNode(SceneNode* ptr) {
    SceneNode* parent = ptr->mParent;
    SceneNode* child  = ptr->mChildren[0];

    parent->detachChild(*ptr);
    ptr->detachChild(*child);

    delete ptr;
    parent->attachChild(child);

    --mCountNode;
    updateHeadPosition();
    updateCarrier();
}

SceneNode* BasicList::search(const int val) const {
    return internalSearch(val);
}
SceneNode* BasicList::internalFind(const size_t index) const {
    SceneNode* ptr = mHead->mChildren[0];
    size_t pos     = 0;

    while (ptr != mTail && pos < index) {
        ptr = ptr->mChildren[0];
        ++pos;
    }
    return ptr;
}
SceneNode* BasicList::internalSearch(const int val) const {
    SceneNode* ptr = mHead->mChildren[0];
    while (ptr != mTail) {
        if (ptr->mNode.getValue() == val) break;
        ptr = ptr->mChildren[0];
    }
    return ptr;
}

void BasicList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    mHead->drawArrow(target, states);
    mHead->draw(target, states);
}
void BasicList::updateArray(Vector<int> arr) {
    mArr       = arr;
    mCountNode = arr.size();
    updateArray();
}

void BasicList::clear() {
    if (mHead) {
        delete mHead;
        mHead = mTail = nullptr;
    }
}
void BasicList::updateArray() {
    clear();

    // Head
    mHead = new SceneNode(BasicNode(Constants::CirleNodeRadius + 10,
                                    Constants::NodeOutlineThinkness,
                                    30, 0));
    mHead->mNode.setFillColorBody(Constants::ControlTableThemeColor);
    mHead->mNode.setOutlineColor(Constants::ControlTableThemeColor);
    mHead->mNode.setText("Head");

    // Array
    SceneNode* temp = mHead;
    for (int i = 0; i < mArr.size(); ++i) {
        mTail = new SceneNode(BasicNode(mRadiusNode,
                                        mOutlineThicknessNode,
                                        mPointCountNode,
                                        mInitAngleNode,
                                        mArr[i]));
        mTail->setPosition(i == 0 ? Constants::ShiftNode : mShiftNode);
        temp->attachChild(mTail);
        temp = mTail;
    }

    // NULL (Tail)
    mTail = new SceneNode(BasicNode(Constants::CirleNodeRadius + 10,
                                    Constants::NodeOutlineThinkness,
                                    30, 0));
    mTail->mNode.setFillColorBody(Constants::ControlTableThemeColor);
    mTail->mNode.setOutlineColor(Constants::ControlTableThemeColor);
    mTail->mNode.setText("NULL");
    mTail->setPosition(Constants::ShiftNode);
    temp->attachChild(mTail);

    updateHeadPosition();
    updateCarrier();
}
void BasicList::updateHeadPosition() {
    int mCnt = mCountNode + 2;
    mHead->setPosition(Constants::MidPointSceneVisual);
    int x = 0, y = 0;
    if (mCountNode == 0) {
        x = -Constants::ShiftNode.x / 2;
        y = -Constants::ShiftNode.y / 2;
    }
    else if (mCountNode == 1) {
        x = -Constants::ShiftNode.x;
        y = -Constants::ShiftNode.y;
    }
    else {
        x = -(Constants::ShiftNode.x + (mCnt - 1) * mShiftNode.x / 2);
        y = -(Constants::ShiftNode.y + (mCnt - 1) * mShiftNode.y / 2);
    }
    mHead->move(x, y);
}
void BasicList::updateCarrier() {
    mCarrier.mCountNode = mCountNode;
}

Animation BasicList::applyOperation() {
    mCarrier.mPlayIsPressed = false;
    while (!mStatesHolder.empty()) {
        mStatesHolder.back().apply();
        mStatesHolder.pop_back();
    }

    switch (mCarrier.mOperationType) {
        case Constants::Operation::Init: {
            updateArray(mCarrier.mArr);
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
            SceneNode* ptr      = find(mCarrier.mPos);
            mStatesHolder  = holdColorAnimationFind(mHead->mChildren[0], ptr);
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
}
