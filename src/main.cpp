/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** main
*/
#include "interfaces/IDisplay.hpp"
#include "interfaces/IModule.hpp"

#include "sfml/SfmlDisplay.hpp"
#include "ncurses/NcursesDisplay.hpp"
#include "modules/Hostname.hpp"
#include "modules/OSModule.hpp"
#include "modules/DateTime.hpp"
#include "modules/CpuModule.hpp"
#include "modules/RamModule.hpp"
#include "modules/NetworkModule.hpp"
#include "modules/BatteryModule.hpp"
#include "modules/UptimeModule.hpp"
#include "modules/TemperatureModule.hpp"
#include "modules/DiskModule.hpp"

int main(int ac, char **av)
{
    Krell::IDisplay *display = nullptr;
    int display_type = 0;

    if (ac > 1 && std::string(av[1]) == "-sfml") {
        display = new SfmlDisplay();
        display_type = 1;
    } else {
        display = new NcursesDisplay();
    }

    std::vector<Krell::IModule *> modules;
    modules.push_back(new BatteryModule());
    modules.push_back(new DateTime());
    modules.push_back(new OSModule());
    modules.push_back(new Hostname());
    modules.push_back(new CpuModule());
    modules.push_back(new RamModule());
    modules.push_back(new DiskModule());
    modules.push_back(new NetworkModule());
    modules.push_back(new UptimeModule());
    modules.push_back(new TemperatureModule());
    

    display->init();
    sf::Clock updateClock;
    int res = 0;

    for (auto &module : modules)
        module->update();
    while (true) {
        if (updateClock.getElapsedTime().asMilliseconds() >= 1000) {
            for (auto &module : modules)
                module->update();
            updateClock.restart();
        }

        display->display(modules);
        res = display->handle_inputs();
        if (res == 1)
            break;
        if (res == 2) {
            display->stop();
            delete display;
            if (display_type == 1)
                display = new NcursesDisplay();
            else
                display = new SfmlDisplay();
            display_type = (display_type + 1) % 2;
            display->init();
        }
    }
    display->stop();

    for (auto &mod : modules) {
        delete mod;
    }
    delete display;
    return 0;
}
