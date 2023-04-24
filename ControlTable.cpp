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
}

void ControlTable::draw(sf::RenderTarget& target) {
    target.draw(mControlTableTheme);

    for (int i = 0; i < 5; ++i) {
        if (mButtonMain[i].getID() == Constants::OperationType) {
            mButtonMain[i].setFillColor(Constants::ButtonMainColorClicked);
        }
        else {
            mButtonMain[i].setFillColor(Constants::ButtonMainColor);
        }
        mButtonMain[i].draw(target);
    }

    target.draw(mParameterTableTheme);
}

void ControlTable::handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed) {
    if (mouse.button == sf::Mouse::Left && isPressed) {
        Constants::OperationType = -1;
        for (int i = 0; i < 5; ++i) {
            if (mButtonMain[i].getGlobalBounds().contains(mouse.x, mouse.y)) {
                Constants::OperationType = mButtonMain[i].getID();
            }
        }
    }
}