/*
** EPITECH PROJECT, 2026
** RamBox
** File description:
** RamBox def
*/

#ifndef RAMBOX
    #define RAMBOX

    #include <iostream>
    #include <string>
    #include "modules/RamModule.hpp"
    #include "ncurses/IBox.hpp"

class RamBox : public IBox {
    private:
        /* Attributs */
        WINDOW *_box;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        RamBox(int x, int y);
        ~RamBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
};

#endif