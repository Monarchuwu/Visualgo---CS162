#include "Arrow.h"
#include "Constants.h"

void drawArrow2Point(sf::Vector2f src, sf::Vector2f dest, sf::RenderTarget& target, sf::Color colorArrow) {
    static const float pi = 3.141592654f;
    float arrowThickness  = Constants::NodeOutlineThinkness;
    float headArrowRadius = arrowThickness * 2;

    sf::Vector2f vec = dest - src;
    float angle      = atan2f(vec.y, vec.x) / (2 * pi) * 360;
    float dist       = sqrt(vec.x * vec.x + vec.y * vec.y) - headArrowRadius;
    if (dist < 0.f) dist = 0.f;

    sf::RectangleShape mBody(sf::Vector2f(dist, arrowThickness));
    CircleShape mHead(headArrowRadius, 3);
    mBody.setFillColor(colorArrow);
    mHead.setFillColor(colorArrow);

    mBody.setOrigin(0.f, arrowThickness / 2);
    mHead.setOrigin(-dist, 0.f);
    mBody.setPosition(src);
    mHead.setPosition(src);
    mBody.setRotation(angle);
    mHead.setRotation(angle);
    target.draw(mBody);
    target.draw(mHead);
}

void drawArrow2Head2Point(sf::Vector2f src, sf::Vector2f dest, sf::RenderTarget& target, sf::Color colorArrow) {
    static const float pi = 3.141592654f;
    float arrowThickness  = Constants::NodeOutlineThinkness;
    float headArrowRadius = arrowThickness * 2;

    sf::Vector2f vec = dest - src;
    float angle      = atan2f(vec.y, vec.x) / (2 * pi) * 360;
    float dist       = sqrt(vec.x * vec.x + vec.y * vec.y) - headArrowRadius * 2;
    if (dist < 0.f) dist = 0.f;

    sf::RectangleShape mBody(sf::Vector2f(dist, arrowThickness));
    CircleShape mHead1(headArrowRadius, 3);
    CircleShape mHead2(headArrowRadius, 3, Constants::pi);
    mBody.setFillColor(colorArrow);
    mHead1.setFillColor(colorArrow);
    mHead2.setFillColor(colorArrow);

    mBody.setOrigin(-headArrowRadius, arrowThickness / 2);
    mHead1.setOrigin(-headArrowRadius - dist, 0.f);
    mHead2.setOrigin(-headArrowRadius, 0.f);
    mBody.setPosition(src);
    mHead1.setPosition(src);
    mHead2.setPosition(src);
    mBody.setRotation(angle);
    mHead1.setRotation(angle);
    mHead2.setRotation(angle);
    target.draw(mBody);
    target.draw(mHead1);
    target.draw(mHead2);
}
