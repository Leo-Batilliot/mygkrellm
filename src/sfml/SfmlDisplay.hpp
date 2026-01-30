/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** SfmlDisplay
*/
#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include "interfaces/IDisplay.hpp"
#include "SfmlConfig.hpp"
#include <vector>

struct ModuleWrapper {
    Krell::IModule* module;
    sf::RectangleShape background;
    bool isVisible = true;
    bool isDragging = false;
};

class SfmlDisplay : public Krell::IDisplay {
    public:
        SfmlDisplay();
        ~SfmlDisplay();

        void init() override;
        void stop() override;
        void display(const std::vector<Krell::IModule *> &modules) override;
        bool handle_inputs() override;

    private:
        sf::RenderWindow _window;
        sf::Font _font;
        std::vector<ModuleWrapper> _modules;
        
        int _draggedIdx = -1;
        int _targetIdx = -1;
        sf::Vector2f _dragOffset;

        void syncModules(const std::vector<Krell::IModule *> &modules);
        void renderStaticStack(float &currentY, sf::Vector2i mousePos);
        void renderPreviewLine();
        void renderDraggedModule(sf::Vector2i mousePos);
        void drawModule(ModuleWrapper &wrapper, sf::Vector2f pos);
        void drawHostname(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawDateTime(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawCpu(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawNetwork(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawOS(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawRam(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);

        std::string safeGet(const std::map<std::string, std::string>& data, const std::string& key);
};

#endif