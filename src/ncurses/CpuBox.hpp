/*
** EPITECH PROJECT, 2026
** CpuBox
** File description:
** CpuBox def
*/

#ifndef CPUBOX
    #define CPUBOX

    #include <iostream>
    #include <string>
    #include <ncurses.h>
    #include "modules/CpuModule.hpp"

class CpuBox : public CpuModule{
    private:
        /* Attributs */
        WINDOW *_CpuWin;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        CpuBox();
        ~CpuBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */

        void displayCpuMod();
};

#endif