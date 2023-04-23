#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "BasicNode.h"

class BasicList {
public:
    BasicList(size_t countNode = 0);
    virtual void draw(sf::RenderTarget& target) const;
    // virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    void update();

private:
    size_t mCountNode;
    std::vector<BasicNode> mList;
    sf::Vector2f mStartingPosition; // the position of the first node
};
