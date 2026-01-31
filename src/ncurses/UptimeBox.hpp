/*
** EPITECH PROJECT, 2026
** UptimeBox
** File description:
** UptimeBox def
*/

#ifndef UPTIMEBOX
    #define UPTIMEBOX

    #include <iostream>
    #include <string>
    #include "ncurses/IBox.hpp"

class UptimeBox : public IBox {
    private:
        /* Attributs */

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        UptimeBox(int x, int y);
        ~UptimeBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
};

#endif