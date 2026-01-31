/*
** EPITECH PROJECT, 2026
** RamWindow
** File description:
** RamWindow def
*/

#ifndef RAMMWINDOW
    #define RAMWINDOW

    #include <iostream>
    #include <string>
    #include <ncurses.h>
    #include "interfaces/IModule.hpp"
    #include "modules/RamModule.hpp"

class RamWindow : public RamModule{
    private:
        /* Attributs */
        WINDOW *_RamWin;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        RamWindow();
        ~RamWindow() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */

        void displayRamMod();
};

#endif