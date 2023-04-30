#include "BasicList.h"
#include "Arrow.h"
#include "Constants.h"

BasicList::BasicList(Carrier &carrier, Vector<int> arr)
    : mCarrier(carrier),
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
    SceneNode* temp = new SceneNode(BasicNode(Constants::CirleNodeRadius,
                                              Constants::NodeOutlineThinkness,
                                              val));
    temp->setPosition(Constants::ShiftNode);

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
                                    Constants::NodeOutlineThinkness));
    mHead->mNode.setFillColorBody(Constants::ControlTableThemeColor);
    mHead->mNode.setOutlineColor(Constants::ControlTableThemeColor);
    mHead->mNode.setText("Head");

    // Array
    SceneNode* temp = mHead;
    for (int i = 0; i < mArr.size(); ++i) {
        mTail = new SceneNode(BasicNode(Constants::CirleNodeRadius,
                                        Constants::NodeOutlineThinkness,
                                        mArr[i]));
        mTail->setPosition(Constants::ShiftNode);
        temp->attachChild(mTail);
        temp = mTail;
    }

    // NULL (Tail)
    mTail = new SceneNode(BasicNode(Constants::CirleNodeRadius + 10,
                                    Constants::NodeOutlineThinkness));
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
    mHead->move(-(mCnt - 1) * Constants::ShiftNode.x / 2, 0);
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
            insertNodeBefore(ptr, mCarrier.mVal);

            return Animation();
            break;
        }

        case Constants::Operation::Delete: {
            SceneNode* ptr = find(mCarrier.mPos);

            Animation animation = buildAnimationDelete(ptr, mHead,
                                                       sf::Color::Red,
                                                       sf::Color::Red,
                                                       sf::Color::White,
                                                       Constants::OrangeColor,
                                                       Constants::OrangeColor,
                                                       sf::Color::White,
                                                       mCarrier.mPos == 0,
                                                       mCarrier.mPos + 1 == mCarrier.mCountNode);

            --mCountNode;
            // no need this because the head position will be update while animation
            // updateHeadPosition();
            updateCarrier();

            return animation;
            break;
        }

        case Constants::Operation::Update: {
            SceneNode* ptr      = find(mCarrier.mPos);
            mStatesHolder  = holdColorAnimationFind(mHead->mChildren[0], ptr);
            Animation animation1 = buildAnimationFind(mHead->mChildren[0], ptr,
                                                      Constants::OrangeColor,
                                                      Constants::OrangeColor,
                                                      sf::Color::White);
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
