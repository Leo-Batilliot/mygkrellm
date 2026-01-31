#include "SfmlDisplay.hpp"


void SfmlDisplay::renderStaticStack(float &currentY, sf::Vector2i mousePos, float width, float startX)
{
    for (int i = 0; i < (int)_modules.size(); ++i) {
        if (!_modules[i].isVisible || i == _draggedIdx)
            continue;

        if (_draggedIdx != -1 && _targetIdx == -1) {
            float mid = currentY + (_modules[i].background.getSize().y / 2.0f);
            if (mousePos.y < mid)
                _targetIdx = i;
        }

        drawModule(_modules[i], sf::Vector2f(startX, currentY), width);
        currentY += _modules[i].background.getSize().y + MOD_MARGIN;
    }
    
    if (_draggedIdx != -1 && _targetIdx == -1)
        _targetIdx = _modules.size();
}

void SfmlDisplay::renderPreviewLine()
{
    float py = START_Y;

    for (int i = 0; i < _targetIdx; i++) {
        if (i != _draggedIdx && _modules[i].isVisible)
            py += _modules[i].background.getSize().y + MOD_MARGIN;
    }

    sf::RectangleShape line(sf::Vector2f(MOD_WIDTH, 3));
    line.setFillColor(COLOR_PREVIEW);
    line.setPosition(START_X, py - (MOD_MARGIN / 2.0f) - 4);
    _window.draw(line);
}

void SfmlDisplay::renderDraggedModule(sf::Vector2i mousePos, float width)
{
    auto &m = _modules[_draggedIdx];
    sf::Vector2f dragPos = sf::Vector2f(mousePos.x, mousePos.y) + _dragOffset;

    m.background.setFillColor(COLOR_DRAG);
    m.background.setOutlineThickness(BORDER_THICKNESS * 2);
    m.background.setOutlineColor(sf::Color::White);

    drawModule(m, dragPos, width);
}

void SfmlDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    syncModules(modules);
    _window.clear(COLOR_BG);

    float dynamicWidth = static_cast<float>(_window.getSize().x) - 40.0f;
    float dynamicStartX = 20.0f;

    _view.setCenter(_window.getSize().x / 2.0f, (_window.getSize().y / 2.0f) + _scrollY);
    _window.setView(_view);

    sf::Vector2i pixelMousePos = sf::Mouse::getPosition(_window);
    sf::Vector2f worldMousePos = _window.mapPixelToCoords(pixelMousePos);
    sf::Vector2i mousePos(static_cast<int>(worldMousePos.x), static_cast<int>(worldMousePos.y));

    float currentY = START_Y;
    _targetIdx = -1;

    renderStaticStack(currentY, mousePos, dynamicWidth, dynamicStartX);

    float contentHeight = currentY + MOD_MARGIN;
    _maxScrollY = std::max(0.0f, contentHeight - (float)_window.getSize().y);

    float marginDist = dynamicStartX + dynamicWidth + 1; 
    sf::RectangleShape rightMask(sf::Vector2f(1000.0f, contentHeight + 2000.0f));
    rightMask.setPosition(marginDist, 0);
    rightMask.setFillColor(COLOR_BG);
    _window.draw(rightMask);

    sf::RectangleShape leftMask(sf::Vector2f(dynamicStartX - 1, contentHeight + 2000.0f));
    leftMask.setPosition(0, 0);
    leftMask.setFillColor(COLOR_BG);
    _window.draw(leftMask);

    if (_draggedIdx != -1) {
        renderPreviewLine();
        renderDraggedModule(mousePos, dynamicWidth);
    }

    _window.display();
}

void SfmlDisplay::drawModule(ModuleWrapper &wrapper, sf::Vector2f pos, float width)
{
    std::string name = wrapper.module->getName();
    const auto &data = wrapper.module->getData();
    float ty = pos.y + 25; 

    wrapper.background.setSize(sf::Vector2f(width, wrapper.background.getSize().y));
    wrapper.background.setPosition(pos);
    if (!(_draggedIdx != -1 && &wrapper == &_modules[_draggedIdx])) {
        wrapper.background.setFillColor(COLOR_MOD_FILL);
        wrapper.background.setOutlineThickness(BORDER_THICKNESS);
        wrapper.background.setOutlineColor(COLOR_MOD_BORDER);
    }
    _window.draw(wrapper.background);

    sf::Text title(name, _font, 18);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(COLOR_TITLE);
    title.setPosition(pos.x + 15, pos.y - 12); 

    sf::RectangleShape mask(sf::Vector2f(title.getGlobalBounds().width + 10, 4));
    mask.setFillColor(COLOR_BG);
    mask.setPosition(pos.x + 10, pos.y - 2); 

    _window.draw(wrapper.background);
    _window.draw(mask);
    _window.draw(title);
    
    if (name == "Hostname") drawHostname(data, pos, ty);
    else if (name == "Date & Time") drawDateTime(data, pos, ty);
    else if (name == "CPU") drawCpu(wrapper.module, data, pos, ty);
    else if (name == "Network") drawNetwork(data, pos, ty);
    else if (name == "OS & Kernel") drawOS(data, pos, ty);
    else if (name == "RAM") drawRam(data, pos, ty);
    else if (name == "Battery") drawBattery(data, pos, ty);

    wrapper.background.setSize(sf::Vector2f(MOD_WIDTH, ty - pos.y + 10));
}