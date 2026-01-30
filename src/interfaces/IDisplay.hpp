/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_
#include <vector>
#include "interfaces/IModule.hpp"

namespace Krell {
    class IDisplay {
        public:
            virtual ~IDisplay() = default;

            // Initialise le système pour l'affichage
            virtual void init() = 0;

            // Arrète le système pour l'affichage
            virtual void stop() = 0;

            // Affiche une frame avec les data données
            virtual void display(const std::vector<IModule *> &modules) = 0;
            
            // gère les input (return false si on doit stopper le programme)
            virtual bool handle_inputs() = 0;
        protected:
        private:
    };
}

#endif /* !IDISPLAY_HPP_ */
