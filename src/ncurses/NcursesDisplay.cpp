/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** NcursesDisplay implementation
*/

#include "ncurses/NcursesDisplay.hpp"

NcursesDisplay::NcursesDisplay()
{
}

NcursesDisplay::~NcursesDisplay()
{
}

void NcursesDisplay::init()
{
    initscr();
}

void NcursesDisplay::stop()
{
    endwin();
}

void NcursesDisplay::display(const std::vector<Krell::IModule *> &modules)
{
    printw("Ncurses Display");
    int c = getch();
    (void)modules;
}

bool NcursesDisplay::handle_inputs()
{
    return true;
}
