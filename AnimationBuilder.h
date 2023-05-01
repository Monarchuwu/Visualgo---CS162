#pragma once
#include "Animation.h"
#include "SceneNode.h"

Vector<UpdateSceneNode> holdColorAnimationFind(SceneNode* src, SceneNode* dest);

// Insert

// color 1 is the color of the node deleted
// color 2 is the color of the prev and next nodes
//Animation
//buildAnimationInsert(SceneNode* ptr, SceneNode* mHead, SceneNode* newPtr,
//                     sf::Color colorBody1,
//                     sf::Color colorOutline1,
//                     sf::Color colorText1,
//                     sf::Color colorBody2,
//                     sf::Color colorOutline2,
//                     sf::Color colorText2,
//                     bool isHead,
//                     bool isTail,
//                     sf::Vector2f shiftNode);

// Delete

// color 1 is the color of the node deleted
// color 2 is the color of the prev and next nodes
//Animation
//buildAnimationDelete(SceneNode* ptr, SceneNode* mHead,
//                     sf::Color colorBody1,
//                     sf::Color colorOutline1,
//                     sf::Color colorText1,
//                     sf::Color colorBody2,
//                     sf::Color colorOutline2,
//                     sf::Color colorText2,
//                     bool isHead,
//                     bool isTail,
//                     sf::Vector2f shiftNode);

// Update

//Animation
//buildAnimationUpdate(SceneNode* ptr,
//                     int val,
//                     sf::Color colorBody,
//                     sf::Color colorOutline,
//                     sf::Color colorText);

Animation
buildAnimationFind(SceneNode* src, SceneNode* dest,
                   sf::Color colorBody,
                   sf::Color colorOutline,
                   sf::Color colorText);
