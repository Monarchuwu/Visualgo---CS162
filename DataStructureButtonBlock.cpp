#include "DataStructureButtonBlock.h"

DataStructureButtonBlock::DataStructureButtonBlock(
    sf::Vector2f position,
    sf::Vector2f size) {
    for (int i = 0; i < Constants::CountDataStructure; ++i) {
        mButtonDS[i].setID(i);
        mButtonDS[i].setSize(size + sf::Vector2f(-1, 0));
        mButtonDS[i].setPosition(position + sf::Vector2f(size.x * i, 0));
        mButtonDS[i].setFillColor(Constants::ButtonMainColor);
        mButtonDS[i].setFont(Constants::Font);
        mButtonDS[i].setStyle(sf::Text::Bold);
        mButtonDS[i].setCharacterSize(Constants::ButtonMainCharacterSize);
        mButtonDS[i].setTextFillColor(sf::Color::Black);
        mButtonDS[i].setText(Constants::DataStructureText[i]);
    }
}

void DataStructureButtonBlock::draw(sf::RenderTarget& target) {
    for (int i = 0; i < Constants::CountDataStructure; ++i) {
        mButtonDS[i].draw(target);
    }
}

int DataStructureButtonBlock::handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed) {
    int temp = -1;
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        for (int i = 0; i < Constants::CountDataStructure; ++i) {
            if (mButtonDS[i].getGlobalBounds().contains(mouse.x, mouse.y)) {
                temp = mButtonDS[i].getID();
            }
        }
    }
    return temp;
}