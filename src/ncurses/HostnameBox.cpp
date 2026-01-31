/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "HostnameBox.hpp"

HostnameBox::HostnameBox(int x, int y) : _box(newwin(5, 72, y, x)), _height(5) {}

HostnameBox::HostnameBox() : _box(newwin(5, 72, 0, 0)), _height(5) {}

HostnameBox::~HostnameBox()
{
    if (_box)
        delwin(_box);
}

std::string HostnameBox::getModuleNeeded() const {
    return "Hostname";
}

WINDOW *HostnameBox::getWin() const {
    return _box;
}

int HostnameBox::getHeight() const {
    return _height;
}

void HostnameBox::setYPos(int y, int width) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, width, y, 0);
}

int HostnameBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

void HostnameBox::display(Krell::IModule *module) {
    if (!_box) return;
    int winW, winH;
    getmaxyx(_box, winH, winW);
    (void)winH;
    const std::map<std::string, std::string> data = module->getData();

    std::string hostname = safeGet(data, "Hostname");
    std::string username = safeGet(data, "Username");

    werase(_box);
    box(_box, 0, 0);
    
    // Titre
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " Hostname ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 15, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 1, 2, "Hostname: %s", hostname.c_str());
    mvwprintw(_box, 2, 2, "Username: %s", username.c_str());
    
    wnoutrefresh(_box);
}