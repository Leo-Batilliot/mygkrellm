/*
** EPITECH PROJECT, 2026
** IBox
** File description:
** IBox def
*/

#ifndef IBOX
    #define IBOX

    #include <iostream>
    #include <string>
    #include <ncurses.h>
    #include "interfaces/IModule.hpp"

class IBox {
    private:
        /* Attributs */

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        IBox() = default;
        virtual ~IBox() = default;

        /* Getters */

        /* Setters */

        /* Operator */

        /* Methods */
        virtual void display(Krell::IModule *module) = 0;
        virtual WINDOW *getWin() const = 0;
};

std::ostream& operator<<(std::ostream& os, const IBox& obj);

#endif