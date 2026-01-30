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
        NcursesDisplay();
        ~NcursesDisplay() override;

        void init() override;
        void stop() override;
        void display(const std::vector<Krell::IModule *> &modules) override;
        bool handle_inputs() override;

    protected:
    private:
};

#endif /* !NCURSESDISPLAY_HPP_ */
