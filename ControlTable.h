#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "BoxInput.h"
#include "SelectPositionBlock.h"
#include "InitArrayBlock.h"
#include "Vector.h"
#include "CircleShape.h"
#include "Carrier.h"

class ControlTable {
    // [0..900] x [500..900]
public:
    ControlTable(Carrier &carrier);
    void setButtonMainList(int listOperation);
    void setButtonMainList(Vector<int> &list);
    void setSelectPositionList(Vector<int> &selectPosition);

    virtual void draw(sf::RenderTarget& target);
    void handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed);
    void handleKeyInput(sf::Event::KeyEvent mouse);

private:
    // update OperationType and update SelectionPositionBlock
    void setOperationType(int type);
    void SetRangeValueBoxInputPosition(); // must change

private:
    Carrier &mCarrier;

    /// Main
    // Theme : [0..900] x [500..900]
    sf::RectangleShape mControlTableTheme;

    /// Button List
    Vector<Button> mButtonMain;
    Vector<int> mButtonMainList;
    // return what button is being selected
    int mOperationType;

    /// Parameter Table
    // Theme
    sf::RectangleShape mParameterTableTheme;

    /// Row 0 (Init Array)
    // Init Block
    InitArrayBlock mInitBlock;

    /// Row 1 (Select Position)
    // Select Position Block
    SelectPositionBlock mSelectPosition;

    /// Row 2 (Box Input Pos)
    // [input position][random]
    BoxInput mBoxInputPos;

    /// Row 3 (Box Input Val)
    // [input value][random]
    BoxInput mBoxInputVal;

    /// Row 4 (Play Button)
    // Play Button : Play Animation
    // Change to <Unavailable> when animation is being played
    Button mPlay;
};