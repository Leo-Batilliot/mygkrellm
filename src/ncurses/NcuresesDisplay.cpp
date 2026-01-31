#include <ncurses.h>
#include "ncurses/NcursesDisplay.hpp"
#include "modules/DateTime.hpp"
#include "modules/Hostname.hpp"
#include "iostream"
#include "ncurses/RamBox.hpp"
#include "ncurses/CpuBox.hpp"
#include "ncurses/OsBox.hpp"
#include "ncurses/BatteryBox.hpp"
#include "ncurses/UptimeBox.hpp"
#include "ncurses/TemperatureBox.hpp"

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

    _timeWindow = newwin(5, 72, 2, 2);
    _hostnameWindow = newwin(5, 72, 7, 2);

    _boxes.push_back(new OsBox(2, 12));
    _boxes.push_back(new CpuBox(77, 14));
    _boxes.push_back(new RamBox(2, 17));
    _boxes.push_back(new BatteryBox(2, 24));
    _boxes.push_back(new UptimeBox(2, 31));
    _boxes.push_back(new TemperatureBox(77, 2));

    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

void NcursesDisplay::stop()
{
    if (_window) {
        delwin(_window);
        _window = nullptr;
    }
    if (_timeWindow) {
        delwin(_timeWindow);
        _timeWindow = nullptr;
    }
    if (_hostnameWindow) {
        delwin(_hostnameWindow);
        _hostnameWindow = nullptr;
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

    int h, w;
    getmaxyx(stdscr, h, w);
    box(stdscr, 0, 0);
    mvprintw(1, 2, "Ncurses Display (press q to quit, s to switch) - %dx%d", w, h);
    
    wnoutrefresh(stdscr);

    for (auto module : modules) {
        if (module->getName() == "Hostname") {
            auto data = module->getData();
            werase(_hostnameWindow);
            box(_hostnameWindow, 0, 0);
            mvwprintw(_hostnameWindow, 1, 2, "Hostname: %s", data.at("Hostname").c_str());
            mvwprintw(_hostnameWindow, 2, 2, "Username: %s", data.at("Username").c_str());
            wnoutrefresh(_hostnameWindow);
        }
        if (module->getName() == "Date & Time") {
            auto data = module->getData();
            werase(_timeWindow);
            box(_timeWindow, 0, 0);
            mvwprintw(_timeWindow, 1, 2, "Time: %s", data.at("Time").c_str());
            mvwprintw(_timeWindow, 2, 2, "Date: %s", data.at("Date").c_str());
            wnoutrefresh(_timeWindow);
        }
        for (IBox *box : _boxes) {
            if (box && box->getModuleNeeded() == module->getName()) {
                box->display(module);
            }
        }
    }
    doupdate();
}

int NcursesDisplay::handle_inputs()
{
    int ch = getch();

    if (ch == 'q') return 1;
    if (ch == 's') return 2;
    return 0;
}