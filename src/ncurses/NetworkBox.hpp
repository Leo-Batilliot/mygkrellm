/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** HostnameBox
*/

#ifndef NETWORKBOX_HPP_
#define NETWORKBOX_HPP_

#include "ncurses/IBox.hpp"
#include "modules/NetworkModule.hpp"
#include <deque>
#include <ctime>
#include <vector>
#include <string>

class NetworkBox : public IBox {
    public:
        NetworkBox(int x, int y);
        ~NetworkBox() override;

        void display(Krell::IModule *module) override;
        WINDOW *getWin() const override;
        std::string getModuleNeeded() const override;
        int getHeight() const override;
        void setYPos(int y) override;
        int getYPos() const override;

    protected:
    private:
        WINDOW *_box;
        std::deque<int> _downloadHisto;
        std::deque<int> _updateHisto;
        time_t _lastUpdate;
        float _highestDL = 0;
        float _highestUP = 0;
        int _height;
};

#endif /* !NETWORKBOX_HPP_ */
