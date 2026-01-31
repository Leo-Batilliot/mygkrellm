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
        ~HostnameBox() override;

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;

    protected:
    private:
        WINDOW *_box;
};

#endif /* !HOSTNAMEBOX_HPP_ */
