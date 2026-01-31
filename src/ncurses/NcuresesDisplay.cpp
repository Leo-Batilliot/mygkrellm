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
#include "ncurses/IBox.hpp"

NcursesDisplay::~NcursesDisplay()
{
}

void NcursesDisplay::init()
{
    initscr();
    noecho();
    raw();
    curs_set(0);
    start_color();
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
    _boxes.push_back(new RamBox());
    _boxes.push_back(new CpuBox());
    _boxes.push_back(new NetworkBox());
    
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void NcursesDisplay::stop()
{
    if (_window) {
        delwin(_window);
        _window = nullptr;
    }
    for (IBox *b : _boxes) {
        if (b)
            delete b;
    }
    _boxes.clear();
    endwin();
}

void NcursesDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    erase(); 

    //box(stdscr, 0, 0);
    mvprintw(1, 2, "MyGKrellm (press q to quit, s to switch)");
    
    wnoutrefresh(stdscr);

    for (auto module : modules) {
        for (int i = _iterator; i < (int)_boxes.size(); i++) {
            if (_boxes[i]->getModuleNeeded() == module->getName()) {
                _boxes[i]->display(module);
                if (i == _iterator)
                    _boxes[i]->setYPos(2);
                else
                    _boxes[i]->setYPos(_boxes[i - 1]->getYPos() + _boxes[i - 1]->getHeight() + 1);
            }
        }
    }
    doupdate();
}

int NcursesDisplay::handle_inputs()
{
    int ch = getch();

    if (ch == KEY_DOWN)
        _iterator++;
    if (ch == KEY_UP)
        _iterator--;
    if (ch == ' ')
        _iterator = 0;
    if (_iterator >= (int)_boxes.size()) {
        _iterator = 0;
    }
    if (_iterator < 0) {
        _iterator = _boxes.size() - 1;
    }

    if (ch == 'q') return 1;
    if (ch == 's') return 2;
    return 0;
}