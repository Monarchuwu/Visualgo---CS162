#pragma once
#include "Animation.h"

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
