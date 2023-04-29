#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BasicNode.h"
#include "SceneNode.h"
#include "Carrier.h"

class BasicList {
public:
    BasicList(Carrier &carrier, size_t countNode = 0);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

    size_t getCountNode() const;

private:
    void update();

private:
    Carrier mCarrier;

    size_t mCountNode;
    std::vector<BasicNode> mList;
    sf::Vector2f mStartingPosition; // the position of the first node
};
