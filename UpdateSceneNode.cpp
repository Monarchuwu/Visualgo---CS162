#include "UpdateSceneNode.h"

UpdateSceneNode::UpdateSceneNode(SceneNode* ptr)
    : mPtr(ptr),
      mStatus(0),
      mVal(),
      mColorBody(),
      mColorOutline(),
      mColorText(),
      mArrowVisible() {
    setArrowVisible(true);
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
void UpdateSceneNode::setAttach(SceneNode* children) {
    mAttachChild = children;
    mStatus |= 1 << Attach;
}
void UpdateSceneNode::setAttachHolder(SceneNode** holder) {
    mHolder = holder;
    mStatus |= 1 << Attach;
    mStatus |= 1 << Holder;
}
void UpdateSceneNode::setDetach(SceneNode* children) {
    mDetachChild = children;
    mStatus |= 1 << Detach;
}
void UpdateSceneNode::setDetach(SceneNode** holder, SceneNode* children) {
    mHolder     = holder;
    mDetachChild = children;
    mStatus |= 1 << Detach;
    mStatus |= 1 << Holder;
}
void UpdateSceneNode::setTranslation(const sf::Vector2f &translation) {
    mTranslation = translation;
    mStatus |= 1 << Translation;
}
void UpdateSceneNode::setTranslation(float x, float y) {
    setTranslation(sf::Vector2f(x, y));
}
void UpdateSceneNode::setArrowVisible(bool visible) {
    mArrowVisible = visible;
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

    if (mStatus >> Attach & 1) {
        if (mStatus >> Holder & 1)
            mPtr->attachChild(*mHolder);
        else
            mPtr->attachChild(mAttachChild);
    }

    if (mStatus >> Detach & 1) {
        if (mStatus >> Holder & 1)
            *mHolder = mPtr->detachChild(*mDetachChild);
        else
            mPtr->detachChild(*mDetachChild);
    }

    if (mStatus >> Translation & 1) {
        mPtr->move(mTranslation);
    }
    
    if (mArrowVisible) {
        mPtr->enableArrow();
    }
    else {
        mPtr->disableArrow();
    }
}