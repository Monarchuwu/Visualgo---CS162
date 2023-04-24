#include "ControlTable.h"
#include "Constants.h"

ControlTable::ControlTable() {
    mControlTableTheme.setSize(sf::Vector2f(900, 400));
    mControlTableTheme.setPosition(0, 500);
    mControlTableTheme.setFillColor(Constants::ControlTableThemeColor);

    for (int i = 0; i < 5; ++i) {
        mButtonMain[i].setID(i);
        mButtonMain[i].setSize(sf::Vector2f(280, 75));
        mButtonMain[i].setPosition(10, 510 + 76 * i);
        mButtonMain[i].setFillColor(Constants::ButtonMainColor);
        mButtonMain[i].setFont(Constants::Font);
        mButtonMain[i].setStyle(sf::Text::Bold);
        mButtonMain[i].setCharacterSize(Constants::ButtonMainCharacterSize);
        mButtonMain[i].setTextFillColor(sf::Color::Black);
        mButtonMain[i].setText(mNameButtonMain[i]);
    }

    mParameterTableTheme.setSize(sf::Vector2f(600, 380));
    mParameterTableTheme.setPosition(290, 510);
    mParameterTableTheme.setFillColor(Constants::ParameterTableThemeColor);

    mSelectPosition.setSize(sf::Vector2f(390, 60));
    mSelectPosition.setPosition(395, 530);
    mSelectPosition.setFillColor(Constants::BackGroundTextColor);
    mSelectPosition.setFont(Constants::Font);
    mSelectPosition.setStyle(sf::Text::Bold);
    mSelectPosition.setCharacterSize(Constants::ButtonMainCharacterSize);
    mSelectPosition.setTextFillColor(sf::Color::Black);
    mSelectPosition.setText(Constants::PositionText[0]);

    mTriangleLeft.setPointCount(3);
    mTriangleLeft.setRadius(30);
    mTriangleLeft.setInitAngle(3.141592654f); // pi
    mTriangleLeft.setPosition(355, 560);
    mTriangleLeft.setFillColor(Constants::BackGroundTextColor);

    mTriangleRight.setPointCount(3);
    mTriangleRight.setRadius(30);
    mTriangleRight.setInitAngle(0);
    mTriangleRight.setPosition(825, 560);
    mTriangleRight.setFillColor(Constants::BackGroundTextColor);
}

void ControlTable::draw(sf::RenderTarget& target) {
    target.draw(mControlTableTheme);

    /// Button Main
    for (int i = 0; i < 5; ++i) {
        if (mButtonMain[i].getID() == Constants::OperationType) {
            mButtonMain[i].setFillColor(Constants::ButtonMainColorClicked);
        }
        else {
            mButtonMain[i].setFillColor(Constants::ButtonMainColor);
        }
        mButtonMain[i].draw(target);
    }

    /// Parameter Table
    target.draw(mParameterTableTheme);
    // Position Row (Row 1)
    mSelectPosition.draw(target);
    target.draw(mTriangleLeft);
    target.draw(mTriangleRight);
}

void ControlTable::handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed) {
    // Main Button
    if (mouse.button == sf::Mouse::Left && isPressed) {
        int temp = -1;
        for (int i = 0; i < 5; ++i) {
            if (mButtonMain[i].getGlobalBounds().contains(mouse.x, mouse.y)) {
                Constants::OperationType = mButtonMain[i].getID();
            }
        }
        if (temp != -1) {
            Constants::OperationType = temp;
            return;
        }
    }

    // Position Row (Row 1)
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        int temp = 0;
        if (mTriangleLeft.getGlobalBounds().contains(mouse.x, mouse.y)) temp -= 1;
        if (mTriangleRight.getGlobalBounds().contains(mouse.x, mouse.y)) temp += 1;
        (Constants::PositionType += 3 + temp) %= 3;
        mSelectPosition.setText(Constants::PositionText[Constants::PositionType]);
    }
}