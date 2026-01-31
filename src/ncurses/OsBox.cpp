/*
** EPITECH PROJECT, 2026
** OsBox
** File description:
** functions of OsBox
*/

#include "OsBox.hpp"

OsBox::OsBox(int x, int y) : _box(newwin(5, 72, y, x)), _height(5) {}

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

void OsBox::setYPos(int y) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, 72, y, 2);
}

int OsBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

void OsBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();

    werase(_box);
    box(_box, 0, 0);
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " OS & Kernel ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 18, "=");
    wattroff(_box, A_BOLD);
    int line = 1;
    for (auto const& [key, value] : data) {
        wattron(_box, A_BOLD);
        mvwprintw(_box, line, 2, "%s:", key.c_str());
        wattroff(_box, A_BOLD);
        mvwprintw(_box, line, 2 + key.length() + 2, "%s", value.c_str());
        line++;
    }
    wnoutrefresh(_box);
}