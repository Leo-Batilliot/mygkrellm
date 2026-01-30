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
        OSModule() : _name("OS & Kernel") {update();}
        virtual ~OSModule() = default;

        void update() override
        {
            struct utsname buffer;

            if (uname(&buffer) != -1) {
                _data["Operating system"] = std::string(buffer.sysname);
                _data["Kernel"] = std::string(buffer.release);
            } else {
                _data["Operating system"] = "Unknown";
                _data["Kernel"] = "Unknown";
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !OSMODULE_HPP_ */