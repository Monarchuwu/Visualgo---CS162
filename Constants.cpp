#include <iostream>
#include "Constants.h"

namespace Constants {
    /// Color Constants
    // Dark > DarkMedium > LightMedium > Light
    sf::Color StandardColor[4] = {
        sf::Color(96, 150, 180),
        sf::Color(147, 191, 207),
        sf::Color(189, 205, 214),
        sf::Color(238, 233, 218)
    };

    /// Font Constants
    sf::Font Font;

    /// Node Constants
    // Body
    sf::Color NodeFillColor    = StandardColor[1];
    sf::Color NodeOutlineColor = sf::Color::Black;
    sf::Color TextNodeColor    = sf::Color::Black;

    /// Basic List Constants
    size_t CountNode;

    /// Control Table Constants
    // Control Table
    sf::Color ControlTableThemeColor = StandardColor[1];
    // Button Main
    sf::Color ButtonMainColor = StandardColor[0];
    sf::Color ButtonMainColorClicked = StandardColor[3];
    // Parameter Table
    sf::Color ParameterTableThemeColor = StandardColor[3];
    sf::Color BackGroundTextColor      = StandardColor[2];
    sf::Color BackGroundTextColorHold  = StandardColor[1];
    // Position Row (Row 1)

    void init() {
        if (!Font.loadFromFile(FontName)) {
            std::cout << "Can't load the font !!!";
            exit(0);
        }
    }
} // namespace Constants