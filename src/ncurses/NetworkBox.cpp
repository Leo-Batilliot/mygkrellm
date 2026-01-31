/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "NetworkBox.hpp"
#include <iostream>

NetworkBox::NetworkBox(int x, int y) : _box(newwin(25, 72, y, x)), _downloadHisto{}, _updateHisto{}, _lastUpdate(time(nullptr)), _height(25) {}

NetworkBox::NetworkBox() : _box(newwin(25, 72, 0, 0)), _downloadHisto{}, _updateHisto{}, _lastUpdate(time(nullptr)), _height(25) {}

NetworkBox::~NetworkBox()
{
    if (_box)
        delwin(_box);
}

void NetworkBox::setYPos(int y, int width) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, width, y, 0);
}

int NetworkBox::getYPos() const {
    if (!_box) return 0;
    return getbegy(_box);
}

int NetworkBox::getHeight() const {
    return _height;
}

std::string NetworkBox::getModuleNeeded() const {
    return "Network";
}

WINDOW *NetworkBox::getWin() const {
    return _box;
}

void NetworkBox::display(Krell::IModule *module) {
    if (!_box || !module) return;
    int winW, winH;
    getmaxyx(_box, winH, winW);
    (void)winH;
    const std::map<std::string, std::string> data = module->getData();
    
    int graphWidth = winW - 7; 
    int endCol = winW - 2;     
    time_t now = time(nullptr);

    auto toKB = [](const std::string& val) -> float {
        try {
            float f = std::stof(val);
            if (val.find("MB/s") != std::string::npos) return f * 1024.0f;
            if (val.find("GB/s") != std::string::npos) return f * 1024.0f * 1024.0f;
            return f;
        } catch (...) { return 0; }
    };

    float currentDL = toKB(safeGet(data, "Download"));
    float currentUP = toKB(safeGet(data, "Upload"));

    if (now != _lastUpdate || _downloadHisto.empty()) {
        _downloadHisto.push_back(currentDL);
        _updateHisto.push_back(currentUP);
        _lastUpdate = now;
        if ((int)_downloadHisto.size() > graphWidth) _downloadHisto.pop_front();
        if ((int)_updateHisto.size() > graphWidth) _updateHisto.pop_front();
    }

    _highestDL = 0; _highestUP = 0;
    for (float v : _downloadHisto) if (v > _highestDL) _highestDL = v;
    for (float v : _updateHisto) if (v > _highestUP) _highestUP = v;

    werase(_box);
    box(_box, 0, 0);

    wattron(_box, A_BOLD | COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " Network ");
    wattroff(_box, A_BOLD | COLOR_PAIR(1));

    auto formatUnit = [](float kb) -> std::string {
        if (kb >= 1024.0f) return std::to_string(kb / 1024.0f).substr(0, 4) + " MB/s";
        return std::to_string(kb).substr(0, 4) + " KB/s";
    };

    mvwprintw(_box, 1, 1, "Download: %s | Highest: %s", safeGet(data, "Download").c_str(), formatUnit(_highestDL).c_str());
    mvwprintw(_box, 2, 1, "100|");
    mvwprintw(_box, 6, 1, " 50|");
    mvwprintw(_box, 11, 1, "  0|");

    mvwprintw(_box, 12, 1, "Upload: %s | Highest: %s", safeGet(data, "Upload").c_str(), formatUnit(_highestUP).c_str());
    mvwprintw(_box, 13, 1, "100|");
    mvwprintw(_box, 18, 1, " 50|");
    mvwprintw(_box, 23, 1, "  0|");

    for (int i = 0; i < (int)_downloadHisto.size(); i++) {
        float valDL = *(_downloadHisto.rbegin() + i);
        float valUP = *(_updateHisto.rbegin() + i);
        int xPos = endCol - i;
        if (xPos < 6) break;

        int hDL = (int)((std::min(valDL, 100.0f) / 100.0f) * 9);
        for (int j = 0; j <= hDL; j++) mvwaddch(_box, 11 - j, xPos, 'O');

        int hUP = (int)((std::min(valUP, 100.0f) / 100.0f) * 9);
        for (int j = 0; j <= hUP; j++) mvwaddch(_box, 23 - j, xPos, 'O');
    }

    wnoutrefresh(_box);
}