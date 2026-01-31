/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "HostnameBox.hpp"

HostnameBox::HostnameBox(int x, int y) : _box(newwin(5, 45, y, x)) {}

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

void HostnameBox::display(Krell::IModule *module) {
    if (!_box) return;
    const std::map<std::string, std::string> data = module->getData();

    std::string hostname = data.at("Hostname");
    std::string username = data.at("Username");

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