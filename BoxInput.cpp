#include "BoxInput.h"
#include "Constants.h"
#include "Random.h"

BoxInput::BoxInput(std::string textConst,
                   std::string text,
                   size_t lengthText,
                   size_t minVal,
                   size_t maxVal,
                   float width,
                   float height,
                   sf::Vector2f position)
    : mBoxInput(),
      mRandomButton(),
      mLengthText(lengthText),
      mMinVal(minVal),
      mMaxVal(maxVal),
      mWidth(width),
      mHeight(height),
      mPosition(position),
      mIsHold(false) {
    mBoxInput.setFont(Constants::Font);
    mBoxInput.setStyle(sf::Text::Bold);
    mBoxInput.setCharacterSize(Constants::ButtonMainCharacterSize);
    mBoxInput.setTextFillColor(sf::Color::Black);
    mBoxInput.setTextConst(textConst);
    mBoxInput.setText(text);

    mRandomButton.setFillColor(Constants::BackGroundTextColor);
    mRandomButton.setFont(Constants::Font);
    mRandomButton.setStyle(sf::Text::Bold);
    mRandomButton.setCharacterSize(Constants::ButtonMainCharacterSize);
    mRandomButton.setTextFillColor(sf::Color::Black);
    mRandomButton.setText("Rand");

    updateShape();
}

size_t BoxInput::getLengthText() const { return mLengthText; }
void BoxInput::setMinValue(size_t minVal) { 
    mMinVal = minVal;
    updateValue();
}
void BoxInput::setMaxValue(size_t maxVal) {
    mMaxVal = maxVal;
    updateValue();
}
void BoxInput::setRangeValue(size_t minVal, size_t maxVal) {
    mMinVal = minVal;
    mMaxVal = maxVal;
    updateValue();
}
void BoxInput::updateValue() {
    size_t val = std::stoi("0" + mBoxInput.getText());
    if (val < mMinVal) val = mMinVal;
    else if (val > mMaxVal) val = mMaxVal;
    mBoxInput.setText(std::to_string(val));
}
void BoxInput::setRandomValue() {
    mBoxInput.setText(std::to_string(Random::Rand(mMinVal, mMaxVal)));
}

void BoxInput::setSize(sf::Vector2f size) { setSize(size.x, size.y); }
void BoxInput::setSize(float x, float y) {
    mWidth = x, mHeight = y;
    updateShape();
}

void BoxInput::setPosition(sf::Vector2f position) {
    mPosition = position;
    updateShape();
}
void BoxInput::setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); }

void BoxInput::updateShape() {
    if (mWidth < 1 || mHeight < 1) {
        mWidth = mHeight = 1;
    }
    // [540 x 90]
    // [320 x 90][200 x 90], distance = 20
    float scaleX = mWidth / 540;
    mBoxInput.setSize(sf::Vector2f(320 * scaleX, mHeight));
    mRandomButton.setSize(sf::Vector2f(200 * scaleX, mHeight));

    mBoxInput.setPosition(mPosition);
    mRandomButton.setPosition(mPosition + sf::Vector2f(mWidth - 200 * scaleX, 0));
}

void BoxInput::setHold(bool isHold) { mIsHold = isHold; }
bool BoxInput::getHold() const { return mIsHold; }

int BoxInput::getValue() const {
    return std::stoi(mBoxInput.getText());
}

void BoxInput::draw(sf::RenderTarget& target) {
    if (mIsHold) {
        mBoxInput.setFillColor(Constants::BackGroundTextColorHold);
    }
    else {
        mBoxInput.setFillColor(Constants::BackGroundTextColor);
    }
    mBoxInput.draw(target);
    mRandomButton.draw(target);
}
