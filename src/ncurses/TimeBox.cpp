/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "TimeBox.hpp"

TimeBox::TimeBox(int x, int y) : _box(newwin(5, 72, y, x)), _height(5) {}

TimeBox::TimeBox() : _box(newwin(5, 72, 0, 0)), _height(5) {}

TimeBox::~TimeBox()
{
    if (_box)
        delwin(_box);
}

int TimeBox::getHeight() const {
    return _height;
}

void TimeBox::setYPos(int y) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, 72, y, 2);
}

int TimeBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

std::string TimeBox::getModuleNeeded() const {
    return "Date & Time";
}

WINDOW *TimeBox::getWin() const {
    return _box;
}

void TimeBox::display(Krell::IModule *module) {
    if (!_box) return;
    const std::map<std::string, std::string> data = module->getData();

    std::string date = data.at("Date");
    std::string time = data.at("Time");

    werase(_box);
    box(_box, 0, 0);
    
    // Titre
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " Date & Time ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 18, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 1, 2, "Date: %s", date.c_str());
    mvwprintw(_box, 2, 2, "Time: %s", time.c_str());
    
    wnoutrefresh(_box);
}