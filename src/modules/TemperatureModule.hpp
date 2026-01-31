/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** TemperatureModule.hpp
*/

#ifndef TEMPERATUREMODULE_HPP_
#define TEMPERATUREMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <string>
#include <map>
#include <vector>

class TemperatureModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;
        std::string _path;
        bool _hasSensor;

        void findSensor()
        {
            _hasSensor = false;
            for (int i = 0; i < 5; ++i) {
                std::string p = "/sys/class/thermal/thermal_zone" + std::to_string(i) + "/temp";
                std::ifstream file(p);
                if (file.is_open()) {
                    _path = p;
                    _hasSensor = true;
                    return;
                }
            }
        }

    public:
        TemperatureModule() : _name("Temperature")
        {
            findSensor();
            update();
        }
        virtual ~TemperatureModule() = default;

        void update() override
        {
            if (!_hasSensor) {
                _data["Temp"] = "No Sensor (VM?)";
                return;
            }
            std::ifstream file(_path);
            long milliTemp = 0;
            if (file.is_open() && (file >> milliTemp)) {
                float temp = milliTemp / 1000.0f;
                int tInt = (int)temp;
                int tDec = (int)((temp - tInt) * 10);
                if (tDec < 0) tDec = -tDec;
                _data["Temp"] = std::to_string(tInt) + "." + std::to_string(tDec) + " C";
            } else {
                _data["Temp"] = "Unknown";
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !TEMPERATUREMODULE_HPP_ */