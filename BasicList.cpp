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
    std::string nameHead,
    std::string nameTail)
    : mRadiusNode(radiusNode),
      mOutlineThicknessNode(outlineThickness),
      mPointCountNode(pointCount),
      mInitAngleNode(initAngle),
      mShiftNode(shiftNode),
      mDoubleHeadedArrow(doubleHeadedArrow),
      mArr(arr),
      mCountNode(arr.size()),
      mNameHead(nameHead),
      mNameTail(nameTail),
      mHead(nullptr),
      mTail(nullptr) {
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
                                    30, 0),
                          mDoubleHeadedArrow);
    mHead->mNode.setFillColorBody(Constants::ControlTableThemeColor);
    mHead->mNode.setOutlineColor(Constants::ControlTableThemeColor);
    mHead->mNode.setText(mNameHead);

    // Array
    SceneNode* temp = mHead;
    for (int i = 0; i < mArr.size(); ++i) {
        mTail = new SceneNode(BasicNode(mRadiusNode,
                                        mOutlineThicknessNode,
                                        mPointCountNode,
                                        mInitAngleNode,
                                        mArr[i]),
                              mDoubleHeadedArrow && i != 0);
        mTail->setPosition(i == 0 ? Constants::ShiftNode : mShiftNode);
        temp->attachChild(mTail);
        temp = mTail;
    }

    // NULL (Tail)
    mTail = new SceneNode(BasicNode(Constants::CirleNodeRadius + 10,
                                    Constants::NodeOutlineThinkness,
                                    30, 0),
                          false);
    mTail->mNode.setFillColorBody(Constants::ControlTableThemeColor);
    mTail->mNode.setOutlineColor(Constants::ControlTableThemeColor);
    mTail->mNode.setText(mNameTail);
    mTail->setPosition(Constants::ShiftNode);
    temp->attachChild(mTail);

    updateHeadPosition();
}
void BasicList::updateHeadPosition() {
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
        x = -(Constants::ShiftNode.x + (mCountNode - 1) * mShiftNode.x / 2);
        y = -(Constants::ShiftNode.y + (mCountNode - 1) * mShiftNode.y / 2);
    }
    mHead->move(x, y);
}