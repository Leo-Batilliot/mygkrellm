/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "NetworkBox.hpp"
#include <iostream>

NetworkBox::NetworkBox(int x, int y) : _box(newwin(25, 75, y, x)), _downloadHisto{}, _updateHisto{}, _lastUpdate(time(nullptr)) {}

NetworkBox::~NetworkBox()
{
    if (_box)
        delwin(_box);
}

std::string NetworkBox::getModuleNeeded() const {
    return "Network";
}

WINDOW *NetworkBox::getWin() const {
    return _box;
}

void NetworkBox::display(Krell::IModule *module) {
    if (!_box) return;
    const std::map<std::string, std::string> data = module->getData();
    constexpr std::size_t MAX_HISTO = 68;
    time_t now = time(nullptr);

    int download = stoi(data.at("Download"));
    int upload = stoi(data.at("Upload"));

    if (_highestDL < download) {
        _highestDL = download;
    }

    if (_highestUP < upload) {
        _highestUP = upload;
    }

    if (_updateHisto.empty()) {
        _downloadHisto.push_back(download);
        _updateHisto.push_back(upload);
    }
    else if (now != _lastUpdate) {
        _updateHisto.push_back(upload);
        _downloadHisto.push_back(download);
        _lastUpdate = now;
    }
    if (_downloadHisto.size() > MAX_HISTO)
        _downloadHisto.pop_front();
    if (_updateHisto.size() > MAX_HISTO)
        _updateHisto.pop_front();

    werase(_box);
    box(_box, 0, 0);
    
    // Titre
    wattron(_box, A_BOLD);
    mvwprintw(_box, 0, 4, "=");
    wattron(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 5, " Network ");
    wattroff(_box, COLOR_PAIR(1));
    mvwprintw(_box, 0, 15, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 1, 1, "Download: %s | Highest: %i", data.at("Download").c_str(), _highestDL);
    mvwprintw(_box, 2, 1, "100|");
    mvwprintw(_box, 6, 1, "50 |");
    mvwprintw(_box, 11, 1, "0  |");
    mvwprintw(_box, 12, 1, "Upload: %s | Highest: %i", data.at("Upload").c_str(), _highestUP);
    mvwprintw(_box, 13, 1, "100|");
    mvwprintw(_box, 18, 1, "50 |");
    mvwprintw(_box, 23, 1, "0  |");

    for (size_t i = 0; i < _downloadHisto.size(); i++) {
        int height = (_downloadHisto[i]) % 10;
        for (int j = 0; j < height; j++) {
            mvwprintw(_box, 11 - j, i + 5, "=");
        }
    }

    for (size_t i = 0; i < _updateHisto.size(); i++) {
        int height = (_updateHisto[i]) % 10;
        for (int j = 0; j < height; j++) {
            mvwprintw(_box, 23 - j, i + 5, "=");
        }
    }
    
    wnoutrefresh(_box);
}