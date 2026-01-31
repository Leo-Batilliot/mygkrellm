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
    #include <ncurses.h>
    #include "interfaces/IModule.hpp"
    #include "modules/RamModule.hpp"

class RamBox : public RamModule{
    private:
        /* Attributs */
        WINDOW *_RamWin;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        RamBox();
        ~RamBox() override;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */

        void displayRamMod();
};

#endif