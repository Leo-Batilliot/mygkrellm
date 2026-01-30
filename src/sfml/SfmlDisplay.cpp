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
    _window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE);
    _window.setFramerateLimit(FRAME_LIMIT);
    _font.loadFromFile(FONT_PATH);
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