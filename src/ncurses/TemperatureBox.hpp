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
        int _height;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        TemperatureBox(int x, int y);
        TemperatureBox();
        ~TemperatureBox() override;

        /* Getters */

        /* Setters */
        void setYPos(int y, int width) override;
        int getYPos() const override;

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
        int getHeight() const override;
};

#endif