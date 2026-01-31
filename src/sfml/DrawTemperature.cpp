/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawTemperature
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawTemperature(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    std::string tempStr = safeGet(data, "Temp");
    float tempVal = 0;

    try {
        if (tempStr != "Unknown" && tempStr.find("No Sensor") == std::string::npos)
            tempVal = std::stof(tempStr);
    } catch (...) { tempVal = 0; }

    sf::Text label("CPU Temp", _font, 16);
    label.setPosition(pos.x + 20, ty - 5);
    label.setFillColor(COLOR_LABEL);
    _window.draw(label);

    sf::Text value(tempStr, _font, 18);
    value.setStyle(sf::Text::Bold);
    value.setPosition(pos.x + VALUE_X_OFFSET, ty - 7);
    
    sf::Color tempColor = sf::Color::Green;
    if (tempVal > 80) tempColor = sf::Color::Red;
    else if (tempVal > 65) tempColor = sf::Color(255, 165, 0);
    else if (tempVal < 35) tempColor = sf::Color(100, 200, 255);
    
    value.setFillColor(tempColor);
    _window.draw(value);

    float barWidth = 270.0f;
    float barHeight = 10.0f;

    sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
    bgBar.setPosition(pos.x + VALUE_X_OFFSET + 80, ty);
    bgBar.setFillColor(sf::Color(40, 40, 40));
    _window.draw(bgBar);

    float ratio = std::min(std::max(tempVal / 100.0f, 0.0f), 1.0f);
    if (ratio > 0) {
        sf::RectangleShape fillBar(sf::Vector2f(barWidth * ratio, barHeight));
        fillBar.setPosition(pos.x + VALUE_X_OFFSET + 80, ty);
        fillBar.setFillColor(tempColor);
        
        _window.draw(fillBar);
    }

    ty += 20;
}