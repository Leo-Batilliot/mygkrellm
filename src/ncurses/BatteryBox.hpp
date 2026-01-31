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

        /* Methods */

    protected:
        /* Attributs */
        WINDOW *_box;
        /* Methods */

    public:
        /* Const / Destr */
        BatteryBox(int x, int y);
        ~BatteryBox();

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
};

#endif