#ifndef SFMLCONFIG_HPP_
#define SFMLCONFIG_HPP_

#include <SFML/Graphics.hpp>

// Window Settings
#define WIN_WIDTH 800
#define WIN_HEIGHT 1080
#define WIN_TITLE "MyGKrellm"
#define FRAME_LIMIT 60

// Visual Settings
#define MOD_WIDTH WIN_WIDTH - 40
#define MOD_MARGIN 20
#define START_Y 20
#define START_X 20

// Module Settings
#define COLOR_LABEL sf::Color::White
#define COLOR_VALUE sf::Color::Green
#define VALUE_X_OFFSET 190

// Colors
#define COLOR_BG sf::Color(30, 30, 30)
#define COLOR_MOD_FILL sf::Color(30, 30, 30)
#define COLOR_MOD_BORDER sf::Color(255, 255, 255, 100)
#define BORDER_THICKNESS 1.0f
#define COLOR_DRAG sf::Color(100, 70, 70, 150)
#define COLOR_PREVIEW sf::Color(255, 0, 0, 150)
#define COLOR_TITLE sf::Color::Red

// Assets
#define FONT_PATH "src/assets/fonts/OpenSansRegular.ttf"

#endif