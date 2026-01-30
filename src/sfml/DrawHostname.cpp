/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** drawHostname
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawHostname(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_hostname("Host", _font, 16);
    label_hostname.setPosition(pos.x + 20, ty);
    label_hostname.setFillColor(COLOR_LABEL);
    _window.draw(label_hostname);

    sf::Text value_hostname(safeGet(data, "Hostname"), _font, 16);
    value_hostname.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_hostname.setFillColor(COLOR_VALUE);
    _window.draw(value_hostname);
    ty += 22;

    sf::Text label_username("Username", _font, 16);
    label_username.setPosition(pos.x + 20, ty);
    label_username.setFillColor(COLOR_LABEL);
    _window.draw(label_username);

    sf::Text value_username(safeGet(data, "Username"), _font, 16);
    value_username.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_username.setFillColor(COLOR_VALUE);
    _window.draw(value_username);
    ty += 22;
}