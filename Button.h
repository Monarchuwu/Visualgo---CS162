#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button();

    void setID(int ID);
    int getID() const;

    void setPosition(const sf::Vector2f &position);
    void setPosition(float x, float y);
    void setSize(const sf::Vector2f& size);
    void setFillColor(const sf::Color& color);

    void setFont(const sf::Font& font);
    void setStyle(sf::Uint32 style);
    void setCharacterSize(size_t size = 35);
    void setTextConst(std::string text = "");
    void setText(std::string text = "");
    void setTextFillColor(const sf::Color& color);

    std::string getTextConst() const;
    std::string getText() const;
    std::string getTextAll() const;

    virtual void draw(sf::RenderTarget& target);

    void setAction(std::function<void()> clickedAction);

    sf::FloatRect getGlobalBounds() const;
    sf::FloatRect getLocalBounds() const;

    //void enableFitContent();
    //void disableFitContent();

private:
    void setPositionContent();

private:
    int mID;
    sf::RectangleShape mButton;
    sf::Text mText;
    std::string mTextConst, mTextTemp;
    std::function<void()> mAction;
    bool mFitContent;
};
