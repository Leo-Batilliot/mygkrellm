/*
** EPITECH PROJECT, 2026
** UptimeBox
** File description:
** functions of UptimeBox
*/

#include "UptimeBox.hpp"

UptimeBox::UptimeBox(int x, int y) : _box(newwin(5, 72, y, x)), _height(5) {}

UptimeBox::~UptimeBox() {
    if (_box)
        delwin(_box);
}

void UptimeBox::setYPos(int y) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, 72, y, 2);
}

int UptimeBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

int UptimeBox::getHeight() const {
    return _height;
}

WINDOW *UptimeBox::getWin() const {
    return _box;
}
    
std::string UptimeBox::getModuleNeeded() const {
    return "Uptime";
}

void UptimeBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();

    std::string uptime = data.count("Uptime") ? data.at("Uptime") : "Unknown";

    werase(_box);
    box(_box, 0, 0);
    
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " UPTIME ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 13, "=");
    wattroff(_box, A_BOLD);

    wattron(_box, A_BOLD);
    mvwprintw(_box, 2, 3, "System has been running for:");
    wattroff(_box, A_BOLD);
    
    wattron(_box, A_BOLD);
    mvwprintw(_box, 2, 32, "%s", uptime.c_str());
    wattroff(_box, A_BOLD);

    wnoutrefresh(_box);
}
