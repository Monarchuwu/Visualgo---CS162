#include "UpdateSceneNode.h"

UpdateSceneNode::UpdateSceneNode(SceneNode* ptr)
    : mPtr(ptr),
      mStatus(0),
      mVal(),
      mColorBody(),
      mColorOutline(),
      mColorText(),
      mParent() {
}

void UpdateSceneNode::setVal(int val) {
    mVal = val;
    mStatus |= 1 << Val;
}
void UpdateSceneNode::setFillColor(const sf::Color &color) {
    mColorBody = color;
    mStatus |= 1 << ColorBody;
}
void UpdateSceneNode::setOutlineColor(const sf::Color& color) {
    mColorOutline = color;
    mStatus |= 1 << ColorOutLine;
}
void UpdateSceneNode::setTextColor(const sf::Color &color) {
    mColorText = color;
    mStatus |= 1 << ColorText;
}
void UpdateSceneNode::setParent(SceneNode* parent) {
    mParent = parent;
    mStatus |= 1 << Parent;
}
void UpdateSceneNode::setChildren(const Vector<SceneNode*>&children) {
    mChildren = children;
    mStatus |= 1 << Children;
}
void UpdateSceneNode::setTranslation(const sf::Vector2f &translation) {
    mTranslation = translation;
    mStatus |= 1 << Translation;
}

void UpdateSceneNode::apply() {
    if (mStatus >> Val & 1) {
        mPtr->mNode.setValue(mVal);
    }

    if (mStatus >> ColorBody & 1) {
        mPtr->mNode.setFillColorBody(mColorBody);
    }

    if (mStatus >> ColorOutLine & 1) {
        mPtr->mNode.setOutlineColor(mColorOutline);
    }

    if (mStatus >> ColorText & 1) {
        mPtr->mNode.setFillColorText(mColorText);
    }

    if (mStatus >> Parent & 1) {
        mPtr->mParent = mParent;
    }

    if (mStatus >> Children & 1) {
        mPtr->mChildren = mChildren;
    }

    if (mStatus >> Translation & 1) {
        mPtr->move(mTranslation);
    }
}