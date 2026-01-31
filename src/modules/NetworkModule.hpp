/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** NetworkModule.hpp
*/

#ifndef NETWORKMODULE_HPP_
#define NETWORKMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

class NetworkModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

        unsigned long long _prevRxBytes = 0;
        unsigned long long _prevTxBytes = 0;
        bool _firstUpdate = true;

        std::string formatSpeed(unsigned long long bytes)
        {
            float speedKB = bytes / 1024.0f;
            float speedMB = speedKB / 1024.0f;

            if (speedMB >= 1.0f) {
                int integer = (int)speedMB;
                int decimal = (int)((speedMB - integer) * 10);
                return std::to_string(integer) + "." + std::to_string(decimal) + " MB/s";
            } else {
                int size = (int)speedKB;
                return std::to_string(size) + " KB/s";
            }
        }

    public:
        NetworkModule() : _name("Network")
        {
            _data["Download"] = "Unknown";
            _data["Upload"] = "Unknown";
            update();
        }
        virtual ~NetworkModule() = default;

        void update() override
        {
            std::ifstream file("/proc/net/dev");
            std::string line;
            
            unsigned long long currentRxTotal = 0;
            unsigned long long currentTxTotal = 0;

            if (!file.is_open()) return;

            std::getline(file, line);
            std::getline(file, line);

            while (std::getline(file, line)) {
                std::replace(line.begin(), line.end(), ':', ' ');
                std::stringstream ss(line);
                std::string iface;
                unsigned long long received, transmitted, trash;
                
                ss >> iface >> received;
                
                if (iface == "lo") continue;
                for (int i = 0; i < 7; ++i) ss >> trash;
                
                ss >> transmitted;

                currentRxTotal += received;
                currentTxTotal += transmitted;
            }

            unsigned long long diffRx = 0;
            unsigned long long diffTx = 0;

            if (!_firstUpdate) {
                if (currentRxTotal >= _prevRxBytes) diffRx = currentRxTotal - _prevRxBytes;
                if (currentTxTotal >= _prevTxBytes) diffTx = currentTxTotal - _prevTxBytes;
            } else {
                _firstUpdate = false;
            }

            _prevRxBytes = currentRxTotal;
            _prevTxBytes = currentTxTotal;

            _data["Download"] = formatSpeed(diffRx);
            _data["Upload"]   = formatSpeed(diffTx);
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !NETWORKMODULE_HPP_ */