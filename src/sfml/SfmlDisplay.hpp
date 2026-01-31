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
        int handle_inputs() override;

    private:
        sf::RenderWindow _window;
        sf::Font _font;
        sf::Texture _lightningTexture;
        sf::Sprite _lightningSprite;
        std::vector<ModuleWrapper> _modules;
        
        int _draggedIdx = -1;
        int _targetIdx = -1;
        sf::Vector2f _dragOffset;

        sf::View _view;
        float _scrollY = 0.0f;
        const float _scrollSpeed = 20.0f;
        float _maxScrollY = 0.0f;

        void syncModules(const std::vector<Krell::IModule *> &modules);
        void renderStaticStack(float &currentY, sf::Vector2i mousePos, float width, float startX);
        void renderPreviewLine(float width, float startX);
        void renderDraggedModule(sf::Vector2i mousePos, float width);
        void drawModule(ModuleWrapper &wrapper, sf::Vector2f pos, float width);
        void drawHostname(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawDateTime(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawCpu(Krell::IModule *module, const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawNetwork(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawOS(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawRam(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawBattery(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawUptime(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawTemperature(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);
        void drawDisk(const std::map<std::string, std::string>& data, sf::Vector2f pos, float& ty);

        std::string safeGet(const std::map<std::string, std::string>& data, const std::string& key);
};

#endif