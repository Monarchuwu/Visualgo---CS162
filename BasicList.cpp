#include "BasicList.h"
#include "Arrow.h"
#include "Constants.h"

BasicList::BasicList(Carrier &carrier, Vector<int> arr)
    : mCarrier(carrier),
      mArr(arr),
      mHead(nullptr),
      mTail(nullptr) {

    updateArray();
}

size_t BasicList::getCountNode() const { return mArr.size(); }

void BasicList::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    mHead->drawArrow(target, states);
    mHead->draw(target, states);
}
void BasicList::updateArray(Vector<int> arr) {
    mArr = arr;
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
}
void BasicList::updateHeadPosition() {
    int mCountNode = mArr.size() + 2;
    mHead->setPosition(Constants::MidPointSceneVisual);
    mHead->move(-(mCountNode - 1) * Constants::ShiftNode.x / 2, 0);
}