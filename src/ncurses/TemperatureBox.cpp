#include "TemperatureBox.hpp"
#include <algorithm>

TemperatureBox::TemperatureBox(int x, int y) : _box(newwin(10, 72, y, x)) {}

TemperatureBox::~TemperatureBox() {
    if (_box)
        delwin(_box);
}

WINDOW *TemperatureBox::getWin() const {
    return _box;
}

std::string TemperatureBox::getModuleNeeded() const {
    return "Temperature";
}

void TemperatureBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();
    
    float currentTemp = 0.0;
    if (data.count("Temperature")) {
        currentTemp = std::stof(data.at("Temperature"));
    }
    
    _prevData.push_back(currentTemp);
    if (_prevData.size() > 60)
        _prevData.erase(_prevData.begin());

    werase(_box);
    box(_box, 0, 0);

    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " TEMPERATURE ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 18, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 1, 3, "Current: %.1f°C", currentTemp);

    int graphHeight = 6;
    int graphWidth = 60;
    int startY = 8;
    int startX = 6;

    float minT = 30.0;
    float maxT = 90.0;

    for (size_t i = 0; i < _prevData.size(); ++i) {
        float val = _prevData[i];
        
        int barHeight = (int)((val - minT) / (maxT - minT) * graphHeight);
        if (barHeight < 1 && val > 0) barHeight = 1;
        if (barHeight > graphHeight) barHeight = graphHeight;

        for (int h = 0; h < barHeight; ++h) {
            int pair = 3;
            if (val > 75) pair = 1;
            else if (val > 55) pair = 2;

            wattron(_box, COLOR_PAIR(pair));
            mvwaddch(_box, startY - h, startX + i, '|');
            wattroff(_box, COLOR_PAIR(pair));
        }
    }

    for (int h = 0; h <= graphHeight; h++) mvwaddch(_box, startY - h, startX - 1, ACS_VLINE);
    for (int w = 0; w < graphWidth; w++) mvwaddch(_box, startY + 1, startX + w, ACS_HLINE);

    wrefresh(_box);
}