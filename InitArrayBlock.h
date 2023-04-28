#pragma once
#include "SFML/Graphics.hpp"
#include "Button.h"
#include "Vector.h"

class InitArrayBlock {
public:
	// Constructor
    InitArrayBlock(float width           = 1,
                   float height          = 1,
                   sf::Vector2f position = sf::Vector2f(0, 0));
    void setFileName(std::string fileName);

    // Set size for BoxInput
    void setSize(sf::Vector2f size);
    void setSize(float x, float y);

    // Set position for BoxInput
    void setPosition(sf::Vector2f position);
    void setPosition(float x, float y);

    /* --- Interact --- */
    Vector<int> getArray() const;
    // draw InitArrayBlock on target
    virtual void draw(sf::RenderTarget& target);
    void handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed);

private:
    void updateShape();
    void updateText(bool flagError = false);
    void randomArray();
    void readFromFile();

private:
    Button mBoxText;
    Button mRandomButton;
    Button mFileButton;

    float mWidth, mHeight;
    sf::Vector2f mPosition;

    Vector<int> mArr;
    std::string mFileName;
};
