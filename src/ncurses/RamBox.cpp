/*
** EPITECH PROJECT, 2026
** RamBox
** File description:
** functions of RamBox
*/

#include "RamBox.hpp"

RamBox::RamBox(int x, int y) : _box(newwin(7, 72, y, x)) {}

RamBox::~RamBox() {
    if (_box)
        delwin(_box);
}

WINDOW *RamBox::getWin() const {
    return _box;
}

void RamBox::display(Krell::IModule *module) {
    if (!_box)
        return;
    const std::map<std::string, std::string> data = module->getData();
    int totalUsage = std::stoi(data.at("Used"));
    int total = std::stoi(data.at("Total"));
    float percent = std::stof(data.at("Percent"));

    werase(_box);
    box(_box, 0, 0);
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " RAM ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 10, "=");
    wattroff(_box, A_BOLD);
    mvwprintw(_box, 2, 3, "Ram Usage: %d Mb /%d Mb | %d free.", totalUsage, total, (total - totalUsage));
    mvwprintw(_box, 4, 4, "[");
    int barSize = 50;
    for (int i = 0; i < barSize; i++) {
        if (i < (float)barSize / 2.3)
            wattron(_box, COLOR_PAIR(3));
        else if (i < ((float)barSize / 3) * 2.3)
            wattron(_box, COLOR_PAIR(2));
        else
            wattron(_box, COLOR_PAIR(1));
        char c = i >= (percent / 100.0 * barSize) ? '.' : '|';;
        mvwprintw(_box, 4, i+6, "%c", c);
        wattroff(_box, COLOR_PAIR(1));
        wattroff(_box, COLOR_PAIR(2));
        wattroff(_box, COLOR_PAIR(3));
    }
    mvwprintw(_box, 4, 7+barSize, "]    %.2f%%", percent);
    wrefresh(_box);
}