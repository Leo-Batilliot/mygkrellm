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
    if (std::getenv("DISPLAY") == nullptr) {
        throw std::runtime_error("No GUI set");
    }

    _window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), WIN_TITLE);

    if (!_window.isOpen())
        throw std::runtime_error("Failed to create SFML window (no GUI?)");

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i centerPos((desktop.width / 2) - (WIN_WIDTH / 2), (desktop.height / 2) - (WIN_HEIGHT / 2));
    _window.setPosition(centerPos);
    _window.setFramerateLimit(FRAME_LIMIT);

    if (!_font.loadFromFile(FONT_PATH))
        throw std::runtime_error(std::string("Missing Font: ") + FONT_PATH);
    if (!_lightningTexture.loadFromFile(LIGHTNING_PATH))
        throw std::runtime_error(std::string("Missing Texture: ") + LIGHTNING_PATH);
    _lightningSprite.setTexture(_lightningTexture);

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