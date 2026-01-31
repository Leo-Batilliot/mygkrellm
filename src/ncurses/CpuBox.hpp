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
    #include "ncurses/IBox.hpp"
    #include "modules/CpuModule.hpp"

class CpuBox : public IBox {
    private:
        /* Attributs */
        WINDOW *_box;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        CpuBox(int x, int y);
        ~CpuBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
};

#endif