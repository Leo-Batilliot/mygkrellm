/*
** EPITECH PROJECT, 2026
** CpuWindow
** File description:
** functions of CpuWindow
*/

#include "CpuWindow.hpp"

CpuWindow::CpuWindow() : _CpuWin(nullptr) {}

CpuWindow::~CpuWindow() {}

void CpuWindow::displayCpuMod() {
     if (!_CpuWin)
        _CpuWin = newwin(7, 72, 2, 2);
    const std::map<std::string, std::string> data = getData();
    std::string model = data.at("Model");
    double frequency = std::stod(data.at("Frequency"));
    float percent = std::stof(data.at("Percent"));


    werase(_CpuWin);
    box(_CpuWin, 0, 0);
    wattron(_CpuWin, A_BOLD);
    mvwprintw(_CpuWin, 0, 4, "=");
    wattron(_CpuWin, COLOR_PAIR(1));
    mvwprintw(_CpuWin, 0, 5, " CPU ");
    wattroff(_CpuWin, COLOR_PAIR(1));
    mvwprintw(_CpuWin, 0, 10, "=");
    wattroff(_CpuWin, A_BOLD);
    mvwprintw(_CpuWin, 2, 3, "Model : %s", data.at("Model").c_str());
    mvwprintw(_CpuWin, 3, 3, "Freq  : %s", data.at("Frequency").c_str());
    mvwprintw(_CpuWin, 3, 35, "Cores : %s", data.at("Cores").c_str());

    float globalUsage = std::stof(data.at("Usage"));
    mvwprintw(_CpuWin, 5, 3, "Usage: [");
    
    int barSize = 50;
    int filled = (int)((globalUsage / 100.0f) * barSize);

    for (int i = 0; i < barSize; i++) {
        if (i < filled) {
            if (i < barSize * 0.5) wattron(_CpuWin, COLOR_PAIR(3));
            else if (i < barSize * 0.8) wattron(_CpuWin, COLOR_PAIR(2));
            else wattron(_CpuWin, COLOR_PAIR(1));
            mvwaddch(_CpuWin, 5, i + 11, '|');
            wattroff(_CpuWin, COLOR_PAIR(1) | COLOR_PAIR(2) | COLOR_PAIR(3));
        } else {
            mvwaddch(_CpuWin, 5, i + 11, '.');
        }
    }
    mvwprintw(_CpuWin, 5, 12 + barSize, "] %.1f%%", globalUsage);
    int row = 7;
    int col = 0;
    std::map<std::string, std::string> &coresUsage = getCoreUsage();
    for (auto const& [core, usage] : coresUsage) {
        int xPos = (col % 2 == 0) ? 3 : 35;
        mvwprintw(_CpuWin, row + (col / 2), xPos, "%s: %s", core.c_str(), usage.c_str());
        col++;
    }

    wrefresh(_CpuWin);
}