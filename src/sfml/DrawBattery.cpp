/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DrawBattery
*/
#include "SfmlDisplay.hpp"

void SfmlDisplay::drawBattery(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    std::string level_str = safeGet(data, "Level");
    std::string status_val = safeGet(data, "Status");
    float level = 0;

    if (level_str != "---" && level_str != "Unknown" && level_str != "Online") {
        level = std::stof(level_str);
    } else if (level_str == "Online") {
        level = 100;
    }

    sf::Color battery_color = sf::Color::White;
    if (status_val == "Charging") battery_color = sf::Color::Green;
    if (level <= 10.0f) battery_color = sf::Color::Red;
    else if (level <= 20.0f) battery_color = sf::Color(255, 165, 0);

    sf::Text label_percent(level_str, _font, 22);
    label_percent.setStyle(sf::Text::Bold);
    label_percent.setPosition(pos.x + 20, ty + 17);
    label_percent.setFillColor(sf::Color::White);
    _window.draw(label_percent);

    float logo_w = 100.0f;
    float logo_h = 48.0f;
    float logo_x = pos.x + VALUE_X_OFFSET;
    float logo_y = ty + 4;

    sf::RectangleShape battery_body(sf::Vector2f(logo_w, logo_h));
    battery_body.setPosition(logo_x, logo_y);
    battery_body.setFillColor(sf::Color::Transparent);
    battery_body.setOutlineThickness(2);
    battery_body.setOutlineColor(sf::Color(120, 120, 120));
    _window.draw(battery_body);

    sf::RectangleShape battery_tip(sf::Vector2f(8, 20));
    battery_tip.setPosition(logo_x + logo_w + 2, logo_y + (logo_h / 4));
    battery_tip.setFillColor(sf::Color(120, 120, 120));
    _window.draw(battery_tip);

    if (level > 0) {
        float pad = 3.0f;
        float fill_w = (logo_w - (pad * 2)) * (level / 100.0f);
        sf::RectangleShape battery_fill(sf::Vector2f(fill_w, logo_h - (pad * 2)));
        battery_fill.setPosition(logo_x + pad, logo_y + pad);
        battery_fill.setFillColor(battery_color);
        _window.draw(battery_fill);
    }
    ty += 85;

    sf::Text value_status(status_val, _font, 16);
    value_status.setPosition(pos.x + VALUE_X_OFFSET, ty - 28);
    value_status.setFillColor(
        (status_val == "Charging") ? sf::Color::Green :
        (status_val == "Discharging") ? sf::Color::White :
        COLOR_VALUE
    );
    _window.draw(value_status);

    if (status_val == "Charging") {
        sf::Sprite lightning = _lightningSprite;
        lightning.setRotation(270);

        float targetHeight = logo_h * 1.5f;
        sf::Vector2u texSize = _lightningTexture.getSize();

        float scale = targetHeight / texSize.y;
        lightning.setScale(scale, scale);

        sf::FloatRect bounds = lightning.getGlobalBounds();
        float centerX = logo_x + logo_w / 2 - bounds.width / 2;
        float centerY = logo_y + logo_h / 2 - bounds.height / 2;
        lightning.setPosition(centerX, centerY + 30);

        _window.draw(lightning);
    }
}