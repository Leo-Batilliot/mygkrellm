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

std::string RamBox::getModuleNeeded() const {
    return "RAM";
}

WINDOW *RamBox::getWin() const {
    return _box;
}

void RamBox::display(Krell::IModule *module) {
    if (!_box) return;
    const std::map<std::string, std::string> data = module->getData();

    float totalUsage = std::stof(data.at("Used"));
    float total = std::stof(data.at("Total"));
    float percent = std::stof(data.at("Percent"));
    float free = total - totalUsage;

    werase(_box);
    wnoutrefresh(_box);
    box(_box, 0, 0);
    
    // Titre
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " RAM ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 10, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 2, 3, "Ram Usage: %.1f GB / %.1f GB | %.1f free", totalUsage, total, free);

    mvwprintw(_box, 4, 4, "[");
    int barSize = 50;
    for (int i = 0; i < barSize; i++) {
        int pair = 3;
        if (i >= (barSize * 0.66)) pair = 1;
        else if (i >= (barSize * 0.33)) pair = 2;

        wattron(_box, COLOR_PAIR(pair));
        char c = (i < (percent / 100.0 * barSize)) ? '|' : '.';
        mvwprintw(_box, 4, i + 6, "%c", c);
        wattroff(_box, COLOR_PAIR(pair));
    }
    mvwprintw(_box, 4, 7 + barSize, "]    %.2f%%", percent);
    wnoutrefresh(_box);
}