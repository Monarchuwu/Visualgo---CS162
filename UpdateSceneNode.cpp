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
void UpdateSceneNode::setDetach(SceneNode** holder) {
    mHolder = holder;
    mStatus |= 1 << Detach;
    mStatus |= 1 << Holder;
}
void UpdateSceneNode::setAssigned(SceneNode** holder) {
    mHolder = holder;
    mStatus |= 1 << Assigned;
    mStatus |= 1 << Holder;
}
void UpdateSceneNode::setDelete() {
    mStatus |= 1 << Delete;
}
void UpdateSceneNode::setTranslation(const sf::Vector2f& translation) {
    mTranslation = translation;
    mStatus |= 1 << Translation;
}
void UpdateSceneNode::setTranslation(float x, float y) {
    setTranslation(sf::Vector2f(x, y));
}
void UpdateSceneNode::setArrowVisible(bool visible) {
    mArrowVisible = visible;
    mStatus |= 1 << VisibleArrow;
}
void UpdateSceneNode::setTextBelow(std::string str) {
    mTextBelow = str;
    mStatus |= 1 << TextBelow;
}
void UpdateSceneNode::addTextBelow(std::string str) {
    mTextBelow = str;
    mStatus |= 1 << AddTextBelow;
}
void UpdateSceneNode::resetTextBelow() {
    mStatus |= 1 << ResetTextBelow;
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
        *mHolder = mPtr->detachChild();
    }

    if (mStatus >> Assigned & 1) {
        *mHolder = mPtr;
    }

    if (mStatus >> Delete & 1) {
        delete mPtr;
        return;
    }

    if (mStatus >> Translation & 1) {
        mPtr->move(mTranslation);
    }
    
    if (mStatus >> VisibleArrow & 1) {
        if (mArrowVisible)
            mPtr->enableArrow();
        else mPtr->disableArrow();
    }

    if (mStatus >> TextBelow & 1) {
        mPtr->mNode.setTextBelow(mTextBelow);
    }

    if (mStatus >> AddTextBelow & 1) {
        mPtr->mNode.setTextBelow(mPtr->mNode.getTextBelow() + mTextBelow);
    }

    if (mStatus >> ResetTextBelow & 1) {
        std::string str = mPtr->mNode.getTextBelow();
        if (str.size() >= 5) {
            std::string tmp;
            tmp.push_back(str[0]);
            tmp.push_back(str[1]);
            tmp.push_back(str[2]);
            tmp.push_back(str[3]);
            tmp.push_back(str[4]);

            if (tmp == "Head/" || tmp == "Tail/") {
                str = tmp;
            }
            else str = "";
        }
        else str = "";

        mPtr->mNode.setTextBelow(str);
    }
}