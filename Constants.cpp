#include <iostream>
#include "Constants.h"

namespace Constants {
    sf::Color NodeFillColor    = sf::Color::Black;
    sf::Color NodeOutlineColor = sf::Color::White;
    sf::Color TextNodeColor    = sf::Color::White;

    sf::Font Font;

    void init() {
        if (!Font.loadFromFile(FontName)) {
            std::cout << "Can't load the font !!!";
            exit(0);
        }
    }

} // namespace Constants