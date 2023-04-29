#pragma once
#include "SceneNode.h"

enum AnimationUpdate {
    Val,
    ColorBody,
    ColorOutLine,
    ColorText,
    Parent,
    Children,
    Translation
};

class UpdateSceneNode {
public:
    UpdateSceneNode(SceneNode* ptr = nullptr);

    void setVal(int val);
    void setFillColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setTextColor(const sf::Color &color);
    void setParent(SceneNode* parent);
    void setChildren(const Vector<SceneNode*> &children);
    void setTranslation(const sf::Vector2f &translation);

    void apply();

private:
    SceneNode* mPtr;
    int mStatus;

    int mVal;
    sf::Color mColorBody;
    sf::Color mColorOutline;
    sf::Color mColorText;
    SceneNode* mParent;
    Vector<SceneNode*> mChildren;
    sf::Vector2f mTranslation;
};
