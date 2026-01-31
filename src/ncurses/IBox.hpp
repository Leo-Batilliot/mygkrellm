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
        virtual void setYPos(int y, int width) = 0;
        virtual int getYPos() const = 0;

        /* Operator */

        /* Methods */
        virtual void display(Krell::IModule *module) = 0;
        virtual WINDOW *getWin() const = 0;
        virtual std::string getModuleNeeded() const = 0;
        virtual int getHeight() const = 0;
};

std::string safeGet(const std::map<std::string, std::string>& data, const std::string& key);

#endif