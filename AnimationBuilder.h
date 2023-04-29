#pragma once
#include "UpdateSceneNode.h"
#include "SceneNode.h"

typedef Vector<UpdateSceneNode> AnimationScene;
typedef Vector<AnimationScene> Animation;

Vector<UpdateSceneNode> holdColorAnimationFind(SceneNode* src, SceneNode* dest);

//Animation
//buildAnimationInsert(SceneNode* ptr,
//                     int val,
//                     sf::Color colorBody,
//                     sf::Color colorOutline,
//                     sf::Color colorText);

Animation
buildAnimationUpdate(SceneNode* ptr,
                     int val,
                     sf::Color colorBody,
                     sf::Color colorOutline,
                     sf::Color colorText);

Animation
buildAnimationFind(SceneNode* src, SceneNode* dest,
                   sf::Color colorBody,
                   sf::Color colorOutline,
                   sf::Color colorText);

// Push Animation B to the end of Animation A
void add(Animation& A, const Animation& B);