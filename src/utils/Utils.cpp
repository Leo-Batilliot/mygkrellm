/*
** EPITECH PROJECT, 2026
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** utils
*/

#include <stdexcept>
#include <map>

std::string safeGet(const std::map<std::string, std::string>& data, const std::string& key)
{
    auto it = data.find(key);
    if (it != data.end())
        return it->second;
    throw std::runtime_error("Missing value : " + key);
    return "0";
}