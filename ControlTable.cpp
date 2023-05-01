#include "ControlTable.h"
#include "Constants.h"
#include "Random.h"

ControlTable::ControlTable(Carrier &carrier)
    : mCarrier(carrier),
      mBoxInputPos("i = ", "0", 1),
      mBoxInputVal("v = ", "0", 2, 0, 99) {
    mControlTableTheme.setSize(sf::Vector2f(900, 400));
    mControlTableTheme.setPosition(0, 500);
    mControlTableTheme.setFillColor(Constants::ControlTableThemeColor);

    mParameterTableTheme.setSize(sf::Vector2f(600, 360));
    mParameterTableTheme.setPosition(290, 530);
    mParameterTableTheme.setFillColor(Constants::ParameterTableThemeColor);

    mInitBlock.setSize(540, 110);
    mInitBlock.setPosition(320, 550);
    mInitBlock.setFileName("initSLL.txt");

    mSelectPosition.setSize(530, 50);
    mSelectPosition.setPosition(325, 680);

    mBoxInputPos.setSize(260, 50);
    mBoxInputPos.setPosition(320, 750);

    mBoxInputVal.setSize(260, 50);
    mBoxInputVal.setPosition(600, 750);

    mPlay.setSize(sf::Vector2f(540, 50));
    mPlay.setPosition(320, 820);
    mPlay.setFillColor(Constants::BackGroundTextColor);
    mPlay.setFont(Constants::Font);
    mPlay.setStyle(sf::Text::Bold);
    mPlay.setCharacterSize(Constants::ButtonMainCharacterSize);
    mPlay.setTextFillColor(sf::Color::Black);
    mPlay.setText("Play");
}

void ControlTable::setButtonMainList(Vector<int> &list) {
    mButtonMainList = list;
    mButtonMain.reserve(mButtonMainList.size());

    // [10..290] x [530..890]
    int stepY = (890 - 530) / mButtonMainList.size();
    for (int i = 0; i < mButtonMainList.size(); ++i) {
        Button button;
        button.setID(mButtonMainList[i]);
        button.setSize(sf::Vector2f(280, stepY - 1));
        button.setPosition(10, 530 + stepY * i);
        button.setFillColor(Constants::ButtonMainColor);
        button.setFont(Constants::Font);
        button.setStyle(sf::Text::Bold);
        button.setCharacterSize(Constants::ButtonMainCharacterSize);
        button.setTextFillColor(sf::Color::Black);
        button.setText(Constants::OperationText[mButtonMainList[i]]);
        mButtonMain.push_back(button);
    }
    setOperationType(mButtonMainList[0]);
}

void ControlTable::setSelectPositionList(Vector<int>& list) {
    mSelectPosition.setSelectPositionList(list);
}

void ControlTable::draw(sf::RenderTarget& target) {
    target.draw(mControlTableTheme);

    /// Button Main
    for (int i = 0; i < mButtonMain.size(); ++i) {
        if (mButtonMain[i].getID() == mOperationType) {
            mButtonMain[i].setFillColor(Constants::ButtonMainColorClicked);
        }
        else {
            mButtonMain[i].setFillColor(Constants::ButtonMainColor);
        }
        mButtonMain[i].draw(target);
    }

    /// Parameter Table
    target.draw(mParameterTableTheme);
    // Init Block (Row 0)
    mInitBlock.draw(target);
    // Position Row (Row 1)
    mSelectPosition.draw(target);
    // Box Input 1 (Row 2)
    mBoxInputPos.draw(target);
    // Box Input 2 (Row 3)
    mBoxInputVal.draw(target);
    // Play Button (Row 4)
    mPlay.draw(target);
}

void ControlTable::handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed) {
    // Main Button
    if (mouse.button == sf::Mouse::Left && isPressed) {
        int temp = -1;
        for (int i = 0; i < mButtonMain.size(); ++i) {
            if (mButtonMain[i].getGlobalBounds().contains(mouse.x, mouse.y)) {
                temp = mButtonMain[i].getID();
            }
        }
        if (temp != -1) {
            if (mOperationType != temp) {
                setOperationType(temp);
            }
            return;
        }
    }

    // Init Array Block (Row 0)
    mInitBlock.handleButtonInput(mouse, isPressed);

    // Position Row (Row 1)
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        if (mSelectPosition.mTriangleLeft.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mSelectPosition.updateType(-1);
        }
        if (mSelectPosition.mTriangleRight.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mSelectPosition.updateType(1);
        }
        SetRangeValueBoxInputPosition();
    }

    // Box Input (Row 2 + 3)
    if (mouse.button == sf::Mouse::Left && !isPressed) {

        // Box Input Position (Row 2)
        if (mBoxInputPos.mRandomButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            SetRangeValueBoxInputPosition();
            mBoxInputPos.setRandomValue();
        }
        if (mBoxInputPos.mBoxInput.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mBoxInputPos.setHold(true);
        }
        else {
            SetRangeValueBoxInputPosition();
            mBoxInputPos.setHold(false);
        }

        // Box Input Value (Row 3)
        if (mBoxInputVal.mRandomButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mBoxInputVal.setRandomValue();
        }
        if (mBoxInputVal.mBoxInput.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mBoxInputVal.setHold(true);
        }
        else {
            mBoxInputVal.setHold(false);
        }
    }

    // Play Button (Row 4)
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        if (mPlay.getGlobalBounds().contains(mouse.x, mouse.y)) {
            mCarrier.mOperationType = mOperationType;
            mCarrier.mArr           = mInitBlock.getArray();
            mCarrier.mPos           = mBoxInputPos.getValue();
            mCarrier.mVal           = mBoxInputVal.getValue();
            mCarrier.mPlayIsPressed = true;
        }
    }
}

void ControlTable::handleKeyInput(sf::Event::KeyEvent key) {
    bool isNum    = sf::Keyboard::Num0 <= key.code && key.code <= sf::Keyboard::Num9;
    bool isNumPad = sf::Keyboard::Numpad0 <= key.code && key.code <= sf::Keyboard::Numpad9;
    bool isDigit  = isNum || isNumPad;

    if (isDigit && mBoxInputPos.getHold()) {
        int limitLength = mBoxInputPos.getLengthText();
        std::string str = mBoxInputPos.mBoxInput.getText();
        str += char(key.code - (isNum ? sf::Keyboard::Num0 : sf::Keyboard::Numpad0) + '0');
        if (str.length() > limitLength) str.erase(str.begin());
        mBoxInputPos.mBoxInput.setText(str);
    }

    if (isDigit && mBoxInputVal.getHold()) {
        int limitLength = mBoxInputVal.getLengthText();
        std::string str = mBoxInputVal.mBoxInput.getText();
        str += char(key.code - (isNum ? sf::Keyboard::Num0 : sf::Keyboard::Numpad0) + '0');
        if (str.length() > limitLength) str.erase(str.begin());
        mBoxInputVal.mBoxInput.setText(str);
    }
}

void ControlTable::setOperationType(int type) {
    mOperationType = type;
    Vector<int> list;
    for (int i = 0; i < 7; ++i) {
        if (Constants::SelectPosList[type] >> i & 1) {
            list.push_back(i);
        }
    }
    setSelectPositionList(list);
}
void ControlTable::SetRangeValueBoxInputPosition() {
    int mi = 0;
    int ma = 0;
    int pos = 0;
    switch (mSelectPosition.getPositionType()) {
        case Constants::Position::Beginning_0:
            pos = 0;
            mBoxInputPos.setRangeValue(pos, pos);
            break;

        case Constants::Position::Middle_0_n1:
            mi = 0;
            ma = (int)mCarrier.mCountNode - 1;
            if (ma < mi) ma = mi;
            mBoxInputPos.setMinValue(mi);
            mBoxInputPos.setMaxValue(ma);
            break;

        case Constants::Position::Middle_0_n:
            mi = 0;
            ma = (int)mCarrier.mCountNode;
            if (ma < mi) ma = mi;
            mBoxInputPos.setMinValue(mi);
            mBoxInputPos.setMaxValue(ma);
            break;

        case Constants::Position::Middle_1_n1:
            mi = 1;
            ma = (int)mCarrier.mCountNode - 1;
            if (ma < mi) ma = mi;
            mBoxInputPos.setMinValue(mi);
            mBoxInputPos.setMaxValue(ma);
            break;

        case Constants::Position::Middle_1_n2:
            mi = 1;
            ma = (int)mCarrier.mCountNode - 2;
            if (ma < mi) ma = mi;
            mBoxInputPos.setMinValue(mi);
            mBoxInputPos.setMaxValue(ma);
            break;

        case Constants::Position::End_n1:
            pos = (int)mCarrier.mCountNode - 1;
            if (pos < 0) pos = 0;
            mBoxInputPos.setRangeValue(pos, pos);
            break;

        case Constants::Position::End_n:
            pos = (int)mCarrier.mCountNode;
            if (pos < 0) pos = 0;
            mBoxInputPos.setRangeValue(pos, pos);
            break;

        default:
            break;
    }
}
