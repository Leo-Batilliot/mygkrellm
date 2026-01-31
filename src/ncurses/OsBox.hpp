/*
** EPITECH PROJECT, 2026
** OsBox
** File description:
** OsBox def
*/

#ifndef OSBOX
    #define OSBOX

    #include <iostream>
    #include <string>
    #include "ncurses/IBox.hpp"

class OsBox : public IBox {
    private:
        /* Attributs */
        WINDOW *_box;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        OsBox(int x, int y);
        ~OsBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
};

#endif