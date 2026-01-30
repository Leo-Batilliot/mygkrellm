#include "SfmlDisplay.hpp"

void SfmlDisplay::renderStaticStack(float &currentY, sf::Vector2i mousePos)
{
    for (int i = 0; i < (int)_modules.size(); ++i) {
        if (!_modules[i].isVisible || i == _draggedIdx)
            continue;

        if (_draggedIdx != -1 && _targetIdx == -1) {
            float mid = currentY + (_modules[i].background.getSize().y / 2.0f);
            if (mousePos.y < mid)
                _targetIdx = i;
        }

        drawModule(_modules[i], sf::Vector2f(START_X, currentY));
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
    line.setPosition(START_X, py - (MOD_MARGIN / 2.0f) - 1);
    _window.draw(line);
}

void SfmlDisplay::renderDraggedModule(sf::Vector2i mousePos)
{
    auto &m = _modules[_draggedIdx];
    sf::Vector2f dragPos = sf::Vector2f(mousePos.x, mousePos.y) + _dragOffset;

    m.background.setFillColor(COLOR_DRAG);
    m.background.setOutlineThickness(BORDER_THICKNESS * 2);
    m.background.setOutlineColor(sf::Color::White);

    drawModule(m, dragPos);
}

void SfmlDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    syncModules(modules);
    _window.clear(COLOR_BG);
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
    float currentY = START_Y;
    _targetIdx = -1;

    renderStaticStack(currentY, mousePos);

    if (_draggedIdx != -1)
        renderPreviewLine();

    if (_draggedIdx != -1)
        renderDraggedModule(mousePos);

    _window.display();
}

static void drawHostname(sf::RenderWindow& window, sf::Font& font, const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    // Hostname
    sf::Text labelH("Host:", font, 16);
    labelH.setPosition(pos.x + 20, ty);
    labelH.setFillColor(COLOR_LABEL);
    window.draw(labelH);

    sf::Text valH(data.at("Hostname"), font, 16);
    valH.setPosition(pos.x + VALUE_X_OFFSET, ty);
    valH.setFillColor(COLOR_VALUE);
    window.draw(valH);
    ty += 22;

    // Username
    sf::Text labelU("User:", font, 16);
    labelU.setPosition(pos.x + 20, ty);
    labelU.setFillColor(COLOR_LABEL);
    window.draw(labelU);

    sf::Text valU(data.at("Username"), font, 16);
    valU.setPosition(pos.x + VALUE_X_OFFSET, ty);
    valU.setFillColor(COLOR_VALUE);
    window.draw(valU);
    ty += 22;
}

static void drawDateTime(sf::RenderWindow& window, sf::Font& font, const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    // Date
    sf::Text labelD("Date:", font, 16);
    labelD.setPosition(pos.x + 20, ty);
    labelD.setFillColor(COLOR_LABEL);
    window.draw(labelD);

    sf::Text valD(data.at("Date"), font, 16);
    valD.setPosition(pos.x + VALUE_X_OFFSET, ty);
    valD.setFillColor(COLOR_VALUE);
    window.draw(valD);
    ty += 22;

    sf::Text labelT("Time:", font, 16);
    labelT.setPosition(pos.x + 20, ty);
    labelT.setFillColor(COLOR_LABEL);
    window.draw(labelT);

    sf::Text valT(data.at("Time"), font, 16);
    valT.setPosition(pos.x + VALUE_X_OFFSET, ty);
    valT.setFillColor(COLOR_VALUE);
    window.draw(valT);
    ty += 22;
}

static void drawCpu(sf::RenderWindow& window, sf::Font& font, const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    const char* labels[] = {"Model:", "Frequence:", "Cores:", "Usage:"};
    const char* keys[] = {"Model", "Frequency", "Cores", "Usage"};

    for (int i = 0; i < 4; i++) {
        sf::Text label(labels[i], font, 16);
        label.setPosition(pos.x + 20, ty);
        label.setFillColor(COLOR_LABEL);
        window.draw(label);

        sf::Text val(data.at(keys[i]), font, 16);
        val.setPosition(pos.x + VALUE_X_OFFSET, ty);
        val.setFillColor(i != 3 ? COLOR_VALUE : sf::Color(255 * std::stof(data.at("Usage")) / 100, 255 * (100 - std::stof(data.at("Usage"))) / 100, 0));
        window.draw(val);

        if (i == 3) {
            float usage = std::stof(data.at("Usage"));
            sf::RectangleShape barBg(sf::Vector2f(180, 12));
            barBg.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
            barBg.setFillColor(sf::Color(80, 80, 80));
            window.draw(barBg);

            sf::RectangleShape barFill(sf::Vector2f(1.8f * usage, 12));
            barFill.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
            barFill.setFillColor(sf::Color(255 * usage / 100, 255 * (100 - usage) / 100, 0));
            window.draw(barFill);
        }
        ty += 25;
    }
}

void SfmlDisplay::drawModule(ModuleWrapper &wrapper, sf::Vector2f pos)
{
    std::string name = wrapper.module->getName();
    const auto &data = wrapper.module->getData();
    float ty = pos.y + 40;

    wrapper.background.setPosition(pos);

    if (!(_draggedIdx != -1 && &wrapper == &_modules[_draggedIdx])) {
        wrapper.background.setFillColor(COLOR_MOD_FILL);
        wrapper.background.setOutlineThickness(BORDER_THICKNESS);
        wrapper.background.setOutlineColor(COLOR_MOD_BORDER);
    }

    _window.draw(wrapper.background);

    sf::Text title(name, _font, 20);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(COLOR_TITLE);
    title.setPosition(pos.x + 10, pos.y + 5);
    _window.draw(title);
    
    if (name == "Hostname")
        drawHostname(_window, _font, data, pos, ty);
    else if (name == "Date & Time")
        drawDateTime(_window, _font, data, pos, ty);
    else if (name == "CPU")
        drawCpu(_window, _font, data, pos, ty);
    wrapper.background.setSize(sf::Vector2f(MOD_WIDTH, ty - pos.y + 10));
}