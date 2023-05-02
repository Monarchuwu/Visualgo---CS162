#include <cassert>
#include "AnimationBuilder.h"
#include "SceneNodeHolder.h"

Vector<UpdateSceneNode> holdColorAnimationFind(SceneNode* src, SceneNode* dest) {
    Vector<UpdateSceneNode> list;

    while (src != nullptr) {
        list.push_back(UpdateSceneNode(src));
        list.back().setFillColor(src->mNode.getFillColorBody());
        list.back().setOutlineColor(src->mNode.getOutlineColor());
        list.back().setTextColor(src->mNode.getFillColorText());

        if (src == dest) break;
        src = src->mChildren;
    }

    return list;
}

Animation
buildAnimationInsertAtBeginning(SceneNode* mHead, SceneNode* newPtr,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode,
                                sf::Vector2f headPosition) {

    Animation animation;

    /* ---------- Scene 1 ---------- */
    AnimationState scene1(0.75f);
    /* ------ Highlight Node  ------ */
    // Update 1.1
    UpdateSceneNode update1_1(mHead);
    update1_1.setFillColor(colorBody2);
    update1_1.setOutlineColor(colorOutline2);
    update1_1.setTextColor(colorText2);
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    AnimationState scene2(0.75f);
    /* --- Attach newPtr - mHead --- */
    /* ------ Invisible arrow ------ */
    /* ----- Set the position  ----- */
    UpdateSceneNode update2_1(newPtr);
    update2_1.setAttach(mHead);
    update2_1.setTranslation(headPosition - shiftNode / 2.f);
    UpdateSceneNode update2_2(mHead);
    update2_2.setArrowVisible(false);
    update2_2.setTranslation(-headPosition + shiftNode);
    /* ------ mHead = newPtr  ------ */
    UpdateSceneNode update2_3(newPtr);
    update2_3.setAssigned(SceneNodeHolder::Holder31);
    /* ------- Enable newPtr  ------ */
    /* ----- Highlight newptr  ----- */
    /* ------- Set TextBelow ------- */
    UpdateSceneNode update2_4(newPtr);
    update2_4.setFillColor(colorBody1);
    update2_4.setOutlineColor(colorOutline1);
    update2_4.setTextColor(colorText1);
    update2_4.setTextBelow("tmp/");
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    scene2.addUpdateSceneNode(update2_3);
    scene2.addUpdateSceneNode(update2_4);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    AnimationState scene3(0.75f);
    /* ------- Visible arrow ------- */
    /* ------- Set TextBelow ------- */
    UpdateSceneNode update3_1(newPtr);
    update3_1.setTextBelow("Head/");
    UpdateSceneNode update3_2(mHead);
    update3_2.setArrowVisible(true);
    update3_2.handleHeadTailTextBelow();
    // Scene add
    scene3.addUpdateSceneNode(update3_1);
    scene3.addUpdateSceneNode(update3_2);
    /* ----------------------------- */

    /* ---------- Scene 4 ---------- */
    AnimationState scene4(0.75f);
    /* ---- Un-hightlight Node  ---- */
    UpdateSceneNode update4_1(newPtr);
    update4_1.setFillColor(Constants::NodeFillColor);
    update4_1.setOutlineColor(Constants::NodeOutlineColor);
    update4_1.setTextColor(Constants::TextNodeColor);
    UpdateSceneNode update4_2(mHead);
    update4_2.setFillColor(Constants::NodeFillColor);
    update4_2.setOutlineColor(Constants::NodeOutlineColor);
    update4_2.setTextColor(Constants::TextNodeColor);
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    scene4.addUpdateSceneNode(update4_2);
    /* ----------------------------- */

    // Animation add
    animation.addState(scene1);
    animation.addState(scene2);
    animation.addState(scene3);
    animation.addState(scene4);

    return animation;
}

Animation
buildAnimationInsertAtEnd(SceneNode* mHead, SceneNode* mTail, SceneNode* newPtr,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode) {
    Animation animation;

    /* ---------- Scene 1 ---------- */
    AnimationState scene1(0.75f);
    /* ------ Highlight Node  ------ */
    // Update 1.1
    UpdateSceneNode update1_1(mTail);
    update1_1.setFillColor(colorBody2);
    update1_1.setOutlineColor(colorOutline2);
    update1_1.setTextColor(colorText2);
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    AnimationState scene2(0.75f);
    /* --- Attach mTail - newPtr --- */
    /* ------ Invisible arrow ------ */
    /* ----- Set the position  ----- */
    UpdateSceneNode update2_1(mTail);
    update2_1.setAttach(newPtr);
    UpdateSceneNode update2_2(newPtr);
    update2_2.setArrowVisible(false);
    update2_2.setTranslation(shiftNode);
    UpdateSceneNode update2_3(mHead);
    update2_3.setTranslation(-shiftNode / 2.f);
    /* ------- Enable newPtr  ------ */
    /* ----- Highlight newptr  ----- */
    /* ------- Set TextBelow ------- */
    UpdateSceneNode update2_4(newPtr);
    update2_4.setFillColor(colorBody1);
    update2_4.setOutlineColor(colorOutline1);
    update2_4.setTextColor(colorText1);
    update2_4.setTextBelow("tmp/");
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    scene2.addUpdateSceneNode(update2_3);
    scene2.addUpdateSceneNode(update2_4);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    AnimationState scene3(0.75f);
    /* ------- Visible arrow ------- */
    /* ------- Set TextBelow ------- */
    UpdateSceneNode update3_1(newPtr);
    update3_1.setArrowVisible(true);
    update3_1.setTextBelow("Tail/");
    UpdateSceneNode update3_2(mTail);
    update3_2.setHoldHeadTextBelow();
    // Scene add
    scene3.addUpdateSceneNode(update3_1);
    scene3.addUpdateSceneNode(update3_2);
    /* ----------------------------- */

    /* ---------- Scene 4 ---------- */
    AnimationState scene4(0.75f);
    /* ---- Un-hightlight Node  ---- */
    UpdateSceneNode update4_1(mTail);
    update4_1.setFillColor(Constants::NodeFillColor);
    update4_1.setOutlineColor(Constants::NodeOutlineColor);
    update4_1.setTextColor(Constants::TextNodeColor);
    UpdateSceneNode update4_2(newPtr);
    update4_2.setFillColor(Constants::NodeFillColor);
    update4_2.setOutlineColor(Constants::NodeOutlineColor);
    update4_2.setTextColor(Constants::TextNodeColor);
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    scene4.addUpdateSceneNode(update4_2);
    /* ----------------------------- */

    // Animation add
    animation.addState(scene1);
    animation.addState(scene2);
    animation.addState(scene3);
    animation.addState(scene4);

    return animation;
}

Animation
buildAnimationInsertAtMiddle(SceneNode* ptr, SceneNode* mHead, SceneNode* newPtr,
                             sf::Color colorBody1,
                             sf::Color colorOutline1,
                             sf::Color colorText1,
                             sf::Color colorBody2,
                             sf::Color colorOutline2,
                             sf::Color colorText2,
                             sf::Vector2f shiftNode) {
    SceneNode* parent = ptr;
    SceneNode* child  = parent->mChildren;
    ptr               = newPtr;

    Animation animation;

    /* ---------- Scene 1 ---------- */
    /* ------ Highlight Node  ------ */
    /* ------ Invisible arrow ------ */
    /* ------- Set TextBelow ------- */
    /* ----- Fix the distance  ----- */
    /* ------- Left go left  ------- */
    /* ------ Right to right  ------ */
    AnimationState scene1(1.0f);
    // Update 1.1
    UpdateSceneNode update1_1(mHead);
    update1_1.setTranslation(-shiftNode.x / 2, 0);
    // Update 1.2
    UpdateSceneNode update1_2(parent);
    update1_2.setFillColor(colorBody2);
    update1_2.setOutlineColor(colorOutline2);
    update1_2.setTextColor(colorText2);
    update1_2.addTextBelow("prv/");
    // Update 1.3
    UpdateSceneNode update1_3(child);
    update1_3.setFillColor(colorBody2);
    update1_3.setOutlineColor(colorOutline2);
    update1_3.setTextColor(colorText2);
    update1_3.setArrowVisible(false);
    update1_3.addTextBelow("nxt/");
    update1_3.setTranslation(shiftNode.x, 0);
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    scene1.addUpdateSceneNode(update1_2);
    scene1.addUpdateSceneNode(update1_3);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    /* --------- Enable ptr -------- */
    /* ------- Highlight ptr ------- */
    /* ------- Set TextBelow ------- */
    /* --- Detach parent - child --- */
    /* Attach parent - ptr - child   */
    /* ---- ptr is pulled down  ---- */
    /* ------ Visible arrows  ------ */
    AnimationState scene2(1.0f);
    // Update 2.1
    UpdateSceneNode update2_1(parent);
    update2_1.setDetach(&SceneNodeHolder::Holder11);
    // Update 2.2
    UpdateSceneNode update2_2(parent);
    update2_2.setAttach(ptr);
    // Update 2.3
    UpdateSceneNode update2_3(ptr);
    update2_3.setFillColor(colorBody1);
    update2_3.setOutlineColor(colorOutline1);
    update2_3.setTextColor(colorText1);
    update2_3.addTextBelow("cur/");
    update2_3.setAttachHolder(&SceneNodeHolder::Holder11);
    update2_3.setTranslation(shiftNode.x, Constants::ShiftNode.x);
    update2_3.setArrowVisible(true);
    // Update 2.4
    UpdateSceneNode update2_4(child);
    update2_4.setTranslation(-shiftNode.x, -Constants::ShiftNode.x);
    update2_4.setArrowVisible(true);
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    scene2.addUpdateSceneNode(update2_3);
    scene2.addUpdateSceneNode(update2_4);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    /* ----- ptr is pulled up  ----- */
    AnimationState scene3(1.0f);
    // Update 3.1
    UpdateSceneNode update3_1(ptr);
    update3_1.setTranslation(0, -Constants::ShiftNode.x);
    // Update 3.2
    UpdateSceneNode update3_2(child);
    update3_2.setTranslation(0, Constants::ShiftNode.x);
    // Scene add
    scene3.addUpdateSceneNode(update3_1);
    scene3.addUpdateSceneNode(update3_2);
    /* ----------------------------- */

    /* ---------- Scene 4 ---------- */
    /* ----- Un-highlight Node ----- */
    /* ----- Reset Text Below  ----- */
    AnimationState scene4(1.0f);
    // Update 4.1
    UpdateSceneNode update4_1(parent);
    update4_1.setFillColor(Constants::NodeFillColor);
    update4_1.setOutlineColor(Constants::NodeOutlineColor);
    update4_1.setTextColor(Constants::TextNodeColor);
    update4_1.resetTextBelow();
    // Update 4.2
    UpdateSceneNode update4_2(ptr);
    update4_2.setFillColor(Constants::NodeFillColor);
    update4_2.setOutlineColor(Constants::NodeOutlineColor);
    update4_2.setTextColor(Constants::TextNodeColor);
    update4_2.resetTextBelow();
    // Update 4.3
    UpdateSceneNode update4_3(child);
    update4_3.setFillColor(Constants::NodeFillColor);
    update4_3.setOutlineColor(Constants::NodeOutlineColor);
    update4_3.setTextColor(Constants::TextNodeColor);
    update4_3.resetTextBelow();
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    scene4.addUpdateSceneNode(update4_2);
    scene4.addUpdateSceneNode(update4_3);
    /* ----------------------------- */

    // Animation add
    animation.addState(scene1);
    animation.addState(scene2);
    animation.addState(scene3);
    animation.addState(scene4);

    return animation;
}

Animation
buildAnimationDeleteAtBeginning(SceneNode* mHead,
                                sf::Color colorBody1,
                                sf::Color colorOutline1,
                                sf::Color colorText1,
                                sf::Color colorBody2,
                                sf::Color colorOutline2,
                                sf::Color colorText2,
                                sf::Vector2f shiftNode,
                                sf::Vector2f headPosition) {

    SceneNode* tmp = mHead->mChildren;
    
    Animation animation;

    /* ---------- Scene 1 ---------- */
    AnimationState scene1(0.75f);
    /* ------ Highlight Node  ------ */
    // Update 1.1
    UpdateSceneNode update1_1(mHead);
    update1_1.setFillColor(colorBody2);
    update1_1.setOutlineColor(colorOutline2);
    update1_1.setTextColor(colorText2);
    // Update 1.2
    UpdateSceneNode update1_2(tmp);
    update1_2.setFillColor(colorBody1);
    update1_2.setOutlineColor(colorOutline1);
    update1_2.setTextColor(colorText1);
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    scene1.addUpdateSceneNode(update1_2);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    AnimationState scene2(0.75f);
    /* ------ Invisible arrow ------ */
    /* ------- Set TextBelow ------- */
    UpdateSceneNode update2_1(tmp);
    update2_1.setArrowVisible(false);
    update2_1.addTextBelow("Head/");
    update2_1.handleTailHeadTextBelow();
    UpdateSceneNode update2_2(mHead);
    update2_2.setTextBelow("tmp/");
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    AnimationState scene3(0.75f);
    /* ---- Detach mHead - tmp  ---- */
    /* -------- Set Delete  -------- */
    UpdateSceneNode update3_1(mHead);
    update3_1.setDetach(&SceneNodeHolder::Holder01);
    update3_1.setDelete();
    UpdateSceneNode update3_2(tmp);
    update3_2.setAssigned(SceneNodeHolder::Holder21); // ->mHead
    /* ------- Set Position  ------- */
    update3_2.setTranslation(headPosition - shiftNode / 2.f);
    // Scene add
    scene3.addUpdateSceneNode(update3_1);
    scene3.addUpdateSceneNode(update3_2);
    /* ----------------------------- */

    /* ---------- Scene 4 ---------- */
    AnimationState scene4(0.75f);
    /* ---- Un-hightlight Node  ---- */
    UpdateSceneNode update4_1(tmp);
    update4_1.setFillColor(Constants::NodeFillColor);
    update4_1.setOutlineColor(Constants::NodeOutlineColor);
    update4_1.setTextColor(Constants::TextNodeColor);
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    /* ----------------------------- */

    // Animation add
    animation.addState(scene1);
    animation.addState(scene2);
    animation.addState(scene3);
    animation.addState(scene4);

    return animation;
}

Animation
buildAnimationDeleteAtMiddle(SceneNode* ptr, SceneNode* mHead,
                             sf::Color colorBody1,
                             sf::Color colorOutline1,
                             sf::Color colorText1,
                             sf::Color colorBody2,
                             sf::Color colorOutline2,
                             sf::Color colorText2,
                             sf::Vector2f shiftNode) {
    SceneNode* parent = ptr;
    ptr               = parent->mChildren;
    SceneNode* child  = ptr->mChildren;

    Animation animation;

    /* ---------- Scene 1 ---------- */
    /* ------ Highlight Node  ------ */
    /* ------ Set Text Below  ------ */
    /* ---- ptr is pulled down  ---- */
    AnimationState scene1(1.0f);
    // Update 1.1
    UpdateSceneNode update1_1(parent);
    update1_1.setFillColor(colorBody2);
    update1_1.setOutlineColor(colorOutline2);
    update1_1.setTextColor(colorText2);
    update1_1.addTextBelow("prv/");
    // Update 1.2
    UpdateSceneNode update1_2(ptr);
    update1_2.setFillColor(colorBody1);
    update1_2.setOutlineColor(colorOutline1);
    update1_2.setTextColor(colorText1);
    update1_2.setTranslation(sf::Vector2f(0, Constants::ShiftNode.x));
    update1_2.addTextBelow("cur/");
    // Update 1.3
    UpdateSceneNode update1_3(child);
    update1_3.setFillColor(colorBody2);
    update1_3.setOutlineColor(colorOutline2);
    update1_3.setTextColor(colorText2);
    update1_3.setTranslation(0, -Constants::ShiftNode.x);
    update1_3.addTextBelow("nxt/");
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    scene1.addUpdateSceneNode(update1_2);
    scene1.addUpdateSceneNode(update1_3);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    /* ----- Fix the distance  ----- */
    /* ------- Left go right ------- */
    /* ------- Right to left ------- */
    AnimationState scene2(1.0f);
    // Update 2.1
    UpdateSceneNode update2_1(mHead);
    update2_1.setTranslation(shiftNode.x / 2, 0);
    // Update 2.2
    UpdateSceneNode update2_2(ptr);
    update2_2.setTranslation(-shiftNode.x / 2, 0);
    // Update 2.3
    UpdateSceneNode update2_3(child);
    update2_3.setTranslation(-shiftNode.x / 2, 0);
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    scene2.addUpdateSceneNode(update2_3);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    /* ---- Invisible 2 arrows  ---- */
    AnimationState scene3(1.0f);
    // Update 3.1
    UpdateSceneNode update3_1(ptr);
    update3_1.setArrowVisible(false);
    // Update 3.2
    UpdateSceneNode update3_2(child);
    update3_2.setArrowVisible(false);
    // Scene add
    scene3.addUpdateSceneNode(update3_1);
    scene3.addUpdateSceneNode(update3_2);
    /* ----------------------------- */

    /* ---------- Scene 4 ---------- */
    /* - Connect parent and child  - */
    /* -------- Delete ptr  -------- */
    /* ------- Enable arrow  ------- */
    AnimationState scene4(1.0f);
    // Update 4.1
    UpdateSceneNode update4_1(parent);
    update4_1.setDetach(&SceneNodeHolder::Holder01);
    // Update 4.2
    UpdateSceneNode update4_2(ptr);
    update4_2.setDetach(&SceneNodeHolder::Holder01); // Holder01 contains child
    update4_2.setDelete();
    // Update 4.3
    UpdateSceneNode update4_3(parent);
    update4_3.setAttachHolder(&SceneNodeHolder::Holder01);
    // Update 4.4
    UpdateSceneNode update4_4(child);
    update4_4.setArrowVisible(true);
    update4_4.setTranslation(shiftNode.x / 2, Constants::ShiftNode.x);
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    scene4.addUpdateSceneNode(update4_2);
    scene4.addUpdateSceneNode(update4_3);
    scene4.addUpdateSceneNode(update4_4);
    /* ----------------------------- */

    /* ---------- Scene 5 ---------- */
    /* ----- Un-highlight Node ----- */
    /* ----- Reset Text Below  ----- */
    AnimationState scene5(1.0f);
    // Update 5.1
    UpdateSceneNode update5_1(parent);
    update5_1.setFillColor(Constants::NodeFillColor);
    update5_1.setOutlineColor(Constants::NodeOutlineColor);
    update5_1.setTextColor(Constants::TextNodeColor);
    update5_1.resetTextBelow();
    // Update 5.2
    UpdateSceneNode update5_2(child);
    update5_2.setFillColor(Constants::NodeFillColor);
    update5_2.setOutlineColor(Constants::NodeOutlineColor);
    update5_2.setTextColor(Constants::TextNodeColor);
    update5_2.resetTextBelow();
    // Scene add
    scene5.addUpdateSceneNode(update5_1);
    scene5.addUpdateSceneNode(update5_2);
    /* ----------------------------- */

    // Animation add
    animation.addState(scene1);
    animation.addState(scene2);
    animation.addState(scene3);
    animation.addState(scene4);
    animation.addState(scene5);

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

        src = src->mChildren;
    }

    return animation;
}
