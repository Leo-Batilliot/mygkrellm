/*
** EPITECH PROJECT, 2026
** RamBox
** File description:
** functions of RamBox
*/

#include "RamBox.hpp"

RamBox::RamBox() : _RamWin(nullptr) {}

RamBox::~RamBox() {
    if (_RamWin)
        delwin(_RamWin);
}

void RamBox::displayRamMod() {
     if (!_RamWin)
        _RamWin = newwin(7, 72, 2, 2);
    const std::map<std::string, std::string> data = getData();
    int totalUsage = std::stoi(data.at("Used"));
    int total = std::stoi(data.at("Total"));
    float percent = std::stof(data.at("Percent"));

    werase(_RamWin);
    box(_RamWin, 0, 0);
    wattron(_RamWin, A_BOLD);
    mvwprintw(_RamWin, 0, 4, "=");
    wattron(_RamWin, COLOR_PAIR(1));
    mvwprintw(_RamWin, 0, 5, " RAM ");
    wattroff(_RamWin, COLOR_PAIR(1));
    mvwprintw(_RamWin, 0, 10, "=");
    wattroff(_RamWin, A_BOLD);
    mvwprintw(_RamWin, 2, 3, "Ram Usage: %d Mb /%d Mb | %d free.", totalUsage, total, (total - totalUsage));
    mvwprintw(_RamWin, 4, 4, "[");
    int barSize = 50;
    for (int i = 0; i < barSize; i++) {
        if (i < (float)barSize / 2.3)
            wattron(_RamWin, COLOR_PAIR(3));
        else if (i < ((float)barSize / 3) * 2.3)
            wattron(_RamWin, COLOR_PAIR(2));
        else
            wattron(_RamWin, COLOR_PAIR(1));
        char c = i >= (percent / 100.0 * barSize) ? '.' : '|';;
        mvwprintw(_RamWin, 4, i+6, "%c", c);
        wattroff(_RamWin, COLOR_PAIR(1));
        wattroff(_RamWin, COLOR_PAIR(2));
        wattroff(_RamWin, COLOR_PAIR(3));
    }
    mvwprintw(_RamWin, 4, 7+barSize, "]    %.2f%%", percent);
    wrefresh(_RamWin);
}