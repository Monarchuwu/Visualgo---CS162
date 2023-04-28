#include <fstream>
#include "InitArrayBlock.h"
#include "Constants.h"
#include "Random.h"

InitArrayBlock::InitArrayBlock(float width,
                               float height,
                               sf::Vector2f position)
    : mBoxText(),
      mRandomButton(),
      mFileButton(),
      mWidth(width),
      mHeight(height),
      mPosition(position) {

    mBoxText.setFillColor(Constants::BackGroundTextColor);
    mBoxText.setFont(Constants::Font);
    mBoxText.setStyle(sf::Text::Bold);
    mBoxText.setCharacterSize(Constants::ButtonMainCharacterSize);
    mBoxText.setTextFillColor(sf::Color::Black);
    mBoxText.setTextConst("arr = ");
    mBoxText.setText("empty");

    mRandomButton.setFillColor(Constants::BackGroundTextColor);
    mRandomButton.setFont(Constants::Font);
    mRandomButton.setStyle(sf::Text::Bold);
    mRandomButton.setCharacterSize(Constants::ButtonMainCharacterSize);
    mRandomButton.setTextFillColor(sf::Color::Black);
    mRandomButton.setText("Rand");

    mFileButton.setFillColor(Constants::BackGroundTextColor);
    mFileButton.setFont(Constants::Font);
    mFileButton.setStyle(sf::Text::Bold);
    mFileButton.setCharacterSize(Constants::ButtonMainCharacterSize);
    mFileButton.setTextFillColor(sf::Color::Black);
    mFileButton.setText("File");

    updateShape();
}
void InitArrayBlock::setFileName(std::string fileName) { mFileName = fileName; }

void InitArrayBlock::setSize(sf::Vector2f size) { setSize(size.x, size.y); }
void InitArrayBlock::setSize(float x, float y) {
    mWidth = x, mHeight = y;
    updateShape();
}

void InitArrayBlock::setPosition(sf::Vector2f position) {
    mPosition = position;
    updateShape();
}
void InitArrayBlock::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }

Vector<int> InitArrayBlock::getArray() const {
    return mArr;
}

void InitArrayBlock::draw(sf::RenderTarget& target) {
    mBoxText.draw(target);
    mRandomButton.draw(target);
    mFileButton.draw(target);
}

void InitArrayBlock::handleButtonInput(sf::Event::MouseButtonEvent mouse, bool isPressed) {
    if (mouse.button == sf::Mouse::Left && !isPressed) {
        if (mRandomButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            randomArray();
        }
        if (mFileButton.getGlobalBounds().contains(mouse.x, mouse.y)) {
            readFromFile();
        }
    }
}

void InitArrayBlock::updateShape() {
    if (mWidth < 1 || mHeight < 1) {
        mWidth = mHeight = 1;
    }
    // 540 x 110
    float scaleX = mWidth / 540;
    float scaleY = mHeight / 110;
    mBoxText.setSize(sf::Vector2f(mWidth, 50 * scaleY));
    mRandomButton.setSize(sf::Vector2f(265 * scaleX, 50 * scaleY));
    mFileButton.setSize(sf::Vector2f(265 * scaleX, 50 * scaleY));

    mBoxText.setPosition(mPosition);
    mRandomButton.setPosition(mPosition + sf::Vector2f(0, 60 * scaleY));
    mFileButton.setPosition(mPosition + sf::Vector2f((mWidth - 265) * scaleX, 60 * scaleY));
}

void InitArrayBlock::updateText(bool flagError) {
    std::string text("");
    if (flagError) { text = "Error, sample array: \"12 23 34\""; }
    else if (mArr.size() == 0) { text = "empty"; }
    else {
        for (int i = 0; i < mArr.size(); ++i) {
            text += (i == 0 ? "" : ",") + std::to_string(mArr[i]);
        }
    }
    mBoxText.setText(text);
}

void InitArrayBlock::randomArray() {
    int countNode = Random::Rand(0, Constants::MaxCountNode);
    mArr.clear();
    mArr.reserve(countNode);

    for (int i = 0; i < countNode; ++i) {
        mArr.push_back(Random::Rand());
    }
    updateText();
}

void InitArrayBlock::readFromFile() {
    std::ifstream fi(mFileName, std::ios::in);
    mArr.clear();

    bool flagError = false;
    std::string str;
    while (mArr.size() < Constants::MaxCountNode && fi >> str) {
        for (int i = 0; i < str.size(); ++i) {
            if (!std::isdigit(str[i])) {
                flagError = true;
                break;
            }
        }
        if (flagError) break;

        if (str.size() > 2) mArr.push_back(99);
        else {
            int val = std::stoi(str);
            if (val < 0) val = 0;
            mArr.push_back(val);
        }
    }
    updateText(flagError);

    fi.close();
}