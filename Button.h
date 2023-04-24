#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button();

    void setPosition(const sf::Vector2f &position);
    void setPosition(float x, float y);
    void setSize(const sf::Vector2f& size);
    void setFillColor(const sf::Color& color);

    void setFont(const sf::Font& font);
    void setStyle(sf::Uint32 style);
    void setCharacterSize(size_t size = 35);
    void setText(std::string text = "");
    void setTextFillColor(const sf::Color& color);

    std::string getText() const;

    virtual void draw(sf::RenderTarget& target);

    void setAction(std::function<void()> clickedAction);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

private:
    //void EnableFitContent();
    //void DisableFitContent();
    void setPositionContent();

private:
    sf::RectangleShape mButton;
    sf::Text mText;
    std::function<void()> mAction;
    bool mFitContent;
};
