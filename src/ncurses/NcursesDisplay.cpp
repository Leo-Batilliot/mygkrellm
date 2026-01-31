#include <ncurses.h>
#include "ncurses/NcursesDisplay.hpp"
#include "modules/Data_time.hpp"
#include "modules/Hostname.hpp"
#include "iostream"

NcursesDisplay::NcursesDisplay() : _window(nullptr)
{
}

NcursesDisplay::~NcursesDisplay()
{
}

void NcursesDisplay::init()
{
    initscr();
    noecho();
    raw();
    curs_set(0);

    int h;
    int w;
    getmaxyx(stdscr, h, w);
    _window = newwin(h, w, 0, 0);
    nodelay(_window, TRUE);  // Activer nodelay sur _window aussi
    keypad(_window, TRUE);   // Activer keypad sur _window aussi
}

void NcursesDisplay::stop()
{
    if (_window) {
        delwin(_window);
        _window = nullptr;
    }
    endwin();
}

void NcursesDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    int h;
    int w;
    getmaxyx(stdscr, h, w);

    wresize(_window, h, w);
    werase(_window);

    box(_window, 0, 0);
    mvwprintw(_window, 1, 2, "Ncurses Display (press q to quit) - %dx%d", w, h);

    wrefresh(_window);

    for (auto module : modules) {
        if (module->getName() == "Time") {
            Data_time* timeModule = dynamic_cast<Data_time*>(module);
            if (timeModule) {
                timeModule->display_time();
            }
        }
        if (module->getName() == "Hostname") {
            Hostname* Hostnamemodule = dynamic_cast<Hostname*>(module);
            if (Hostnamemodule) {
                Hostnamemodule->display_hostname();
            }
        }
    }
}

bool NcursesDisplay::handle_inputs()
{
    int ch = wgetch(_window);

    if (ch == 'q')
        return false;

    if (ch == KEY_RESIZE) {
        return true;
    }

    return true;
}
