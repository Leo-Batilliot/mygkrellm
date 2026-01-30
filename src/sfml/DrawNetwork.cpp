/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawNetwork
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawNetwork(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_down("Download", _font, 16);
    label_down.setPosition(pos.x + 20, ty);
    label_down.setFillColor(COLOR_LABEL);
    _window.draw(label_down);

    sf::Text value_down(safeGet(data, "Download"), _font, 16);
    value_down.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_down.setFillColor(COLOR_VALUE);
    _window.draw(value_down);
    ty += 22;

    sf::Text label_up("Upload", _font, 16);
    label_up.setPosition(pos.x + 20, ty);
    label_up.setFillColor(COLOR_LABEL);
    _window.draw(label_up);

    sf::Text value_up(safeGet(data, "Upload"), _font, 16);
    value_up.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_up.setFillColor(COLOR_VALUE);
    _window.draw(value_up);
    ty += 22;
}