/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawDisk
*/

#include "SfmlDisplay.hpp"

void SfmlDisplay::drawDisk(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    std::string total = safeGet(data, "Total");
    std::string used = safeGet(data, "Used");
    std::string free = safeGet(data, "Free");
    std::string percentStr = safeGet(data, "Percent");

    pos.x += VALUE_X_OFFSET;

    float percent = 0.0f;
    try {
        percent = std::stof(percentStr);
    } catch (...) { percent = 0.0f; }

    sf::Text label_usage("Local Disk - " + total , _font, 16);
    label_usage.setPosition(pos.x, ty);
    label_usage.setFillColor(COLOR_LABEL);
    _window.draw(label_usage);

    ty += 25;
    float barWidth = 270.0f;
    float barHeight = 14.0f;
    float startX = pos.x;

    sf::RectangleShape bgBar(sf::Vector2f(barWidth, barHeight));
    bgBar.setPosition(startX, ty);
    bgBar.setFillColor(sf::Color(200, 200, 200)); 
    _window.draw(bgBar);

    sf::Color winBlue(0, 120, 215);
    sf::Color winRed(232, 17, 35);
    sf::Color fillColor = (percent > 90.0f) ? winRed : winBlue;

    if (percent > 0) {
        float fillWidth = barWidth * (percent / 100.0f);
        sf::RectangleShape fillBar(sf::Vector2f(fillWidth, barHeight));
        fillBar.setPosition(startX, ty);
        fillBar.setFillColor(fillColor);
        _window.draw(fillBar);
    }

    sf::Text label_storage("Storage", _font, 16);
    label_storage.setPosition(pos.x - VALUE_X_OFFSET + 20, ty - 5);
    label_storage.setFillColor(COLOR_LABEL);
    _window.draw(label_storage);

    std::string details = used + " used";
    sf::Text label_details(details, _font, 14);
    label_details.setPosition(pos.x, ty + 18);
    label_details.setFillColor(sf::Color(180, 180, 180));
    _window.draw(label_details);

    ty += 40;
}