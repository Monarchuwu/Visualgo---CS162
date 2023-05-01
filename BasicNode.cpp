#include "BasicNode.h"
#include "Constants.h"
#include "Random.h"

BasicNode::BasicNode(float radius,
                     float outlineThickness,
                     size_t pointCount,
                     float initAngle,
                     int val)
    : mBody(radius, pointCount, initAngle),
      mText(),
      mValue() {
    mBody.setOutlineThickness(outlineThickness);
    mBody.setFillColor(Constants::NodeFillColor);
    mBody.setOutlineColor(Constants::NodeOutlineColor);

    mText.setFont(Constants::Font);
    mText.setStyle(sf::Text::Bold);
    mText.setCharacterSize(Constants::TextNodeCharacterSize);
    mText.setFillColor(Constants::TextNodeColor);

    if (val == -1) val = Random::Rand();
    setValue(val);
}

void BasicNode::setFillColorBody(sf::Color& color) {
    mBody.setFillColor(color);
}
void BasicNode::setFillColorText(sf::Color& color) {
    mText.setFillColor(color);
}
void BasicNode::setOutlineColor(sf::Color& color) {
    mBody.setOutlineColor(color);
}

sf::Color BasicNode::getFillColorBody() const {
    return mBody.getFillColor();
}
sf::Color BasicNode::getFillColorText() const {
    return mText.getFillColor();
}
sf::Color BasicNode::getOutlineColor() const {
    return mBody.getOutlineColor();
}

void BasicNode::setRadius(float radius) {
    mBody.setRadius(radius);
}
void BasicNode::setOutlineThickness(float outlineThickness) {
    mBody.setOutlineThickness(outlineThickness);
}
float BasicNode::getRadius() const {
    return mBody.getRadius();
}
float BasicNode::getOutlineThickness() const {
    return mBody.getOutlineThickness();
}

void BasicNode::setValue(int value) {
    mValue = value;
    mStrText = std::to_string(mValue);
    setText(mStrText);
}
int BasicNode::getValue() const { return mValue; }
void BasicNode::setText(std::string text) {
    mText.setString(text);
    sf::FloatRect rect = mText.getLocalBounds();
    int x              = rect.left + rect.width / 2;
    int y              = rect.top + rect.height / 2;
    mText.setOrigin(x, y);
}
std::string BasicNode::getText() const { return mStrText; }

void BasicNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Transform translation = states.transform.translate(0, 0);
    target.draw(mBody, translation);
    target.draw(mText, translation);
}