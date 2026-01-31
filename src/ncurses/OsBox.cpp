/*
** EPITECH PROJECT, 2026
** OsBox
** File description:
** functions of OsBox
*/

#include "OsBox.hpp"

OsBox::OsBox(int x, int y) : _box(newwin(7, 72, y, x)) {}

OsBox::~OsBox() override {
    if (_box)
        delwin(_box);
}

std::string OsBox::getModuleNeeded() const override {
    return "OS & Kernel";
}

WINDOW *OsBox::getWin() const override {
    return _box;
}

void OsBox::display(Krell::IModule *module) override {
    if (!_box || !module) return;
    const std::map<std::string, std::string> &data = module->getData();

    werase(_box);
    box(_box, 0, 0);
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " OS & Kernel ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 19, "=");
    wattroff(_box, A_BOLD);
    mvwprintw(_box, 1, 2, " %s ", module->getName().c_str());
    int line = 2;
    for (auto const& [key, value] : data) {
        wattron(_box, A_BOLD);
        mvwprintw(_box, line, 2, "%s:", key.c_str());
        wattroff(_box, A_BOLD);
        mvwprintw(_box, line, 2 + key.length() + 2, "%s", value.c_str());
        line++;
    }
    wrefresh(_box);
}