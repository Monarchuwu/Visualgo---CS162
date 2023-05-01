#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Button.h"

class DataStructureButtonBlock {
public:
    DataStructureButtonBlock(sf::Vector2f position,
                             sf::Vector2f size);

    virtual void draw(sf::RenderTarget& target);
    int handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed);

public:
    Button mButtonDS[Constants::CountDataStructure];
};
