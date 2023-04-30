#pragma once
#include "SceneNode.h"

enum AnimationUpdate {
    Val,
    ColorBody,
    ColorOutLine,
    ColorText,
    Attach,
    Detach,
    Holder,
    Translation
};

class UpdateSceneNode {
public:
    UpdateSceneNode(SceneNode* ptr = nullptr);

    void setVal(int val);
    void setFillColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setTextColor(const sf::Color &color);
    void setAttach(SceneNode* children);
    void setAttachHolder(SceneNode** holder);
    void setDetach(SceneNode* children);
    void setDetach(SceneNode** holder, SceneNode* children);
    void setTranslation(const sf::Vector2f &translation);
    void setTranslation(float x, float y);
    void setArrowVisible(bool visible);

    void apply();

private:
    SceneNode* mPtr;
    int mStatus;

    int mVal;
    sf::Color mColorBody;
    sf::Color mColorOutline;
    sf::Color mColorText;
    SceneNode* mAttachChild;
    SceneNode* mDetachChild;
    SceneNode** mHolder;
    sf::Vector2f mTranslation;
    bool mArrowVisible;
};
