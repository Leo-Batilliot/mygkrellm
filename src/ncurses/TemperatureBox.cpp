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

    float currentTemp = data.count("Temp") ? std::stof(data.at("Temp")) : 0.0f;
    _prevData.push_back(currentTemp);
    if (_prevData.size() > 60) _prevData.erase(_prevData.begin());

    werase(_box);
    box(_box, 0, 0);

    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "= TEMPERATURE =");
    wattroff(_box, A_BOLD);
    mvwprintw(_box, 1, 3, "Current: %.1f°C", currentTemp);

    int graphH = 7;
    int graphW = 62;
    int startY = 9;
    int startX = 8;

    mvwprintw(_box, startY - graphH, startX - 4, "90-");
    mvwprintw(_box, startY - (graphH / 2), startX - 4, "60-");
    mvwprintw(_box, startY, startX - 4, "30-");

    for (int i = 0; i <= graphH; i++) mvwaddch(_box, startY - i, startX - 1, ACS_VLINE);
    for (int i = 0; i <= graphW; i++) mvwaddch(_box, startY + 1, startX + i - 1, ACS_HLINE);
    mvwaddch(_box, startY - graphH, startX - 1, '^');
    mvwaddch(_box, startY + 1, startX + graphW, '>');

    float minT = 30.0f;
    float maxT = 90.0f;

    for (size_t i = 0; i < _prevData.size(); i++) {
        int valY = (int)(((_prevData[i] - minT) / (maxT - minT)) * graphH);
        if (valY < 0) valY = 0;
        if (valY > graphH) valY = graphH;

        int pair = 3;
        if (_prevData[i] > 75) pair = 1;
        else if (_prevData[i] > 55) pair = 2;

        wattron(_box, COLOR_PAIR(pair) | A_BOLD);
        
        mvwaddch(_box, startY - valY, startX + i, 'o');

        if (i > 0) {
            int prevY = (int)(((_prevData[i-1] - minT) / (maxT - minT)) * graphH);
            if (prevY < 0) prevY = 0;
            if (prevY > graphH) prevY = graphH;
            
            if (prevY < valY)
                mvwaddch(_box, startY - valY + 1, startX + i, '/');
            else if (prevY > valY)
                mvwaddch(_box, startY - valY - 1, startX + i, '\\');
        }
        wattroff(_box, COLOR_PAIR(pair) | A_BOLD);
    }

    wnoutrefresh(_box);
}