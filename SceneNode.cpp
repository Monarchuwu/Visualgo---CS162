#include "SceneNode.h"
#include <cassert>

SceneNode::SceneNode()
    : mNode(),
      mParent(nullptr) {
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

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    drawCurrent(target, states);

    for (int i = 0; i < mChildren.size(); ++i) {
        SceneNode* child = mChildren[i];
        child->draw(target, states);
    }
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const {
    mNode.draw(target, states);
}
