#include "Button.h"
#include "Constants.h"

Button::Button()
    : mButton(),
      mText(),
      mTextConst(),
      mTextTemp(),
      mFitContent(true) {
    setID(-1);
    mText.setFont(Constants::Font);
    mText.setStyle(sf::Text::Bold);
    mText.setFillColor(sf::Color::Black);
    setCharacterSize();
    setText();
}

void Button::setID(int ID) { mID = ID; }
int Button::getID() const { return mID; }

void Button::setPosition(const sf::Vector2f& position) {
    mButton.setPosition(position);
}

void Button::setPosition(float x, float y) {
    mButton.setPosition(x, y);
}

void Button::setSize(const sf::Vector2f& size) {
    mButton.setSize(size);
}

void Button::setFillColor(const sf::Color& color) {
    mButton.setFillColor(color);
}

void Button::setFont(const sf::Font& font) {
    mText.setFont(font);
}

void Button::setStyle(sf::Uint32 style) {
    mText.setStyle(style);
}

void Button::setCharacterSize(size_t size) {
    mText.setCharacterSize(size);
}

void Button::setTextConst(std::string text) {
    mTextConst = text;
    mText.setString(mTextConst + mTextTemp);
    setPositionContent();
}

void Button::setText(std::string text) {
    mTextTemp = text;
    mText.setString(mTextConst + mTextTemp);
    setPositionContent();
}

void Button::setTextFillColor(const sf::Color& color) {
    mText.setFillColor(color);
}

std::string Button::getTextConst() const {
    return mTextConst;
}

std::string Button::getText() const {
    return mTextTemp;
}

std::string Button::getTextAll() const {
    return mText.getString();
}

void Button::draw(sf::RenderTarget& target) {
    mText.setPosition(mButton.getPosition() + mButton.getSize() / 2.f);
    target.draw(mButton);
    target.draw(mText);
}

void Button::setAction(std::function<void()> clickedAction) {
    mAction = clickedAction;
}

sf::FloatRect Button::getGlobalBounds() const { return mButton.getGlobalBounds(); }
sf::FloatRect Button::getLocalBounds() const { return mButton.getLocalBounds(); }

//void Button::enableFitContent() {
//    mFitContent = true;
//    setPositionContent();
//}
//
//void Button::disableFitContent() {
//    mFitContent = false;
//    setPositionContent();
//}

void Button::setPositionContent() {
    sf::FloatRect rect = mText.getLocalBounds();
    int x              = rect.left + rect.width / 2;
    int y              = rect.top + rect.height / 2;
    if (mFitContent) {
        mText.setOrigin(x, y);
    }
    //else {
    //    if (x < y) {
    //        mText.setOrigin(x, y);
    //    }
    //    else {
    //        mText.setOrigin(y, y);
    //    }
    //}
}