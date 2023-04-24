#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "CircleShape.h"

class ControlTable {
    // [0..900] x [500..900]
public:
    ControlTable();
    virtual void draw(sf::RenderTarget& target);
    void handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed);
    void handleKeyInput(sf::Event::KeyEvent mouse);

private:
    void FixValueBoxInputPosition();

private:
    /// Main
    // Theme : [0..900] x [500..900]
    sf::RectangleShape mControlTableTheme;

    /// Button List
    // ButtonMain : [10..290] x [510..585] + [0][76] per button
    // return: what button is being selected
    Button mButtonMain[5];
    // NameButtonMain
    std::string mNameButtonMain[5] = {
        "Create",
        "Search",
        "Update",
        "Insert",
        "Remove"
    };

    /// Parameter Table
    // Theme : [290..890] x [510..890]
    sf::RectangleShape mParameterTableTheme;
    /// Row 1 (Select Position)
    // Select Position to Insert/Delete : [395..785] x [530..590]
    // Display: <Beginning (i = 0), Middle (i = 1..n-1), End (i = n)>
    Button mSelectPosition;
    // Triangle in the Left of mSelectPosition : [(355, 560), 30]
    CircleShape mTriangleLeft;
    // Triangle in the Right of mSelectPosition : [(825, 560), 30]
    CircleShape mTriangleRight;
    /// Row 2 (Box Input 1)
    // [input position][random]
    // Box Input 1 : [320..650] x [630..690]
    Button mBoxInput1;
    // Random Button 1 : [670..860] x [630..690]
    Button mRandomButton1;
    /// Row 3 (Box Input 2)
    // [input value][random]
    // Box Input 2 : [320..650] x [710..770]
    Button mBoxInput2;
    // Random Button 2 : [670..860] x [710..770]
    Button mRandomButton2;

    /// Row 4 (Play Button)
    // Play Button : [320..860] x [810..870]
    // Display: <Play>
    // Change to <Unavailable> when animation is being played
    Button mPlay;
};