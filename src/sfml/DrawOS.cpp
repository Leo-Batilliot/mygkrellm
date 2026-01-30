/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawOS
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawOS(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_os("Operating system", _font, 16);
    label_os.setPosition(pos.x + 20, ty);
    label_os.setFillColor(COLOR_LABEL);
    _window.draw(label_os);

    sf::Text value_os(safeGet(data, "Operating system"), _font, 16);
    value_os.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_os.setFillColor(COLOR_VALUE);
    _window.draw(value_os);
    ty += 22;

    sf::Text label_kernel("Kernel", _font, 16);
    label_kernel.setPosition(pos.x + 20, ty);
    label_kernel.setFillColor(COLOR_LABEL);
    _window.draw(label_kernel);

    sf::Text value_kernel(safeGet(data, "Kernel"), _font, 16);
    value_kernel.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_kernel.setFillColor(COLOR_VALUE);
    _window.draw(value_kernel);
    ty += 22;
}