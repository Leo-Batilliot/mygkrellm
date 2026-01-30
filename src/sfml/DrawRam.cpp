/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawRam
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawRam(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_total("Total", _font, 16);
    label_total.setPosition(pos.x + 20, ty);
    label_total.setFillColor(COLOR_LABEL);
    _window.draw(label_total);

    sf::Text value_total(safeGet(data, "Total"), _font, 16);
    value_total.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_total.setFillColor(COLOR_VALUE);
    _window.draw(value_total);
    ty += 22;

    sf::Text label_used("Used", _font, 16);
    label_used.setPosition(pos.x + 20, ty);
    label_used.setFillColor(COLOR_LABEL);
    _window.draw(label_used);

    sf::Text value_used(safeGet(data, "Used"), _font, 16);
    value_used.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_used.setFillColor(COLOR_VALUE);
    _window.draw(value_used);
    ty += 22;

    std::string percStr = safeGet(data, "Percent");
    float percent = std::stof(percStr);
    sf::Color ramColor(255 * percent / 100, 255 * (100 - percent) / 100, 0);

    sf::Text label_percentage("Usage", _font, 16);
    label_percentage.setPosition(pos.x + 20, ty);
    label_percentage.setFillColor(COLOR_LABEL);
    _window.draw(label_percentage);

    sf::Text value_percentage(percStr, _font, 16);
    value_percentage.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_percentage.setFillColor(ramColor);
    _window.draw(value_percentage);

    sf::RectangleShape bar_rectangle(sf::Vector2f(270, 12));
    bar_rectangle.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
    bar_rectangle.setFillColor(sf::Color(80, 80, 80));
    _window.draw(bar_rectangle);

    sf::RectangleShape bar_color(sf::Vector2f(2.7f * percent, 12));
    bar_color.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
    bar_color.setFillColor(ramColor);
    _window.draw(bar_color);
    ty += 30;
}