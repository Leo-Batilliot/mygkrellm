/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** IModule
*/

#ifndef IMODULE_HPP_
#define IMODULE_HPP_
#include <string>
#include <map>

namespace Krell {
    class IModule {
        public:
            virtual ~IModule() = default;

            // Actualise les données du module
            virtual void update() = 0;

            // Retourne le nom du module (ex "CPU")
            virtual std::string getName() const  = 0;

            // Retourne un dictionnaire contenant les données avec leur "nom"
            virtual const std::map<std::string, std::string> &getData() const = 0;
        protected:
        private:
    };
}

#endif /* !IMODULE_HPP_ */
