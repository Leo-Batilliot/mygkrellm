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
<<<<<<< HEAD
#include "modules/DateTime.hpp"
#include "modules/CpuModule.hpp"
=======
#include "modules/OSModule.hpp"
#include "modules/DateTime.hpp"
#include "modules/CpuModule.hpp"
#include "modules/RamModule.hpp"
#include "modules/NetworkModule.hpp"
>>>>>>> 14b695a (feat: add all modules + network bonus)

int main(int ac, char **av)
{
    Krell::IDisplay *display = nullptr;

    if (ac > 1 && std::string(av[1]) == "-sfml") {
        display = new SfmlDisplay();
    // } else {
    //     display = new NcursesDisplay();
    }

    std::vector<Krell::IModule *> modules;
    modules.push_back(new Hostname());
<<<<<<< HEAD
    modules.push_back(new DateTime());
    modules.push_back(new CpuModule());
=======
    modules.push_back(new OSModule());
    modules.push_back(new DateTime());
    modules.push_back(new CpuModule());
    modules.push_back(new RamModule());
    modules.push_back(new NetworkModule());
>>>>>>> 14b695a (feat: add all modules + network bonus)

    display->init();
    sf::Clock updateClock;
    bool run = true;

    while (run) {
        if (updateClock.getElapsedTime().asMilliseconds() >= 1000) {
            for (auto &module : modules)
                module->update();
            updateClock.restart();
        }

        display->display(modules);
        run = display->handle_inputs();
    }
    display->stop();

    for (auto &mod : modules) {
        delete mod;
    }
    delete display;
    return 0;
}
