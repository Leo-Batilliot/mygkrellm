/*
** EPITECH PROJECT, 2026
** TemperatureBox
** File description:
** TemperatureBox def
*/

#ifndef TEMPERATUREBOX
    #define TEMPERATUREBOX

    #include <iostream>
    #include <string>
    #include <vector>
    #include <ncurses.h>
    #include "ncurses/IBox.hpp"

class TemperatureBox : public IBox {
    private:
        /* Attributs */
        WINDOW *_box;
        std::vector<float> _prevData;
        int _countPush;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        TemperatureBox(int x, int y);
        ~TemperatureBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
};

#endif