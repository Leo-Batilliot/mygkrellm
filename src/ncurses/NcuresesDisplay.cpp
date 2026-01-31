#include <ncurses.h>
#include "ncurses/NcursesDisplay.hpp"
#include "modules/DateTime.hpp"
#include "modules/Hostname.hpp"
#include "iostream"
#include "ncurses/RamBox.hpp"
#include "ncurses/CpuBox.hpp"
#include "ncurses/TimeBox.hpp"
#include "ncurses/HostnameBox.hpp"
#include "ncurses/NetworkBox.hpp"
#include "ncurses/OsBox.hpp"
#include "ncurses/BatteryBox.hpp"
#include "ncurses/UptimeBox.hpp"
#include "ncurses/TemperatureBox.hpp"
#include "ncurses/DiskBox.hpp"
#include "ncurses/IBox.hpp"

NcursesDisplay::~NcursesDisplay()
{
    stop();
}

void NcursesDisplay::init()
{
    initscr();
    noecho();
    raw();
    curs_set(0);
    start_color();
    timeout(50);
    use_default_colors(); 
    init_pair(1, COLOR_RED, -1);
    init_pair(2, COLOR_YELLOW, -1);
    init_pair(3, COLOR_GREEN, -1);

    _boxes.push_back(new TimeBox());
    _boxes.push_back(new HostnameBox());
    _boxes.push_back(new OsBox());
    _boxes.push_back(new UptimeBox());
    _boxes.push_back(new BatteryBox());
    _boxes.push_back(new TemperatureBox());
    _boxes.push_back(new DiskBox());
    _boxes.push_back(new RamBox());
    _boxes.push_back(new CpuBox());
    _boxes.push_back(new NetworkBox());
  
    _pad = newpad(2000, 500); 
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void NcursesDisplay::stop()
{
    for (IBox *b : _boxes) {
        delete b;
    }
    _boxes.clear();
    if (!isendwin()) {
        endwin();
    }
    if (_pad) {
        delwin(_pad);
        _pad = nullptr;
    }
}

void NcursesDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    _lastModules = &modules;
    werase(_pad);
    wattrset(_pad, A_NORMAL);
    
    int currentY = 0;
    int width = COLS;

    for (auto* module : modules) {
        if (!module) continue;
        
        std::string name = module->getName();

        if (_hiddenModules[name] == true)
            continue;

        for (auto &box : _boxes) {
            if (box->getModuleNeeded() == name) {
                box->setYPos(currentY, width);
                box->display(module);

                copywin(box->getWin(), _pad, 0, 0, currentY, 0, currentY + box->getHeight() - 1, width - 1, FALSE);
                currentY += box->getHeight();
                break;
            }
        }
    }
    
    _totalContentHeight = currentY;

    // Rendu final
    pnoutrefresh(_pad, _scrollOffset, 0, 0, 0, LINES - 1, COLS - 1);
    doupdate();
}

int NcursesDisplay::handle_inputs() {
    int ch = getch();
    int idx = -1;

    if (ch >= '1' && ch <= '9')
        idx = ch - '1';
    else if (ch == '0')
        idx = 9;

    if (_lastModules && idx != -1 && idx < (int)_lastModules->size()) {
        std::string name = (*_lastModules)[idx]->getName();
        _hiddenModules[name] = !_hiddenModules[name];
    }

    if (ch == KEY_DOWN) {
        _scrollOffset += 2;
    }
    if (ch == KEY_UP) {
        _scrollOffset -= 2;
    }
    if (_scrollOffset < 0) {
        _scrollOffset = 0;
    }
    int maxScroll = _totalContentHeight - LINES;
    if (maxScroll < 0) {
        maxScroll = 0;
    }
    if (_scrollOffset > maxScroll) {
        _scrollOffset = maxScroll;
    }

    if (ch == 'q') return 1;
    if (ch == 's') return 2;
    return 0;
}