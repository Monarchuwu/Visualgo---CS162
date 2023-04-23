#include "BasicList.h"
#include "Arrow.h"
#include "Constants.h"

BasicList::BasicList(size_t countNode)
    : mCountNode(countNode),
      mList(),
      mStartingPosition() {
    update();
}

void BasicList::update() {
    if (mCountNode > Constants::MaxCountNode) {
        mCountNode = Constants::MaxCountNode;
    }
    mList.resize(mCountNode);
    mStartingPosition = Constants::MidPointSceneVisual;
    if (mCountNode > 0) {
        mStartingPosition.x -= (mCountNode - 1) * Constants::ShiftNode.x / 2;
    }
}

void BasicList::draw(sf::RenderTarget& target) const {
    sf::Transform states;
    states.translate(mStartingPosition);

    for (size_t index = 0; index < mCountNode; ++index) {
        if (index > 0) {
            sf::Vector2f src = states.transformPoint(0, 0);
            states.translate(Constants::ShiftNode);
            sf::Vector2f dest = states.transformPoint(0, 0);

            float dist = Constants::CirleNodeRadius + Constants::NodeOutlineThinkness;
            src.x += dist;
            dest.x -= dist;
            drawArrow(src, dest, target);
        }
        mList[index].draw(target, states);
    }
}