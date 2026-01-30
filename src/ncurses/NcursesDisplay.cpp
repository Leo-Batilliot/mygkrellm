#include <ncurses.h>
#include "ncurses/NcursesDisplay.hpp"

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
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int h;
    int w;
    getmaxyx(stdscr, h, w);
    _window = newwin(h, w, 0, 0);
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

    (void)modules;

    wrefresh(_window);
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
