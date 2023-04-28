#pragma once
#include "Button.h"
#include <SFML/Graphics.hpp>

class BoxInput {
public:
    // Constructor
    BoxInput(std::string textConst = "i = ",
             std::string text      = "0",
             size_t lengthText     = 1,
             size_t minVal         = 0,
             size_t maxVal         = 9,
             float width           = 0,
             float height          = 0,
             sf::Vector2f position = sf::Vector2f(0, 0));

    // Set range value
    size_t getLengthText() const;
    void setMinValue(size_t minVal);
    void setMaxValue(size_t maxVal);
    void setRangeValue(size_t minVal, size_t maxVal);
    void setRandomValue();

    // Set size for BoxInput
    void setSize(sf::Vector2f size);
    void setSize(float x, float y);

    // Set position for BoxInput
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);

    // Holder
    void setHold(bool isHold);
    bool getHold() const;

    /* ---- Interact ---- */
    int getValue() const;
    // draw BoxInput on target
    virtual void draw(sf::RenderTarget& target);

private:
    void updateShape();
    void updateValue();

public:
    Button mBoxInput;
    Button mRandomButton;

private:
    float mWidth, mHeight;
    sf::Vector2f mPosition;
    size_t mLengthText;
    size_t mMinVal;
    size_t mMaxVal;
    bool mIsHold;
};

/*
    /// Row 2 (Box Input 1)
    // [input position][random]
    // Box Input 1 : [320..650] x [630..690]
    Button mBoxInput1;
    // Random Button 1 : [670..860] x [630..690]
    Button mRandomButton1;
*/