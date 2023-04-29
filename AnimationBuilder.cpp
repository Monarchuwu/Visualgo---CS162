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
    Animation animation;

    UpdateSceneNode temp;
    while (src != nullptr) {
        AnimationScene scene;

        sf::Color oldFillBody = src->mNode.getFillColorBody();
        sf::Color oldFillText = src->mNode.getFillColorText();

        temp = UpdateSceneNode(src);
        temp.setFillColor(colorBody);
        temp.setOutlineColor(colorOutline);
        temp.setTextColor(colorText);
        scene.push_back(temp);
        animation.push_back(scene);

        if (src == dest) break;

        temp = UpdateSceneNode(src);
        temp.setFillColor(oldFillBody);
        temp.setTextColor(oldFillText);
        scene[0] = temp;
        animation.push_back(scene);

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

    AnimationScene scene;
    scene.push_back(temp);

    Animation animation;
    animation.push_back(scene);

    return animation;
}

void add(Animation& A, const Animation& B) {
    for (int i = 0; i < B.size(); ++i) {
        A.push_back(B[i]);
    }
}
