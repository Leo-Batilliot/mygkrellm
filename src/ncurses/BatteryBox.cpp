/*
** EPITECH PROJECT, 2026
** BatteryBox
** File description:
** functions of BatteryBox
*/

#include "BatteryBox.hpp"

BatteryBox::BatteryBox(int x, int y) : _box(newwin(7, 72, y, x)), _height(7) {}

BatteryBox::BatteryBox() : _box(newwin(7, 72, 0, 0)), _height(7) {}

BatteryBox::~BatteryBox() {
    if (_box)
        delwin(_box);
}

WINDOW *BatteryBox::getWin() const {
    return _box;
}

std::string BatteryBox::getModuleNeeded() const {
    return "Battery";
}

int BatteryBox::getHeight() const {
    return _height;
}

void BatteryBox::setYPos(int y, int width) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, width, y, 0);
}

int BatteryBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

void BatteryBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    int winW, winH;
    getmaxyx(_box, winH, winW);
    (void)winH;
    const std::map<std::string, std::string> &data = module->getData();

    std::string status = safeGet(data, "Status");
    std::string levelStr = safeGet(data, "Level");
    
    float percent = 0;
    try {
        percent = std::stof(levelStr);
    } catch (...) {
        percent = 0;
    }

    werase(_box);
    box(_box, 0, 0);
    
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " BATTERY ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 14, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 2, 3, "Status: %-15s | Level: %s", status.c_str(), levelStr.c_str());

    mvwprintw(_box, 4, 4, "[");
    int barSize = 50;
    
    for (int i = 0; i < barSize; i++) {
        int pair = 1;
        if (i < (barSize * 0.20)) pair = 1;
        else if (i < (barSize * 0.50)) pair = 2;
        else pair = 3;

        wattron(_box, COLOR_PAIR(pair));
        char c = (i < (percent / 100.0 * barSize) || levelStr == "Online") ? '|' : '.';
        mvwprintw(_box, 4, i + 6, "%c", c);
        wattroff(_box, COLOR_PAIR(pair));
    }
    
    if (levelStr == "Online" || levelStr == "Offline")
        mvwprintw(_box, 4, 7 + barSize, "]    %s", levelStr.c_str());
    else
        mvwprintw(_box, 4, 7 + barSize, "]    %.1f%%", percent);
    wnoutrefresh(_box);
}
