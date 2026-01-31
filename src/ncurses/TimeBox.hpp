/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** TimeBox
*/

#ifndef TIMEBOX_HPP_
#define TIMEBOX_HPP_

#include "ncurses/IBox.hpp"
#include "modules/DateTime.hpp"

class TimeBox : public IBox {
    public:
        TimeBox(int x, int y);
        ~TimeBox() override;

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;

    protected:
    private:
        WINDOW *_box;
};

#endif /* !TIMEBOX_HPP_ */
