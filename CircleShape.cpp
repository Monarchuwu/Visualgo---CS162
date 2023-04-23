#include "CircleShape.h"

CircleShape::CircleShape(float radius, size_t pointCount, float initAngle)
    : mRadius(radius),
      mPointCount(pointCount),
      mInitAngle(initAngle) {
    update();
}

void CircleShape::setRadius(const float radius) {
    mRadius = radius;
    update();
}

float CircleShape::getRadius() const {
    return mRadius;
}

void CircleShape::setInitAngle(float initAngle) {
    mInitAngle = initAngle;
    update();
}

float CircleShape::getInitAngle() const {
    return mInitAngle;
}

size_t CircleShape::getPointCount() const {
    return mPointCount; // fixed, but could be an attribute of the class if needed
}

sf::Vector2f CircleShape::getPoint(size_t index) const {
    static const float pi = 3.141592654f;

    float angle = index * 2 * pi / getPointCount() + mInitAngle;
    float x     = std::cos(angle) * mRadius;
    float y     = std::sin(angle) * mRadius;
    return sf::Vector2f(x, y);
}