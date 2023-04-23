#pragma once
#include <SFML/Graphics.hpp>

class CircleShape : public sf::Shape {
public:
    CircleShape(float radius = 0.0f, size_t pointCount = 30Ui64, float initAngle = 0.0f);
    void setRadius(float radius);
    float getRadius() const;
    void setInitAngle(float initAngle);
    float getInitAngle() const;
    virtual size_t getPointCount() const;
    virtual sf::Vector2f getPoint(size_t index) const;

private:
    float mRadius;
    float mInitAngle;
    size_t mPointCount;
};
