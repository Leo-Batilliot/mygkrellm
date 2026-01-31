/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** UptimeModule.hpp
*/

#ifndef UPTIMEMODULE_HPP_
#define UPTIMEMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <string>
#include <map>

class UptimeModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

        std::string formatTime(long totalSeconds)
        {
            int days = totalSeconds / 86400;
            int hours = (totalSeconds % 86400) / 3600;
            int minutes = (totalSeconds % 3600) / 60;
            int seconds = totalSeconds % 60;

            std::string res = "";
            if (days > 0) res += std::to_string(days) + "d ";
            if (hours > 0) res += std::to_string(hours) + "h ";
            if (minutes > 0) res += std::to_string(minutes) + "m ";
            res += std::to_string(seconds) + "s";
            return res;
        }

    public:
        UptimeModule() : _name("Uptime")
        {
            _data["Uptime"] = "Unknown";
            update();
        }
        virtual ~UptimeModule() = default;

        void update() override
        {
            std::ifstream file("/proc/uptime");
            double uptimeSeconds = 0;
            
            if (file.is_open()) {
                file >> uptimeSeconds;
                _data["Uptime"] = formatTime((long)uptimeSeconds);
            } else {
                _data["Uptime"] = "Unknown";
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !UPTIMEMODULE_HPP_ */