/*
** EPITECH PROJECT, 2026
** BatteryBox
** File description:
** BatteryBox def
*/

#ifndef BATTERYBOX
    #define BATTERYBOX

    #include <iostream>
    #include <string>
    #include "ncurses/IBox.hpp"

class BatteryBox : public IBox {
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
        BatteryBox(int x, int y);
        BatteryBox();
        ~BatteryBox();

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