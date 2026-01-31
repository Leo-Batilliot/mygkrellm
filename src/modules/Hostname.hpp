/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** Hostname
*/

#ifndef HOSTNAME_HPP_
#define HOSTNAME_HPP_
#include "interfaces/IModule.hpp"
#include <unistd.h>
#include <limits.h>
#include "ncurses.h"

class Hostname : public Krell::IModule {
    private :
        WINDOW *_timeWindow;
        std::string _name;
        std::map<std::string, std::string> _data;
    public:
        Hostname() : _timeWindow(nullptr), _name("Hostname") {update();}
        virtual ~Hostname() = default;

        void update() override
        {
            char hostname[HOST_NAME_MAX];
            char username[LOGIN_NAME_MAX];

            gethostname(hostname, HOST_NAME_MAX);
            getlogin_r(username, LOGIN_NAME_MAX);

            _data["Hostname"] = std::string(hostname);
            _data["Username"] = std::string(username);
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
        
        void display_hostname() {
            if (!_timeWindow) {
                _timeWindow = newwin(5, 30, 7, 2);
            }
            werase(_timeWindow);
            box(_timeWindow, 0, 0);
            mvwprintw(_timeWindow, 1, 1, "Hostname: %s", _data.at("Hostname").c_str());
            mvwprintw(_timeWindow, 2, 1, "Username: %s", _data.at("Username").c_str());
            wrefresh(_timeWindow);
        }
    protected:
};

#endif /* !HOSTNAME_HPP_ */
