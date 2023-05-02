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
// color 2 is the color of the tail node
Animation
buildAnimationInsertAtEnd(SceneNode* mHead, SceneNode* mTail, SceneNode* newPtr,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode);

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

// color 1 is the color of the node inserted
// color 2 is the color of the head node
Animation
buildAnimationDeleteAtBeginning(SceneNode* mHead,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode,
                                sf::Vector2f headPosition);

// color 1 is the color of the node inserted
// color 2 is the color of the head node
Animation
buildAnimationDeleteAtEnd(SceneNode* mTail, SceneNode* mHead,
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
buildAnimationClearFromBeginning(SceneNode* mHead);

Animation
buildAnimationClearFromEnd(SceneNode* mTail);

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

// Copy from buildAnimationFind
Animation
buildAnimationFindWithoutTextBelow(SceneNode* src, SceneNode* dest, SceneNode* mTail,
                                   sf::Color colorBody,
                                   sf::Color colorOutline,
                                   sf::Color colorText);

Animation
buildAnimationAccess(SceneNode* ptr,
                   sf::Color colorBody,
                   sf::Color colorOutline,
                   sf::Color colorText);

// color 1 is the color of the node that is updated the value
// color 2 is the color of other nodes (highlight only)
// while (cur != target)
//   *(cur + 1) = *cur, cur = cur->prev
// *cur = val
Animation
buildAnimationInsertStaticArray(SceneNode* ptr, SceneNode* mTail,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                int val);

// color 1 is the color of the node that is updated the value
// color 2 is the color of other nodes (highlight only)
// while (cur != target)
//   *(cur + 1) = *cur, cur = cur->prev
// *cur = val
Animation
buildAnimationInsertStaticArrayAfterAllocate(
    SceneNode* ptr, SceneNode* mTail, SceneNode* mCopyTail,
    sf::Color colorBody1,
    sf::Color colorOutline1,
    sf::Color colorText1,
    sf::Color colorBody2,
    sf::Color colorOutline2,
    sf::Color colorText2,
    int val);

// color 1 is the color of the node that is updated the value
// color 2 is the color of other nodes (highlight only)
// while (cur != Tail)
//   *cur = *(cur + 1), cur = cur->next
// change color of cur
Animation
buildAnimationDeleteStaticArray(SceneNode* ptr, SceneNode* mTail,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2);

Animation
buildAnimationAllocateDynamicArray(SceneNode* mHead, SceneNode* mCopy,
                                   sf::Color colorBody1,
                                   sf::Color colorOutline1,
                                   sf::Color colorText1,
                                   sf::Color colorBody2,
                                   sf::Color colorOutline2,
                                   sf::Color colorText2);
