/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawUptime
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawUptime(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label("System Uptime", _font, 16);
    label.setPosition(pos.x + 20, ty);
    label.setFillColor(COLOR_LABEL);
    _window.draw(label);

    sf::Text value(safeGet(data, "Uptime"), _font, 16);
    value.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value.setFillColor(COLOR_VALUE);
    _window.draw(value);

    ty += 25; 
}