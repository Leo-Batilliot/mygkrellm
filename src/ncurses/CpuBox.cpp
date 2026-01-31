/*
** EPITECH PROJECT, 2026
** CpuBox
** File description:
** functions of CpuBox
*/

#include "CpuBox.hpp"

CpuBox::CpuBox(int x, int y) : _box(newwin(16, 72, y, x)), _height(16) {}

CpuBox::CpuBox() : _box(newwin(16, 72, 0, 0)), _height(16) {}

CpuBox::~CpuBox() {
    if (_box)
        delwin(_box);
}

WINDOW *CpuBox::getWin() const {
    return _box;
}

int CpuBox::getHeight() const {
    return _height;
}

void CpuBox::setYPos(int y, int width) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, width, y, 0);
}

int CpuBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

std::string CpuBox::getModuleNeeded() const {
    return "CPU";
}

void CpuBox::display(Krell::IModule *module) {
     if (!_box)
        return;
    CpuModule *cpuModule = dynamic_cast<CpuModule *>(module);
    if (!cpuModule)
        return;
    int winW, winH;
    getmaxyx(_box, winH, winW);
    (void)winH;
    const std::map<std::string, std::string> data = cpuModule->getData();
    std::string model = safeGet(data, "Model");

    std::map<std::string, std::string> &coresUsage = cpuModule->getCoreUsage();
    int nbCores = coresUsage.size();
    int height = 8 + (nbCores / 2) + (nbCores % 2);
    wresize(_box, height + 1, winW);
    _height = height + 1;

    wnoutrefresh(_box);
    werase(_box);
    box(_box, 0, 0);
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " CPU ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 10, "=");
    wattroff(_box, A_BOLD);
    mvwprintw(_box, 2, 3, "Model : %s", safeGet(data, "Model").c_str());
    mvwprintw(_box, 3, 3, "Freq  : %s", safeGet(data, "Frequency").c_str());
    mvwprintw(_box, 3, 35, "Cores : %s", safeGet(data, "Cores").c_str());

    float globalUsage = std::stof(safeGet(data, "Usage"));
    mvwprintw(_box, 5, 3, "Usage: [");
    
    int barSize = 50;
    int filled = (int)((globalUsage / 100.0f) * barSize);

    for (int i = 0; i < barSize; i++) {
        if (i < filled) {
            if (i < barSize * 0.5) wattron(_box, COLOR_PAIR(3));
            else if (i < barSize * 0.8) wattron(_box, COLOR_PAIR(2));
            else wattron(_box, COLOR_PAIR(1));
            mvwaddch(_box, 5, i + 11, '|');
            wattroff(_box, COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
        } else {
            mvwaddch(_box, 5, i + 11, '.');
        }
    }
    mvwprintw(_box, 5, 12 + barSize, "] %.1f%%", globalUsage);
    int row = 7;
    int col = 0;
    for (auto const& [core, usage] : coresUsage) {
        int xPos = (col % 2 == 0) ? 3 : 35;
        mvwprintw(_box, row + (col / 2), xPos, "%s: %s", core.c_str(), usage.c_str());
        col++;
    }

    wnoutrefresh(_box);
}