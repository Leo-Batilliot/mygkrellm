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
        int _height;

        /* Methods */

    protected:
        /* Attributs */

        /* Methods */

    public:
        /* Const / Destr */
        RamBox(int x, int y);
        RamBox();
        ~RamBox() override;

        /* Getters */

        /* Setters */

        // std::string getModuleNeeded() const override; // Commented out as it already exists

        /* Methods */
        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
        int getHeight() const override;
        void setYPos(int y) override;
        int getYPos() const override;
};

#endif