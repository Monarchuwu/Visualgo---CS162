#include <cassert>
#include "AnimationBuilder.h"
#include "SceneNodeHolder.h"

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
buildAnimationInsert(SceneNode* ptr, SceneNode* mHead,
                     sf::Color colorBody1,
                     sf::Color colorOutline1,
                     sf::Color colorText1,
                     sf::Color colorBody2,
                     sf::Color colorOutline2,
                     sf::Color colorText2,
                     bool isHead,
                     bool isTail,
                     int val) {

    SceneNode* child  = ptr;
    SceneNode* parent = ptr->mParent;
    ptr               = new SceneNode(BasicNode(Constants::CirleNodeRadius,
                                                Constants::NodeOutlineThinkness,
                                                val),
                                      false);

    Animation animation;

    /* ---------- Scene 1 ---------- */
    /* ------ Highlight Node  ------ */
    /* ----- Disvisible arrow  ----- */
    /* ----- Fix the distance  ----- */
    /* ------- Left go left  ------- */
    /* ------ Right to right  ------ */
    AnimationState scene1(0.5f);
    // Update 1.1
    UpdateSceneNode update1_1(mHead);
    update1_1.setTranslation(-Constants::ShiftNode.x / 2, 0);
    // Update 1.2
    UpdateSceneNode update1_2(parent);
    if (!isHead) {
        update1_2.setFillColor(colorBody2);
        update1_2.setOutlineColor(colorOutline2);
        update1_2.setTextColor(colorText2);
    }
    else {
        update1_2.setFillColor(Constants::ControlTableThemeColor);
        update1_2.setOutlineColor(Constants::ControlTableThemeColor);
        update1_2.setTextColor(Constants::TextNodeColor);
    }
    // Update 1.3
    UpdateSceneNode update1_3(child);
    if (!isTail) {
        update1_3.setFillColor(colorBody2);
        update1_3.setOutlineColor(colorOutline2);
        update1_3.setTextColor(colorText2);
    }
    else {
        update1_3.setFillColor(Constants::ControlTableThemeColor);
        update1_3.setOutlineColor(Constants::ControlTableThemeColor);
        update1_3.setTextColor(Constants::TextNodeColor);
    }
    update1_3.setArrowVisible(false);
    update1_3.setTranslation(Constants::ShiftNode.x, 0);
    // Scene add
    scene1.addUpdateSceneNode(update1_1);
    scene1.addUpdateSceneNode(update1_2);
    scene1.addUpdateSceneNode(update1_3);
    /* ----------------------------- */

    /* ---------- Scene 2 ---------- */
    /* --------- Enable ptr -------- */
    /* ------- Highlight ptr ------- */
    /* --- Detach parent - child --- */
    /* Attach parent - ptr - child   */
    /* ---- ptr is pulled down  ---- */
    /* ----- Envisible arrows  ----- */
    AnimationState scene2(1.0f);
    // Update 2.1
    UpdateSceneNode update2_1(parent);
    update2_1.setDetach(&SceneNodeHolder::Holder02, child);
    // Update 2.2
    UpdateSceneNode update2_2(parent);
    update2_2.setAttach(ptr);
    // Update 2.3
    UpdateSceneNode update2_3(ptr);
    update2_3.setFillColor(colorBody1);
    update2_3.setOutlineColor(colorOutline1);
    update2_3.setTextColor(colorText1);
    update2_3.setAttachHolder(&SceneNodeHolder::Holder02);
    update2_3.setTranslation(Constants::ShiftNode.x, Constants::ShiftNode.x);
    update2_3.setArrowVisible(true);
    // Update 2.4
    UpdateSceneNode update2_4(child);
    update2_4.setTranslation(-Constants::ShiftNode.x, -Constants::ShiftNode.x);
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
    AnimationState scene4(1.0f);
    // Update 4.1
    UpdateSceneNode update4_1(parent);
    if (!isHead) {
        update4_1.setFillColor(Constants::NodeFillColor);
        update4_1.setOutlineColor(Constants::NodeOutlineColor);
        update4_1.setTextColor(Constants::TextNodeColor);
    }
    // Update 4.2
    UpdateSceneNode update4_2(ptr);
    update4_2.setFillColor(Constants::NodeFillColor);
    update4_2.setOutlineColor(Constants::NodeOutlineColor);
    update4_2.setTextColor(Constants::TextNodeColor);
    // Update 4.3
    UpdateSceneNode update4_3(child);
    if (!isTail) {
        update4_3.setFillColor(Constants::NodeFillColor);
        update4_3.setOutlineColor(Constants::NodeOutlineColor);
        update4_3.setTextColor(Constants::TextNodeColor);
    }
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
buildAnimationDelete(SceneNode* ptr, SceneNode* mHead,
                     sf::Color colorBody1,
                     sf::Color colorOutline1,
                     sf::Color colorText1,
                     sf::Color colorBody2,
                     sf::Color colorOutline2,
                     sf::Color colorText2,
                     bool isHead,
                     bool isTail) {
    SceneNode* parent = ptr->mParent;
    SceneNode* child  = ptr->mChildren[0];

    Animation animation;

    /* ---------- Scene 1 ---------- */
    /* ------ Highlight Node  ------ */
    /* ---- ptr is pulled down  ---- */
    AnimationState scene1(1.0f);
    // Update 1.1
    UpdateSceneNode update1_1(parent);
    if (!isHead) {
        update1_1.setFillColor(colorBody2);
        update1_1.setOutlineColor(colorOutline2);
        update1_1.setTextColor(colorText2);
    }
    else {
        update1_1.setFillColor(Constants::ControlTableThemeColor);
        update1_1.setOutlineColor(Constants::ControlTableThemeColor);
        update1_1.setTextColor(Constants::TextNodeColor);
    }
    // Update 1.2
    UpdateSceneNode update1_2(ptr);
    update1_2.setTranslation(sf::Vector2f(0, Constants::ShiftNode.x));
    update1_2.setFillColor(colorBody1);
    update1_2.setOutlineColor(colorOutline1);
    update1_2.setTextColor(colorText1);
    // Update 1.3
    UpdateSceneNode update1_3(child);
    update1_3.setTranslation(0, -Constants::ShiftNode.x);
    if (!isTail) {
        update1_3.setFillColor(colorBody2);
        update1_3.setOutlineColor(colorOutline2);
        update1_3.setTextColor(colorText2);
    }
    else {
        update1_3.setFillColor(Constants::ControlTableThemeColor);
        update1_3.setOutlineColor(Constants::ControlTableThemeColor);
        update1_3.setTextColor(Constants::TextNodeColor);
    }
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
    update2_1.setTranslation(Constants::ShiftNode.x / 2, 0);
    // Update 2.2
    UpdateSceneNode update2_2(ptr);
    update2_2.setTranslation(-Constants::ShiftNode.x / 2, 0);
    // Update 2.3
    UpdateSceneNode update2_3(child);
    update2_3.setTranslation(-Constants::ShiftNode.x / 2, 0);
    // Scene add
    scene2.addUpdateSceneNode(update2_1);
    scene2.addUpdateSceneNode(update2_2);
    scene2.addUpdateSceneNode(update2_3);
    /* ----------------------------- */

    /* ---------- Scene 3 ---------- */
    /* ---- Disvisible 2 arrows ---- */
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
    /* ------ Disvisible ptr  ------ */
    /* ------- Enable arrow  ------- */
    AnimationState scene4(1.0f);
    // Update 4.1
    UpdateSceneNode update4_1(parent);
    update4_1.setDetach(&SceneNodeHolder::Holder01, ptr);
    // Update 4.2
    UpdateSceneNode update4_2(ptr);
    update4_2.setFillColor(Constants::ParameterTableThemeColor);
    update4_2.setOutlineColor(Constants::ParameterTableThemeColor);
    update4_2.setTextColor(Constants::ParameterTableThemeColor);
    update4_2.setDetach(&SceneNodeHolder::Holder01, child);
    // Update 4.3
    UpdateSceneNode update4_3(child);
    update4_3.setArrowVisible(true);
    update4_3.setTranslation(Constants::ShiftNode.x / 2, Constants::ShiftNode.x);
    // Update 4.4
    UpdateSceneNode update4_4(parent);
    update4_4.setAttachHolder(&SceneNodeHolder::Holder01);
    // Scene add
    scene4.addUpdateSceneNode(update4_1);
    scene4.addUpdateSceneNode(update4_2);
    scene4.addUpdateSceneNode(update4_3);
    scene4.addUpdateSceneNode(update4_4);
    /* ----------------------------- */

    /* ---------- Scene 5 ---------- */
    /* ----- Un-highlight Node ----- */
    AnimationState scene5(1.0f);
    // Update 5.1
    UpdateSceneNode update5_1(parent);
    if (!isHead) {
        update5_1.setFillColor(Constants::NodeFillColor);
        update5_1.setOutlineColor(Constants::NodeOutlineColor);
        update5_1.setTextColor(Constants::TextNodeColor);
    }
    // Update 5.2
    UpdateSceneNode update5_2(child);
    if (!isTail) {
        update5_2.setFillColor(Constants::NodeFillColor);
        update5_2.setOutlineColor(Constants::NodeOutlineColor);
        update5_2.setTextColor(Constants::TextNodeColor);
    }
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