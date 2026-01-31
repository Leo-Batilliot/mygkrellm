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
#include "RamBox.hpp"

class NcursesDisplay : public Krell::IDisplay {
    public:
        NcursesDisplay() :  _window(nullptr), _timeWindow(nullptr), _hostnameWindow(nullptr), _ramBox(nullptr) {};
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
        RamBox *_ramBox;
};

#endif /* !NCURSESDISPLAY_HPP_ */