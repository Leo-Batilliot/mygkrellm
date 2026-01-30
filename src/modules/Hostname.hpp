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

class Hostname : public Krell::IModule{
    private :
        std::string _name;
        std::map<std::string, std::string> _data;
    public:
        Hostname() : _name("Hostname") {update();}
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

    protected:
};

#endif /* !HOSTNAME_HPP_ */
