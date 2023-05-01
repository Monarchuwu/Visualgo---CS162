#pragma once
#include "Animation.h"
#include "SceneNode.h"

Vector<UpdateSceneNode> holdColorAnimationFind(SceneNode* src, SceneNode* dest);

// color 1 is the color of the node inserted
// color 2 is the color of the head node
Animation
buildAnimationInsertAtBeginning(SceneNode* mHead, SceneNode* newPtr,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode,
                                sf::Vector2f headPosition);

// color 1 is the color of the node inserted
// color 2 is the color of the prev and next nodes
Animation
buildAnimationInsertAtMiddle(SceneNode* ptr, SceneNode* mHead, SceneNode* newPtr,
                             sf::Color colorBody1,
                             sf::Color colorOutline1,
                             sf::Color colorText1,
                             sf::Color colorBody2,
                             sf::Color colorOutline2,
                             sf::Color colorText2,
                             sf::Vector2f shiftNode);

// color 1 is the color of the node deleted
// color 2 is the color of the prev and next nodes
Animation
buildAnimationDeleteAtMiddle(SceneNode* ptr, SceneNode* mHead,
                             sf::Color colorBody1,
                             sf::Color colorOutline1,
                             sf::Color colorText1,
                             sf::Color colorBody2,
                             sf::Color colorOutline2,
                             sf::Color colorText2,
                             sf::Vector2f shiftNode);

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
