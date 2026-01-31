#include <ncurses.h>
#include "ncurses/NcursesDisplay.hpp"
#include "modules/DateTime.hpp"
#include "modules/Hostname.hpp"
#include "iostream"

NcursesDisplay::NcursesDisplay() : _window(nullptr), _timeWindow(nullptr), _hostnameWindow(nullptr)
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
    _timeWindow = newwin(5, 20, 2, 2);
    _hostnameWindow = newwin(5, 30, 7, 2);
    nodelay(_window, TRUE);
    keypad(_window, TRUE);
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
        if (module->getName() == "Date & Time") {
            std::map<std::string, std::string> data = module->getData();
            werase(_timeWindow);
            box(_timeWindow, 0, 0);
            mvwprintw(_timeWindow, 1, 1, "Time: %s", data.at("Date").c_str());
            mvwprintw(_timeWindow, 2, 1, "Date: %s", data.at("Time").c_str());
            wrefresh(_timeWindow);
        }
        if (module->getName() == "Hostname") {
            std::map<std::string, std::string> data = module->getData();
            werase(_hostnameWindow);
            box(_hostnameWindow, 0, 0);
            mvwprintw(_hostnameWindow, 1, 1, "Hostname: %s", data.at("Hostname").c_str());
            mvwprintw(_hostnameWindow, 2, 1, "Username: %s", data.at("Username").c_str());
            wrefresh(_hostnameWindow);
        }
    }
    usleep(1000);
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