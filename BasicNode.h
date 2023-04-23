#pragma once
#include <SFML/Graphics.hpp>
#include "CircleShape.h"

class BasicNode {
public:
    BasicNode();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
    void updateValue(int value);
    void setText(std::string text = "");
    std::string getText() const;

private:
    CircleShape mBody;
    sf::Text mText;
    int mValue;
    std::string mStrText;
};