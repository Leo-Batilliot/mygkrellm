/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** RamModule.hpp
*/

#ifndef RAMMODULE_HPP_
#define RAMMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class RamModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

        std::string formatSize(unsigned long long sizeKB) {
            float sizeGB = sizeKB / (1024.0f * 1024.0f);
            float sizeMB = sizeKB / 1024.0f;
            
            if (sizeGB >= 1.0f) {
                int integer = (int)sizeGB;
                int decimal = (int)((sizeGB - integer) * 10);
                return std::to_string(integer) + "." + std::to_string(decimal) + " GB";
            } else {
                int size = (int)sizeMB;
                return std::to_string(size) + " MB";
            }
        }

    public:
        RamModule() : _name("RAM") {update();}
        virtual ~RamModule() = default;

        void update() override
        {
            std::ifstream file("/proc/meminfo");
            std::string line;
            std::string key;
            unsigned long long value;
            std::string unit;

            unsigned long long total = 0;
            unsigned long long available = 0;

            if (!file.is_open()) return;

            while (std::getline(file, line)) {
                std::stringstream ss(line);
                ss >> key >> value >> unit;

                if (key == "MemTotal:") {
                    total = value;
                } else if (key == "MemAvailable:") {
                    available = value;
                }
                if (total > 0 && available > 0) break;
            }

            unsigned long long used = total - available;
 
            int percent = 0;
            if (total > 0) {
                percent = (used * 100) / total;
            }

            _data["Total"] = formatSize(total);
            _data["Used"] = formatSize(used);
            _data["Available"] = formatSize(available);
            _data["Percent"] = std::to_string(percent) + "%";
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !RAMMODULE_HPP_ */