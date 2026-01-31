/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawDateTime
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawDateTime(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_date("Date", _font, 16);
    label_date.setPosition(pos.x + 20, ty);
    label_date.setFillColor(COLOR_LABEL);
    _window.draw(label_date);

    sf::Text value_date(safeGet(data, "Date"), _font, 16);
    value_date.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_date.setFillColor(COLOR_VALUE);
    _window.draw(value_date);
    ty += 22;

    sf::Text label_time("Time", _font, 16);
    label_time.setPosition(pos.x + 20, ty);
    label_time.setFillColor(COLOR_LABEL);
    _window.draw(label_time);

    sf::Text value_time(safeGet(data, "Time"), _font, 16);
    value_time.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_time.setFillColor(COLOR_VALUE);
    _window.draw(value_time);
    ty += 22;
}