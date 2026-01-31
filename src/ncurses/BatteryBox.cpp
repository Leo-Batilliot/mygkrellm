/*
** EPITECH PROJECT, 2026
** BatteryBox
** File description:
** functions of BatteryBox
*/

#include "BatteryBox.hpp"

BatteryBox::BatteryBox(int x, int y) : _box(newwin(7, 72, y, x)) {}

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

void BatteryBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();

    std::string status = data.count("Status") ? data.at("Status") : "Unknown";
    std::string levelStr = data.count("Level") ? data.at("Level") : "0";
    
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
