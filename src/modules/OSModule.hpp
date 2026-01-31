/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** OSModule.hpp
*/

#ifndef OSMODULE_HPP_
#define OSMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <sys/utsname.h>
#include <iostream>

class OSModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

    public:
        OSModule() : _name("OS & Kernel")
        {
            _data["Kernel"] = "Unknown";
            _data["Operating system"] = "Unknown";
            update();
        }
        virtual ~OSModule() = default;

        void update() override
        {
            struct utsname buffer;
            if (uname(&buffer) != -1) {
                _data["Kernel"] = std::string(buffer.release);
            } else {
                _data["Kernel"] = "Unknown";
            }

            std::ifstream file("/etc/os-release");
            std::string line;
            std::string osName = "Linux (Unknown)";
            if (file.is_open()) {
                while (std::getline(file, line)) {
                    if (line.find("NAME=") == 0) {
                        osName = line.substr(5);
                        if (osName.size() > 1 && osName.front() == '"' && osName.back() == '"') {
                            osName = osName.substr(1, osName.size() - 2);
                        }
                        break;
                    }
                }
            }
            _data["Operating system"] = osName;
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !OSMODULE_HPP_ */