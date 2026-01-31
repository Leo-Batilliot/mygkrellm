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

    // create boxes and register them
    _boxes.push_back(new TimeBox(2, 2));
    _boxes.push_back(new HostnameBox(2, 7));
    _boxes.push_back(new CpuBox(2, 12));
    _boxes.push_back(new RamBox(2, 29));
    _boxes.push_back(new NetworkBox(80, 12));

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

    int h, w;
    getmaxyx(stdscr, h, w);
    box(stdscr, 0, 0);
    mvprintw(1, 2, "Ncurses Display (press q to quit, s to switch) - %dx%d", w, h);
    
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