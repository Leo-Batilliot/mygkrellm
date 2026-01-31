/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** SfmlDisplay
*/
#include "SfmlDisplay.hpp"

SfmlDisplay::SfmlDisplay() : _draggedIdx(-1), _targetIdx(-1) {}
SfmlDisplay::~SfmlDisplay() {}

void SfmlDisplay::init()
{
    _window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "My MyGKrellM");
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::Vector2i centerPos((desktop.width / 2) - (WIN_WIDTH / 2), (desktop.height / 2) - (WIN_HEIGHT / 2));
    _window.setPosition(centerPos);
    _window.setFramerateLimit(FRAME_LIMIT);

    _font.loadFromFile(FONT_PATH);

    _view = _window.getDefaultView();
}

void SfmlDisplay::stop()
{
    if (_window.isOpen()) _window.close();
}

void SfmlDisplay::syncModules(const std::vector<Krell::IModule *> &modules) {
    if (_modules.size() != modules.size()) {
        _modules.clear();
        for (auto* m : modules) {
            ModuleWrapper wrapper;
            wrapper.module = m;
            wrapper.background.setFillColor(COLOR_MOD_FILL);
            wrapper.background.setOutlineColor(COLOR_MOD_BORDER);
            wrapper.background.setOutlineThickness(BORDER_THICKNESS);
            _modules.push_back(wrapper);
        }
    }
}