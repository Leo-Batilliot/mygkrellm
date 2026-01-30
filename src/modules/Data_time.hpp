/*
** EPITECH PROJECT, 2026
** tek2
** File description:
** Data_time
*/

#ifndef DATA_TIME_HPP_
#define DATA_TIME_HPP_

#include "interfaces/IModule.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include "ncurses.h"

class Data_time : public Krell::IModule {
    public:
        Data_time() : _timeWindow(nullptr) ,_name("Time") { update(); }
        virtual ~Data_time() {
            if(_timeWindow)
                delwin(_timeWindow);
            _timeWindow = nullptr;
        };

        void update() override {
            time_t now = time(nullptr);
            struct tm *localTime = localtime(&now);

            std::ostringstream hours;
            hours << std::setfill('0') << std::setw(2) << localTime->tm_hour << ":"
                << std::setfill('0') << std::setw(2) << localTime->tm_min << ":"
                << std::setfill('0') << std::setw(2) << localTime->tm_sec;
            std::ostringstream date;
            date << std::setfill('0') << std::setw(2) << localTime->tm_mday << "/"
                << std::setfill('0') << std::setw(2) << (localTime->tm_mon + 1) << "/"
                << (localTime->tm_year + 1900);
                
            _data["Hours"] = hours.str();
            _data["Date"] = date.str();
        }
        std::string getName() const override { return _name; }
        const std::map<std::string, std::string> &getData() const override { return _data; }
        
        void display_time() {
            if (!_timeWindow)
                _timeWindow = newwin(5, 20, 2, 2);
            werase(_timeWindow);
            box(_timeWindow, 0, 0);
            mvwprintw(_timeWindow, 1, 1, "Time: %s", _data.at("Hours").c_str());
            mvwprintw(_timeWindow, 2, 1, "Date: %s", _data.at("Date").c_str());
            wrefresh(_timeWindow);
        }
    protected:
    private:
        WINDOW *_timeWindow;
        std::string _name;
        std::map<std::string, std::string> _data;

};

#endif /* !DATA_TIME_HPP_ */
