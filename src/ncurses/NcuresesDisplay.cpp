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

    _boxes.push_back(new TimeBox(2, 2));
    _boxes.push_back(new HostnameBox(29, 2));
    _boxes.push_back(new NetworkBox(77, 2));
    _boxes.push_back(new OsBox(2, 7));
    _boxes.push_back(new CpuBox(77, 27));
    _boxes.push_back(new RamBox(2, 12));
    _boxes.push_back(new BatteryBox(2, 19));
    _boxes.push_back(new UptimeBox(2, 26));
    _boxes.push_back(new TemperatureBox(2, 31));
    _boxes.push_back(new DiskBox(120, 2));

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

    box(stdscr, 0, 0);
    mvprintw(1, 2, "MyGKrellm (press q to quit, s to switch)");
    
    wnoutrefresh(stdscr);

    for (auto module : modules) {
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