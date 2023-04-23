#include "BasicNode.h"
#include "Constants.h"
#include "Random.h"

BasicNode::BasicNode()
    : mBody(Constants::CirleNodeRadius),
      mText(),
      mValue() {
    mBody.setOutlineThickness(Constants::NodeOutlineThinkness);
    mBody.setFillColor(Constants::NodeFillColor);
    mBody.setOutlineColor(Constants::NodeOutlineColor);

    mText.setFont(Constants::Font);
    mText.setStyle(sf::Text::Bold);
    mText.setCharacterSize(Constants::CharacterSize);
    mText.setFillColor(Constants::TextNodeColor);
    updateValue(Random::Rand());
}

void BasicNode::updateValue(int value) {
    mValue = value;
    mStrText = std::to_string(mValue);
    setText(mStrText);
}

void BasicNode::setText(std::string text) {
    mText.setString(text);
    sf::FloatRect rect = mText.getLocalBounds();
    int x              = rect.left + rect.width / 2;
    int y              = rect.top + rect.height / 2;
    mText.setOrigin(x, y);
}

std::string BasicNode::getText() const {
    return mStrText;
}

void BasicNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(mBody, states);

    // sf::FloatRect rect = mText.getGlobalBounds();
    // sf::Vector2f src(rect.left, rect.top);
    // sf::Vector2f dest = src + sf::Vector2f(rect.width, rect.height);
    // sf::RectangleShape shape(dest - src);
    // shape.setPosition(src);
    // target.draw(shape, states);

    target.draw(mText, sf::Transform().translate(states.transform.transformPoint(0, 0)));
}