#include <cassert>
#include "AnimationBuilder.h"

Vector<UpdateSceneNode> holdColorAnimationFind(SceneNode* src, SceneNode* dest) {
    Vector<UpdateSceneNode> list;

    while (true) {
        list.push_back(UpdateSceneNode(src));
        list.back().setFillColor(src->mNode.getFillColorBody());
        list.back().setOutlineColor(src->mNode.getOutlineColor());
        list.back().setTextColor(src->mNode.getFillColorText());

        if (src == dest) break;
        src = src->mChildren[0];
    }

    return list;
}

Animation
buildAnimationFind(SceneNode* src, SceneNode* dest,
                   sf::Color colorBody,
                   sf::Color colorOutline,
                   sf::Color colorText) {

    UpdateSceneNode temp;
    AnimationState state;
    Animation animation;

    while (src != nullptr) {

        sf::Color oldFillBody = src->mNode.getFillColorBody();
        sf::Color oldFillText = src->mNode.getFillColorText();

        temp = UpdateSceneNode(src);
        temp.setFillColor(colorBody);
        temp.setOutlineColor(colorOutline);
        temp.setTextColor(colorText);

        state.addUpdateSceneNode(temp);
        animation.addState(state);
        state.popUpdateSceneNode();

        if (src == dest) break;

        temp = UpdateSceneNode(src);
        temp.setFillColor(oldFillBody);
        temp.setTextColor(oldFillText);
        state.addUpdateSceneNode(temp);
        animation.addState(state);
        state.popUpdateSceneNode();

        src = src->mChildren[0];
    }

    assert(src != nullptr);
    return animation;
}

Animation
buildAnimationUpdate(SceneNode* ptr,
                     int val,
                     sf::Color colorBody,
                     sf::Color colorOutline,
                     sf::Color colorText) {
    UpdateSceneNode temp(ptr);
    temp.setVal(val);
    temp.setFillColor(colorBody);
    temp.setOutlineColor(colorOutline);
    temp.setTextColor(colorText);

    AnimationState state;
    state.addUpdateSceneNode(temp);

    Animation animation;
    animation.addState(state);

    return animation;
}