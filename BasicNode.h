#pragma once
#include <SFML/Graphics.hpp>
#include "CircleShape.h"
#include "Constants.h"

class BasicNode {
public:
    /* --- Constructors --- */
    // Constructor
    BasicNode(float radius,
              float outlineThickness,
              size_t pointCount,
              float initAngle,
              int val = -1);

    /* ------ Color ------ */

    void setFillColorBody(sf::Color& color);
    void setFillColorText(sf::Color& color);
    void setFillColorTextBelow(sf::Color& color);
    void setOutlineColor(sf::Color& color);
    sf::Color getFillColorBody() const;
    sf::Color getFillColorText() const;
    sf::Color getFillColorTextBelow() const;
    sf::Color getOutlineColor() const;

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
    // set text below the Node
    void setTextBelow(std::string text = "");
    // return the text below the Node
    std::string getTextBelow() const;

    /* ----- Interact ----- */
    // draw Node on target
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;

private:
    CircleShape mBody;
    sf::Text mText;
    sf::Text mTextBelow;
    int mValue;
    std::string mStrText;
};