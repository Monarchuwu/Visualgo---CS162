#include "ControlTable.h"
#include "Constants.h"

ControlTable::ControlTable(){
    mControlTableTheme.setSize(sf::Vector2f(900, 400));
    mControlTableTheme.setPosition(0, 500);
    mControlTableTheme.setFillColor(Constants::ControlTableThemeColor);

    for (int i = 0; i < 5; ++i) {
        mButtonMain[i].setSize(sf::Vector2f(280,75));
        mButtonMain[i].setPosition(10, 510 + 76 * i);
        mButtonMain[i].setFillColor(Constants::ButtonMainColor);

        mTextButtonMain[i].setFont(Constants::Font);
        mTextButtonMain[i].setStyle(sf::Text::Bold);
        mTextButtonMain[i].setCharacterSize(Constants::ButtonMainCharacterSize);
        mTextButtonMain[i].setFillColor(sf::Color::Black);
        mTextButtonMain[i].setString(mNameButtonMain[i]);
        sf::FloatRect rect = mTextButtonMain[i].getLocalBounds();
        int x              = rect.left + rect.width / 2;
        int y              = rect.top + rect.height / 2;
        mTextButtonMain[i].setOrigin(x, y);
        mTextButtonMain[i].setPosition(mButtonMain[i].getPosition() + mButtonMain[i].getSize() / 2.f);
    }

    mParameterTableTheme.setSize(sf::Vector2f(600, 380));
    mParameterTableTheme.setPosition(290, 510);
    mParameterTableTheme.setFillColor(Constants::ParameterTableThemeColor);
}

void ControlTable::draw(sf::RenderTarget& target) const {
    target.draw(mControlTableTheme);

    for (int i = 0; i < 5; ++i) {
        target.draw(mButtonMain[i]);
        target.draw(mTextButtonMain[i]);
    }

    target.draw(mParameterTableTheme);
}