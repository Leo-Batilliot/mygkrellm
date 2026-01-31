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
#include <memory>
#include <exception>
#include <iostream>
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
    try {
        std::unique_ptr<Krell::IDisplay> display;
        int display_type = 0;

        if (ac > 1 && std::string(av[1]) == "-sfml") {
            display = std::make_unique<SfmlDisplay>();
            display_type = 1;
        } else {
            display = std::make_unique<NcursesDisplay>();
        }

        std::vector<std::unique_ptr<Krell::IModule>> modules;
        modules.push_back(std::make_unique<BatteryModule>());
        modules.push_back(std::make_unique<DateTime>());
        modules.push_back(std::make_unique<OSModule>());
        modules.push_back(std::make_unique<Hostname>());
        modules.push_back(std::make_unique<CpuModule>());
        modules.push_back(std::make_unique<RamModule>());
        modules.push_back(std::make_unique<DiskModule>());
        modules.push_back(std::make_unique<NetworkModule>());
        modules.push_back(std::make_unique<UptimeModule>());
        modules.push_back(std::make_unique<TemperatureModule>());

        display->init();
        sf::Clock updateClock;
        int res = 0;

        std::vector<Krell::IModule *> rawModules;
        rawModules.reserve(modules.size());
        for (auto &m : modules)
            rawModules.push_back(m.get());

        for (auto &module : rawModules)
            module->update();
        while (true) {
            if (updateClock.getElapsedTime().asMilliseconds() >= 1000) {
                for (auto &module : rawModules)
                    module->update();
                updateClock.restart();
            }

            display->display(rawModules);
            res = display->handle_inputs();
            if (res == 1)
                break;
            if (res == 2) {
                display->stop();
                if (display_type == 1)
                    display = std::make_unique<NcursesDisplay>();
                else
                    display = std::make_unique<SfmlDisplay>();
                display_type = (display_type + 1) % 2;
                display->init();
            }
        }
        display->stop();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "Unknown error" << std::endl;
        return 84;
    }
}
