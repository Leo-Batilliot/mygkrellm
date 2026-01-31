/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** HostnameBox
*/

#ifndef HOSTNAMEBOX_HPP_
#define HOSTNAMEBOX_HPP_

#include "ncurses/IBox.hpp"
#include "modules/Hostname.hpp"

class HostnameBox : public IBox {
    public:
        HostnameBox(int x, int y);
        HostnameBox();
        ~HostnameBox() override;

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
        int getHeight() const override;
        void setYPos(int y) override;
        int getYPos() const override;

    protected:
    private:
        WINDOW *_box;
        int _height;
};

#endif /* !HOSTNAMEBOX_HPP_ */
