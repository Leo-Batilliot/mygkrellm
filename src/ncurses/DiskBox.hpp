/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#ifndef DISKBOX_HPP_
#define DISKBOX_HPP_

#include "ncurses/IBox.hpp"
#include "modules/DateTime.hpp"

class DiskBox : public IBox {
    public:
        DiskBox(int x, int y);
        ~DiskBox() override;

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;

    protected:
    private:
        WINDOW *_box;
};

#endif /* !DISKBOX_HPP_ */
