#include "ControlTable.h"
#include "Constants.h"
#include "Random.h"

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

    mBoxInput1.setSize(sf::Vector2f(330, 60));
    mBoxInput1.setPosition(320, 630);
    mBoxInput1.setFillColor(Constants::BackGroundTextColor);
    mBoxInput1.setFont(Constants::Font);
    mBoxInput1.setStyle(sf::Text::Bold);
    mBoxInput1.setCharacterSize(Constants::ButtonMainCharacterSize);
    mBoxInput1.setTextFillColor(sf::Color::Black);
    mBoxInput1.setTextConst("i = ");
    mBoxInput1.setText("0");

    mRandomButton1.setSize(sf::Vector2f(190, 60));
    mRandomButton1.setPosition(670, 630);
    mRandomButton1.setFillColor(Constants::BackGroundTextColor);
    mRandomButton1.setFont(Constants::Font);
    mRandomButton1.setStyle(sf::Text::Bold);
    mRandomButton1.setCharacterSize(Constants::ButtonMainCharacterSize);
    mRandomButton1.setTextFillColor(sf::Color::Black);
    mRandomButton1.setText("Random");

    mBoxInput2.setSize(sf::Vector2f(330, 60));
    mBoxInput2.setPosition(320, 710);
    mBoxInput2.setFillColor(Constants::BackGroundTextColor);
    mBoxInput2.setFont(Constants::Font);
    mBoxInput2.setStyle(sf::Text::Bold);
    mBoxInput2.setCharacterSize(Constants::ButtonMainCharacterSize);
    mBoxInput2.setTextFillColor(sf::Color::Black);
    mBoxInput2.setTextConst("v = ");
    mBoxInput2.setText("0");

    mRandomButton2.setSize(sf::Vector2f(190, 60));
    mRandomButton2.setPosition(670, 710);
    mRandomButton2.setFillColor(Constants::BackGroundTextColor);
    mRandomButton2.setFont(Constants::Font);
    mRandomButton2.setStyle(sf::Text::Bold);
    mRandomButton2.setCharacterSize(Constants::ButtonMainCharacterSize);
    mRandomButton2.setTextFillColor(sf::Color::Black);
    mRandomButton2.setText("Random");

    mPlay.setSize(sf::Vector2f(540, 60));
    mPlay.setPosition(320, 810);
    mPlay.setFillColor(Constants::BackGroundTextColor);
    mPlay.setFont(Constants::Font);
    mPlay.setStyle(sf::Text::Bold);
    mPlay.setCharacterSize(Constants::ButtonMainCharacterSize);
    mPlay.setTextFillColor(sf::Color::Black);
    mPlay.setText("Play");
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
    // Box Input 1 (Row 2)
    mBoxInput1.draw(target);
    mRandomButton1.draw(target);
    // Box Input 2 (Row 3)
    mBoxInput2.draw(target);
    mRandomButton2.draw(target);
    // Play Button (Row 4)
    mPlay.draw(target);
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

        FixValueBoxInputPosition();
    }

    // Box Input (Row 2 + 3)
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        mBoxInput1.setFillColor(Constants::BackGroundTextColor);
        mBoxInput2.setFillColor(Constants::BackGroundTextColor);
        bool flag = true;

        // Box Input Position (Row 2)
        if (mRandomButton1.getGlobalBounds().contains(mouse.x, mouse.y)) {
            Constants::updateBoxInputPositionValue();
            mBoxInput1.setText(std::to_string(
                Random::Rand(Constants::BoxInputPositionMinVal,
                             Constants::BoxInputPositionMaxVal)));
        }
        if (mBoxInput1.getGlobalBounds().contains(mouse.x, mouse.y)) {
            Constants::BoxInputHolder = &mBoxInput1;
            flag                      = false;
        }

        // Box Input Value (Row 3)
        if (mRandomButton2.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mBoxInput2.setText(std::to_string(Random::Rand()));
        }
        if (mBoxInput2.getGlobalBounds().contains(mouse.x, mouse.y)) {
            // Fix value of Box Input Position
            if (Constants::BoxInputHolder == &mBoxInput1) {
                FixValueBoxInputPosition();
            }
            Constants::BoxInputHolder = &mBoxInput2;
            flag                      = false;
        }

        if (flag && Constants::BoxInputHolder != nullptr) {
            // Fix value of Box Input Position
            if (Constants::BoxInputHolder == &mBoxInput1) {
                FixValueBoxInputPosition();
            }
            Constants::BoxInputHolder = nullptr;
        }
        if (Constants::BoxInputHolder != nullptr) {
            Constants::BoxInputHolder->setFillColor(Constants::BackGroundTextColorHold);
        }
    }

    // Play Button (Row 4)
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        if (mPlay.getGlobalBounds().contains(mouse.x, mouse.y)) {
            // play animation
        }
    }
}

void ControlTable::handleKeyInput(sf::Event::KeyEvent key) {
    bool isNum    = sf::Keyboard::Num0 <= key.code && key.code <= sf::Keyboard::Num9;
    bool isNumPad = sf::Keyboard::Numpad0 <= key.code && key.code <= sf::Keyboard::Numpad9;
    bool isDigit  = isNum || isNumPad;
    if (Constants::BoxInputHolder != nullptr && isDigit) {
        int limitLength = 100;
        if (Constants::BoxInputHolder == &mBoxInput1) limitLength = 1;
        if (Constants::BoxInputHolder == &mBoxInput2) limitLength = 2;

        std::string str = Constants::BoxInputHolder->getText();
        str += char(key.code - (isNum ? sf::Keyboard::Num0 : sf::Keyboard::Numpad0) + '0');
        if (str.length() > limitLength) str.erase(str.begin());
        Constants::BoxInputHolder->setText(str);
    }
}

void ControlTable::FixValueBoxInputPosition() {
    Constants::updateBoxInputPositionValue();
    size_t pos = std::stoi("0" + mBoxInput1.getText());
    if (pos < Constants::BoxInputPositionMinVal) pos = Constants::BoxInputPositionMinVal;
    else if (pos > Constants::BoxInputPositionMaxVal) pos = Constants::BoxInputPositionMaxVal;
    mBoxInput1.setText(std::to_string(pos));
}
