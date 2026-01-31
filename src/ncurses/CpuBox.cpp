/*
** EPITECH PROJECT, 2026
** CpuBox
** File description:
** functions of CpuBox
*/

#include "CpuBox.hpp"

CpuBox::CpuBox(int x, int y) : _box(newwin(16, 75, y, x)) {}

CpuBox::~CpuBox() {
    if (_box)
        delwin(_box);
}

WINDOW *CpuBox::getWin() const {
    return _box;
}

std::string CpuBox::getModuleNeeded() const {
    return "Cpu";
}

void CpuBox::display(Krell::IModule *module) {
     if (!_box)
        return;
    CpuModule *cpuModule = dynamic_cast<CpuModule *>(module);
    if (!cpuModule)
        return;
    const std::map<std::string, std::string> data = cpuModule->getData();
    std::string model = data.at("Model");
    double frequency = std::stod(data.at("Frequency"));
    float percent = std::stof(data.at("Percent"));


    werase(_box);
    box(_box, 0, 0);
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " CPU ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 10, "=");
    wattroff(_box, A_BOLD);
    mvwprintw(_box, 2, 3, "Model : %s", data.at("Model").c_str());
    mvwprintw(_box, 3, 3, "Freq  : %s", data.at("Frequency").c_str());
    mvwprintw(_box, 3, 35, "Cores : %s", data.at("Cores").c_str());

    float globalUsage = std::stof(data.at("Usage"));
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
    std::map<std::string, std::string> &coresUsage = cpuModule->getCoreUsage();
    for (auto const& [core, usage] : coresUsage) {
        int xPos = (col % 2 == 0) ? 3 : 35;
        mvwprintw(_box, row + (col / 2), xPos, "%s: %s", core.c_str(), usage.c_str());
        col++;
    }

    wrefresh(_box);
}