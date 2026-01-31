#include "TemperatureBox.hpp"
#include <algorithm>

TemperatureBox::TemperatureBox(int x, int y) : _box(newwin(12, 72, y, x)), _countPush(0), _height(12) {}

TemperatureBox::TemperatureBox() : _box(newwin(12, 72, 0, 0)), _countPush(0), _height(12) {}

TemperatureBox::~TemperatureBox() {
    if (_box)
        delwin(_box);
}

WINDOW *TemperatureBox::getWin() const {
    return _box;
}

int TemperatureBox::getHeight() const {
    return _height;
}

void TemperatureBox::setYPos(int y) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, 72, y, 2);
}

int TemperatureBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

std::string TemperatureBox::getModuleNeeded() const {
    return "Temperature";
}

void TemperatureBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();
    
    float currentTemp = std::stof(data.at("Temp"));
    
    _countPush++;
    if (_countPush > 1500) {
        _prevData.push_back(currentTemp);
        _countPush = 0;
    }
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
    int startY = 9;
    int startX = 6;

    float minT = 30.0;
    float maxT = 90.0;

    for (size_t i = 0; i < _prevData.size() ; i++) {
        float val = _prevData[i];
        
        int pointY = (int)((val - minT) / (maxT - minT) * graphHeight);
        if (pointY < 1 && val > 0) pointY = 1;
        if (pointY > graphHeight) pointY = graphHeight;

        int pair = 3;
        if (pointY > 4) pair = 1;
        else if (pointY > 2) pair = 2;

        for (int h = 0; h < pointY; h++) {
            wattron(_box, COLOR_PAIR(pair));
            mvwprintw(_box, startY - h, startX + i, "o");
            wattroff(_box, COLOR_PAIR(pair));
        }
    }

    for (int h = 0; h <= graphHeight; h++) mvwprintw(_box, startY - h, startX - 1, "|");
    for (int w = 0; w < graphWidth; w++) mvwprintw(_box, startY + 1, startX + w, "-");

    wnoutrefresh(_box);
}