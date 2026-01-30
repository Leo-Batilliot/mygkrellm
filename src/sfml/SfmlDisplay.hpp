/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** SfmlDisplay
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_
#include <SFML/Graphics.hpp>
#include "interfaces/IDisplay.hpp"

class SfmlDisplay : public Krell::IDisplay{
    public:
        SfmlDisplay();
        ~SfmlDisplay();

        void init() override;
        void stop() override;
        void display(const std::vector<Krell::IModule *> &modules) override;
        bool handle_inputs() override;

    protected:
    private:
};

#endif /* !SFMLDISPLAY_HPP_ */
