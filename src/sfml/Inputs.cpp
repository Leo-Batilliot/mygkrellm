#include "SfmlDisplay.hpp"

bool SfmlDisplay::handle_inputs()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) return false;

        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (int i = 0; i < (int)_modules.size(); ++i) {
                if (_modules[i].background.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    _draggedIdx = i;
                    _dragOffset = _modules[i].background.getPosition() - sf::Vector2f(mousePos.x, mousePos.y);
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (_draggedIdx != -1 && _targetIdx != -1) {
                int finalPos = (_draggedIdx < _targetIdx) ? _targetIdx - 1 : _targetIdx;
                if (finalPos != _draggedIdx && finalPos >= 0 && finalPos < (int)_modules.size()) {
                    auto moving = _modules[_draggedIdx];
                    _modules.erase(_modules.begin() + _draggedIdx);
                    _modules.insert(_modules.begin() + finalPos, moving);
                }
            }
            _draggedIdx = -1;
            _targetIdx = -1;
        }
    }
    return true;
}