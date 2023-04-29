#include "SceneNode.h"
#include "Arrow.h"
#include <cassert>

SceneNode::SceneNode(BasicNode node, bool isNeedArrow)
    : mNode(node),
      mIsNeedArrow(isNeedArrow),
      mParent(nullptr) {
}
SceneNode::~SceneNode() {
    for (int i = 0; i < mChildren.size(); ++i) {
        SceneNode* child = mChildren[i];
        delete child;
    }

    if (mParent) {
        auto found = std::find(mParent->mChildren.begin(), mParent->mChildren.end(), this);
        if (found != mParent->mChildren.end()) {
            mParent->mChildren.erase(found);
        }
    }
}

void SceneNode::attachChild(SceneNode* child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}
SceneNode* SceneNode::detachChild(const SceneNode& node) {
    auto found = std::find_if(mChildren.begin(), mChildren.end(),
                              [&](SceneNode* p) -> bool { return p == &node; });
    assert(found != mChildren.end());

    SceneNode* result = std::move(*found);
    result->mParent   = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::enableArrow() { mIsNeedArrow = true; }
void SceneNode::disableArrow() { mIsNeedArrow = false; }

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);

    for (int i = 0; i < mChildren.size(); ++i) {
        SceneNode* child = mChildren[i];
        child->draw(target, states);
    }
}
void SceneNode::drawArrow(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    sf::Vector2f src = states.transform.transformPoint(0, 0);
    for (int i = 0; i < mChildren.size(); ++i) {
        SceneNode* child = mChildren[i];
        if (child->mIsNeedArrow) {
            sf::Vector2f translation = child->getTransform().transformPoint(0, 0);
            float length             = sqrt(translation.x * translation.x + translation.y * translation.y);
            if (length > 1) {
                sf::Vector2f unit = translation / length;
                float dist1       = mNode.getRadius() + mNode.getOutlineThickness();
                float dist2       = child->mNode.getRadius() + child->mNode.getOutlineThickness();
                drawArrow2Point(src + dist1 * unit,
                                src + translation - dist2 * unit, target);
            }
        }
        child->drawArrow(target, states);
    }
}
// sf::Transform states;
// states.translate();

// for (size_t index = 0; index < mCountNode; ++index) {
//     if (index > 0) {
//         sf::Vector2f src = states.transformPoint(0, 0);
//         states.translate(Constants::ShiftNode);
//         sf::Vector2f dest = states.transformPoint(0, 0);

//        float dist = Constants::CirleNodeRadius + Constants::NodeOutlineThinkness;
//        src.x += dist;
//        dest.x -= dist;
//        drawArrow(src, dest, target);
//    }
//    mList[index].draw(target, states);
//}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    mNode.draw(target, states);
}
