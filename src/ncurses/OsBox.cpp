/*
** EPITECH PROJECT, 2026
** OsBox
** File description:
** functions of OsBox
*/

#include "OsBox.hpp"

OsBox::OsBox(int x, int y) : _box(newwin(5, 72, y, x)), _height(5) {}

OsBox::OsBox() : _box(newwin(5, 72, 0, 0)), _height(5) {}

OsBox::~OsBox() {
    if (_box)
        delwin(_box);
}

std::string OsBox::getModuleNeeded() const {
    return "OS & Kernel";
}

int OsBox::getHeight() const {
    return _height;
}

WINDOW *OsBox::getWin() const {
    return _box;
}

void OsBox::setYPos(int y, int width) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, width, y, 0);
}

int OsBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

void OsBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();
    werase(_box);
    wattrset(_box, A_NORMAL);
    box(_box, 0, 0);

    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " OS & Kernel ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 18, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 2, 2, "Kernel: %s", safeGet(data, "Kernel").c_str());
    mvwprintw(_box, 3, 2, "Operating system: %s", safeGet(data, "Operating system").c_str());

    wnoutrefresh(_box);
}