/*
** EPITECH PROJECT, 2026
** CpuWindow
** File description:
** CpuWindow def
*/

#ifndef CPUWINDOW
    #define CPUWINDOW

    #include <iostream>
    #include <string>
    #include <ncurses.h>
    #include "modules/CpuModule.hpp"

class CpuWindow : public CpuModule{
    private:
        /* Attributs */
        WINDOW *_CpuWin;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        CpuWindow();
        ~CpuWindow() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */

        void displayCpuMod();
};

#endif