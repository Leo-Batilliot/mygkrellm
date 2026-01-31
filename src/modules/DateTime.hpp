/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DateTime.hpp
*/

#ifndef DATETIME_HPP_
#define DATETIME_HPP_

#include "interfaces/IModule.hpp"
#include <ctime>
#include <string>
#include <map>

class DateTime : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

    public:
        DateTime() : _name("Date & Time")
        {
            _data["Date"] = "Unknown";
            _data["Time"] = "unknown";
            update();
        }
        virtual ~DateTime() = default;

        void update() override
        {
            std::time_t now = std::time(nullptr);
            std::tm *local_time = std::localtime(&now);
            char buffer[100];

            std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", local_time);
            _data["Date"] = std::string(buffer);
            
            std::strftime(buffer, sizeof(buffer), "%T", local_time);
            _data["Time"] = std::string(buffer);
        }
        
        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !DATETIME_HPP_ */