#include "SfmlDisplay.hpp"

#include "SfmlDisplay.hpp"
#include "modules/CpuModule.hpp"

void SfmlDisplay::drawCpu(Krell::IModule *module, const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty)
{
    sf::Text label_model("Model", _font, 16);
    label_model.setPosition(pos.x + 20, ty);
    label_model.setFillColor(COLOR_LABEL);
    _window.draw(label_model);

    sf::Text value_model(safeGet(data, "Model"), _font, 16);
    value_model.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_model.setFillColor(COLOR_VALUE);
    _window.draw(value_model);
    ty += 22;

    sf::Text label_frequence("Frequence", _font, 16);
    label_frequence.setPosition(pos.x + 20, ty);
    label_frequence.setFillColor(COLOR_LABEL);
    _window.draw(label_frequence);

    sf::Text value_frequence(safeGet(data, "Frequency"), _font, 16);
    value_frequence.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_frequence.setFillColor(COLOR_VALUE);
    _window.draw(value_frequence);
    ty += 22;

    sf::Text label_cores("Cores", _font, 16);
    label_cores.setPosition(pos.x + 20, ty);
    label_cores.setFillColor(COLOR_LABEL);
    _window.draw(label_cores);

    sf::Text value_cores(safeGet(data, "Cores"), _font, 16);
    value_cores.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_cores.setFillColor(COLOR_VALUE);
    _window.draw(value_cores);
    ty += 22;

    float usage = std::stof(safeGet(data, "Usage"));
    sf::Color usageColor(255 * usage / 100, 255 * (100 - usage) / 100, 0);

    sf::Text label_usage("Total Usage", _font, 16);
    label_usage.setPosition(pos.x + 20, ty);
    label_usage.setFillColor(COLOR_LABEL);
    _window.draw(label_usage);

    sf::Text value_usage(safeGet(data, "Usage"), _font, 16);
    value_usage.setPosition(pos.x + VALUE_X_OFFSET, ty);
    value_usage.setFillColor(usageColor);
    _window.draw(value_usage);

    sf::RectangleShape bar_rectangle(sf::Vector2f(270, 12));
    bar_rectangle.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
    bar_rectangle.setFillColor(sf::Color(80, 80, 80));
    _window.draw(bar_rectangle);

    sf::RectangleShape bar_color(sf::Vector2f(2.7f * usage, 12));
    bar_color.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
    bar_color.setFillColor(usageColor);
    _window.draw(bar_color);
    ty += 35;

    CpuModule* cpuMod = dynamic_cast<CpuModule*>(module); 
    if (cpuMod) {
        auto &cores = cpuMod->getCoreUsage();
        int nbCores = std::stoi(safeGet(data, "Cores"));

        for (int i = 0; i < nbCores; i++) {
            std::string coreName = "cpu" + std::to_string(i);
            
            if (cores.find(coreName) == cores.end())
                continue;

            std::string value = cores.at(coreName);
            float usage = std::stof(value);
            sf::Color gradient_color(255 * usage / 100, 255 * (100 - usage) / 100, 0);

            sf::Text label_core("Core " + std::to_string(i + 1), _font, 14);
            label_core.setPosition(pos.x + 40, ty);
            label_core.setFillColor(COLOR_LABEL);
            _window.draw(label_core);

            sf::Text value_core(value, _font, 14);
            value_core.setPosition(pos.x + VALUE_X_OFFSET, ty);
            value_core.setFillColor(gradient_color);
            _window.draw(value_core);

            sf::RectangleShape cBarBg(sf::Vector2f(270, 8));
            cBarBg.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
            cBarBg.setFillColor(sf::Color(60, 60, 60));
            _window.draw(cBarBg);

            sf::RectangleShape cBarFill(sf::Vector2f(2.7f * usage, 8));
            cBarFill.setPosition(pos.x + VALUE_X_OFFSET + 80, ty + 4);
            cBarFill.setFillColor(gradient_color);
            _window.draw(cBarFill);

            ty += 18; 
        }
    }
}