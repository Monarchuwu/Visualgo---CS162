#include "BasicList.h"
#include "Arrow.h"
#include "Constants.h"
#include "SceneNodeHolder.h"

BasicList::BasicList(float radiusNode,
                     float outlineThickness,
                     size_t pointCount,
                     float initAngle,
                     sf::Vector2f shiftNode,
                     bool doubleHeadedArrow,
                     Vector<int> arr,
                     bool numberArrayElements)
    : mRadiusNode(radiusNode),
      mOutlineThicknessNode(outlineThickness),
      mPointCountNode(pointCount),
      mInitAngleNode(initAngle),
      mShiftNode(shiftNode),
      mDoubleHeadedArrow(doubleHeadedArrow),
      mArr(arr),
      mCountNode(arr.size()),
      mNumberArray(numberArrayElements),
      mHead(nullptr) {
    updateArray();
}

size_t BasicList::getCountNode() const { return mArr.size(); }
SceneNode* BasicList::find(const size_t index) const {
    return internalFind(index);
}

SceneNode* BasicList::search(const int val) const {
    return internalSearch(val);
}
SceneNode* BasicList::internalFind(const size_t index) const {
    SceneNode* ptr = mHead;
    size_t pos     = 0;

    while (ptr != nullptr && pos < index) {
        ++pos;
        ptr = ptr->mChildren;
    }
    return ptr;
}
SceneNode* BasicList::internalSearch(const int val) const {
    SceneNode* ptr = mHead;

    while (ptr != nullptr) {
        if (ptr->mNode.getValue() == val) break;
        ptr = ptr->mChildren;
    }
    return ptr;
}

void BasicList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (mHead == nullptr) return;
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
        mHead = nullptr;
    }
}
void BasicList::clearTextBelow() {
    SceneNode* cur = mHead;
    while (cur != nullptr) {
        cur->mNode.setTextBelow("");
        cur = cur->mChildren;
    }
}
void BasicList::updateArray() {
    clear();

    // Array
    SceneNode* cur = mHead;
    for (int i = 0; i < mArr.size(); ++i) {
        SceneNode* tmp = new SceneNode(BasicNode(mRadiusNode,
                                                 mOutlineThicknessNode,
                                                 mPointCountNode,
                                                 mInitAngleNode,
                                                 mArr[i]),
                                       mDoubleHeadedArrow);
        tmp->setPosition(mShiftNode);
        if (cur == nullptr) {
            mHead = cur = tmp;
        }
        else {
            cur->attachChild(tmp);
            cur = tmp;
        }
    }

    updateHeadPosition();
}
void BasicList::updateHeadPosition() {
    if (mHead == nullptr) return;

    mHead->setPosition(Constants::MidPointSceneVisual);
    int x = -((mCountNode - 1) * mShiftNode.x / 2);
    int y = -((mCountNode - 1) * mShiftNode.y / 2);
    mHead->move(x, y);

    updateTextBelow();
}
void BasicList::updateTextBelow() {
    if (mHead == nullptr) return;
    clearTextBelow();

    if (!mNumberArray) {
        mHead->mNode.setTextBelow("Head/");
        SceneNode* mTail = find(mCountNode - 1);
        mTail->mNode.setTextBelow(mTail->mNode.getTextBelow() + "Tail/");
    }
    else {
        int pos = 0;
        SceneNode* ptr = mHead;
        while (ptr != nullptr) {
            ptr->mNode.setTextBelow(std::to_string(pos) + "/");
            ptr = ptr->mChildren;
            ++pos;
        }
    }
}