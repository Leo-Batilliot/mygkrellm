/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** BatteryModule.hpp
*/

#ifndef BATTERYMODULE_HPP_
#define BATTERYMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <string>
#include <map>

class BatteryModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

        std::string _path;
        enum Type {
            BATTERY, 
            AC_ADAPTER,
            NONE
        } _type;

        void detectSource()
        {      
            if (std::ifstream("/sys/class/power_supply/BAT0/capacity").is_open()) {
                _path = "/sys/class/power_supply/BAT0";
                _type = BATTERY;
                return;
            }
            if (std::ifstream("/sys/class/power_supply/BAT1/capacity").is_open()) {
                _path = "/sys/class/power_supply/BAT1";
                _type = BATTERY;
                return;
            }
            if (std::ifstream("/sys/class/power_supply/ACAD/online").is_open()) {
                _path = "/sys/class/power_supply/ACAD/online";
                _type = AC_ADAPTER;
                return;
            }

            _type = NONE;
        }

    public:
        BatteryModule() : _name("Battery")
        {
            detectSource();
            update();
        }
        virtual ~BatteryModule() = default;

        void update() override
        {
            if (_type == NONE) {
                _data["Status"] = "No Battery";
                _data["Level"] = "---";
                return;
            }

            if (_type == BATTERY) {
                std::ifstream capacityFile(_path + "/capacity");
                std::string buffer;
                if (capacityFile.is_open() && capacityFile >> buffer) {
                    _data["Level"] = buffer + "%";
                } else {
                    _data["Level"] = "Unknown";
                }
                std::ifstream statusFile(_path + "/status");
                if (statusFile.is_open() && statusFile >> buffer) {
                    _data["Status"] = buffer;
                } else {
                    _data["Status"] = "Unknown";
                }
            } 
            else if (_type == AC_ADAPTER) {
                std::ifstream onlineFile(_path);
                std::string buffer;
                if (onlineFile.is_open() && onlineFile >> buffer) {
                    _data["Status"] = "AC Power";
                    if (buffer == "1") {
                        _data["Level"] = "Online";
                    } else {
                        _data["Level"] = "Offline";
                    }
                } else {
                    _data["Status"] = "AC Power";
                    _data["Level"] = "Unknown";
                }
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !BATTERYMODULE_HPP_ */