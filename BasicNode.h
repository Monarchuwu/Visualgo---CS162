#pragma once
#include <SFML/Graphics.hpp>
#include "CircleShape.h"
#include "Constants.h"

class BasicNode {
public:
    /* --- Constructors --- */
    // Constructor
    BasicNode(float radius           = Constants::CirleNodeRadius,
              float outlineThickness = Constants::NodeOutlineThinkness,
              int val                = -1);

    /* ---- Set Color ---- */

    void setFillColorBody(sf::Color& color);
    void setFillColorText(sf::Color& color);
    void setOutlineColor(sf::Color& color);

    /* ----- Detail ----- */

    void setRadius(float radius);
    void setOutlineThickness(float outlineThickness);
    float getRadius() const;
    float getOutlineThickness() const;

    /* ---- Update Value ---- */
    // set value in Node
    void setValue(int value);
    // return the value in Node
    int getValue() const;
    // set text in Node
    void setText(std::string text = "");
    // return the text in Node
    std::string getText() const;

    /* ----- Interact ----- */
    // draw Node on target
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
private:
    CircleShape mBody;
    sf::Text mText;
    int mValue;
    std::string mStrText;
};