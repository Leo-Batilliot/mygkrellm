/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** NcursesDisplay
*/

#ifndef NCURSESDISPLAY_HPP_
#define NCURSESDISPLAY_HPP_
#include "ncurses.h"
#include "interfaces/IDisplay.hpp"

class NcursesDisplay : public Krell::IDisplay {
    public:
        NcursesDisplay() {
            init_pair(1, COLOR_RED, COLOR_BLACK);
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            init_pair(3, COLOR_GREEN, COLOR_BLACK);
        };
        ~NcursesDisplay() override;

        void init() override;
        void stop() override;
        void display(const std::vector<Krell::IModule *> &modules) override;
        int handle_inputs() override;

    protected:
    private:
        WINDOW *_window;
        WINDOW *_timeWindow;
        WINDOW *_hostnameWindow;
        std::vector<IBox*> _boxes;
};

#endif /* !NCURSESDISPLAY_HPP_ */