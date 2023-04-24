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
    // Select Position to Insert/Delete : [395..785] x [530..590]
    // Display: <Beginning (i = 0), Middle (i = 1..n-1), End (i = n)>
    Button mSelectPosition;
    // Triangle in the Left of mSelectPosition : [(355, 560), 30]
    CircleShape mTriangleLeft;
    // Triangle in the Right of mSelectPosition : [(825, 560), 30]
    CircleShape mTriangleRight;
    // [input position][random]
    // [input  value  ][random]
    // [Play] (change to [Unavailable] when animation is begin played) <=> Enter
};