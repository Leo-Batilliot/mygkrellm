/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#include "NetworkBox.hpp"
#include <iostream>

NetworkBox::NetworkBox(int x, int y) : _box(newwin(25, 72, y, x)), _downloadHisto{}, _updateHisto{}, _lastUpdate(time(nullptr)), _height(25) {}

NetworkBox::~NetworkBox()
{
    if (_box)
        delwin(_box);
}

void NetworkBox::setYPos(int y) {
    if (_box)
        delwin(_box);
    _box = newwin(_height, 72, y, 2);
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
    if (!_box) return;
    const std::map<std::string, std::string> data = module->getData();
    constexpr std::size_t MAX_HISTO = 68;
    time_t now = time(nullptr);

    std::string downloadS = data.at("Download");
    std::string uploadS = data.at("Upload");
    bool isKB_DL = (downloadS.find("KB/s") != std::string::npos);
    bool isKB_UP = (uploadS.find("KB/s") != std::string::npos);
    float download = stof(data.at("Download"));
    float upload = stof(data.at("Upload"));

    if (!isKB_DL) {
        download = download * 1000;
    }
    if (!isKB_UP) {
        upload = upload * 1000;
    }

    if (!_downloadHisto.empty()) {
        _highestDL = *std::max_element(
            _downloadHisto.begin(),
            _downloadHisto.end()
        );
    }

    if (!_updateHisto.empty()) {
        _highestUP = *std::max_element(
            _updateHisto.begin(),
            _updateHisto.end()
        );
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
    mvwprintw(_box, 0, 14, "=");
    wattroff(_box, A_BOLD);

    mvwprintw(_box, 1, 1, "Download: %s | Highest: %.0f KB/s", downloadS.c_str(), _highestDL);
    mvwprintw(_box, 2, 1, "100|");
    mvwprintw(_box, 6, 1, " 50|");
    mvwprintw(_box, 11, 1, "  0|");
    mvwprintw(_box, 12, 1, "Upload: %s | Highest: %.0f KB/s", uploadS.c_str(), _highestUP);
    mvwprintw(_box, 13, 1, "100|");
    mvwprintw(_box, 18, 1, " 50|");
    mvwprintw(_box, 23, 1, "  0|");

    for (size_t i = 0; i < _downloadHisto.size(); i++) {
        int v = _downloadHisto[i];
        int height = 0;

        if (_highestDL > 0 && v > 0) {
            height = (v * 10) / _highestDL;
            if (height > 10) height = 10;
        }

        for (int j = 0; j < height; j++) {
            mvwprintw(_box, 11 - j, i + 5, "O");
        }
    }
    for (size_t i = 0; i < _updateHisto.size(); i++) {
        int v = _updateHisto[i];
        int height = 0;

        if (_highestUP > 0 && v > 0) {
            height = (v * 10) / _highestUP;
            if (height > 10) height = 10;
        }

        for (int j = 0; j < height; j++) {
            mvwprintw(_box, 23 - j, i + 5, "O");
        }
    }
    
    wnoutrefresh(_box);
}