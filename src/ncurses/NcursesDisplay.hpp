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
        NcursesDisplay() : _window(nullptr), _ramBox(nullptr), _lastModules(nullptr), _iterator(0) {};
        ~NcursesDisplay() override;

        void init() override;
        void stop() override;
        void display(const std::vector<Krell::IModule *> &modules) override;
        int handle_inputs() override;

    protected:
    private:
        WINDOW *_pad = nullptr;
        int _scrollOffset = 0;
        int _totalContentHeight = 0;
        WINDOW *_window;
        RamBox *_ramBox;
        std::vector<IBox*> _boxes;
        std::map<std::string, bool> _hiddenModules;
        const std::vector<Krell::IModule *> *_lastModules;
        int _iterator;
};

#endif /* !NCURSESDISPLAY_HPP_ */