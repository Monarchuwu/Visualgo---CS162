#pragma once
#include <SFML/Graphics.hpp>

class DashTable {
	// [0..900] x [500..900]
public:
	DashTable();

private:
	/// Main
	// [0..900] x [500..900] : Theme
	sf::RectangleShape mDashTable;

	/// Button List
	// [10..290] x [510..890] : Theme
	sf::RectangleShape mButtonList;
	// [10..290] x [510..586] + [0][76] per button : Button
	// return: what button is being selected
	sf::RectangleShape mButton[5];
	std::string mNameButton[5] = {
	    "Create",
	    "Search",
	    "Update",
	    "Insert",
	    "Delete"
	};

	/// Parameter Table
	// [290..890] x [510..890] : Theme + Table
	// Table
	// is <At Begin (i = 0), At Middle (i = 1..n-2), At End (i = n-1)>
	// [input position][random]
	// [input  value  ][random]
	// [Play] (change to [Unavailable] when animation is begin played) <=> Enter
};
