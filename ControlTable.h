#pragma once
#include <SFML/Graphics.hpp>

class ControlTable {
	// [0..900] x [500..900]
public:
	ControlTable();
	virtual void draw(sf::RenderTarget& target) const;

private:

private:                                                                                                                            private:
	/// Main
	// Theme : [0..900] x [500..900]
    sf::RectangleShape mControlTableTheme;

	/// Button List
	// ButtonMain : [10..290] x [510..585] + [0][76] per button
	// return: what button is being selected
	sf::RectangleShape mButtonMain[5];
	// NameButtonMain
	std::string mNameButtonMain[5] = {
	    "Create",
	    "Search",
	    "Update",
	    "Insert",
	    "Remove"
	};
	sf::Text mTextButtonMain[5];

	/// Parameter Table
	// Theme : [290..890] x [510..890]
	sf::RectangleShape mParameterTableTheme;
	// Table
	// is <At Begin (i = 0), At Middle (i = 1..n-2), At End (i = n-1)>
	// [input position][random]
	// [input  value  ][random]
	// [Play] (change to [Unavailable] when animation is begin played) <=> Enter
};
