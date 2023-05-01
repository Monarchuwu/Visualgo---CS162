#include "SceneNode.h"
#include "Arrow.h"
#include <cassert>

SceneNode::SceneNode(BasicNode node,
                     bool doubleHeadedArrow,
                     bool reverseArrow,
                     bool arrowVisible)
    : mNode(node),
      mDoubleHeadedArrow(doubleHeadedArrow),
      mReverseArrow(reverseArrow),
      mArrowVisible(arrowVisible),
      mParent(nullptr) {
}
SceneNode::~SceneNode() {
    if (mChildren) {
        delete mChildren;
    }

    if (mParent) {
        mParent->mChildren = nullptr;
    }
}

void SceneNode::attachChild(SceneNode* child) {
    if (mChildren != nullptr) delete mChildren;

    child->mParent = this;
    mChildren      = child;
}
SceneNode* SceneNode::detachChild() {
    if (mChildren == nullptr) return nullptr;

    SceneNode* result = mChildren;
    result->mParent   = nullptr;
    mChildren         = nullptr;
    return result;
}

void SceneNode::enableArrow() { mArrowVisible = true; }
void SceneNode::disableArrow() { mArrowVisible = false; }

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);

    if (mChildren) {
        mChildren->draw(target, states);
    }
}
void SceneNode::drawArrow(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();

    sf::Vector2f src = states.transform.transformPoint(0, 0);
    if (mChildren) {
        if (mChildren->mArrowVisible) {
            sf::Vector2f translation = mChildren->getTransform().transformPoint(0, 0);
            float length             = sqrt(translation.x * translation.x + translation.y * translation.y);
            if (length > 1) {
                sf::Vector2f unit = translation / length;
                float dist1       = mNode.getRadius() + mNode.getOutlineThickness();
                float dist2       = mChildren->mNode.getRadius() + mChildren->mNode.getOutlineThickness();
                if (mChildren->mDoubleHeadedArrow) {
                    drawArrow2Head2Point(src + dist1 * unit,
                                         src + translation - dist2 * unit, target);
                }
                else if (mChildren->mReverseArrow) {
                    drawArrow2Point(src + translation - dist2 * unit,
                                    src + dist1 * unit, target);
                }
                else {
                    drawArrow2Point(src + dist1 * unit,
                                    src + translation - dist2 * unit, target);
                }
            }
        }
        mChildren->drawArrow(target, states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    mNode.draw(target, states);
}
