#include "SfmlDisplay.hpp"

int SfmlDisplay::handle_inputs()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q))
            return 1;

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            return 2;

        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        sf::Vector2f mapmousePos = _window.mapPixelToCoords(mousePos);

        if (event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            _view.setSize(static_cast<float>(event.size.width), static_cast<float>(event.size.height));
            _view.setCenter(event.size.width / 2.0f, (event.size.height / 2.0f) + _scrollY);
        }

        if (event.type == sf::Event::MouseButtonPressed ) {
            for (int i = 0; i < (int)_modules.size(); ++i) {
                if (_modules[i].background.getGlobalBounds().contains(mapmousePos.x, mapmousePos.y)) {
                    _draggedIdx = i;
                    _dragOffset = _modules[i].background.getPosition() - mapmousePos;
                    break;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            for (int i = 0; i < (int)_modules.size(); ++i) {
                sf::FloatRect bounds = _modules[i].background.getGlobalBounds();

                if (bounds.contains(mapmousePos)) {
                    _draggedIdx = i;
                    _dragOffset = _modules[i].background.getPosition() - mapmousePos;
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

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {

                _scrollY -= event.mouseWheelScroll.delta * _scrollSpeed;
                if (_scrollY < 0)
                    _scrollY = 0;

                if (_scrollY > _maxScrollY) _scrollY =
                    _maxScrollY;
            }
        }
    }
    return 0;
}