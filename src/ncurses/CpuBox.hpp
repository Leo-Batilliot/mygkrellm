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
        int _height;

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
        void setYPos(int y) override;
        int getYPos() const override;

        /* Operator */

        /* Methods */

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
        int getHeight() const override;
};

#endif