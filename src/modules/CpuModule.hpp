/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** CpuModule.hpp
*/

#ifndef CPUMODULE_HPP_
#define CPUMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

class CpuModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;
        std::map<std::string, std::string> _coresUsage;
        
        unsigned long long _prevTotal = 0;
        unsigned long long _prevIdle = 0;
        std::map<std::string, std::pair<unsigned long long, unsigned long long>> _prevCores;

        std::string trim(const std::string& str)
        {
            size_t first = str.find_first_not_of(" \t");
            if (std::string::npos == first) return str;
            size_t last = str.find_last_not_of(" \t");
            return str.substr(first, (last - first + 1));
        }

    public:
        CpuModule() : _name("CPU")
        {
            _data["Model"] = "Unknown CPU";
            _data["Cores"] = "0";
            _data["Frequency"] = "0.00 GHz";
            _data["Usage"] = "0%";
            update();
        }
        virtual ~CpuModule() = default;

        void update() override
        {
            updateCpuInfo();
            updateCpuUsage();
            updateCoresUsage();
        }

        void updateCpuInfo()
        {
            std::ifstream file("/proc/cpuinfo");
            std::string line;
            int cores = 0;

            if (!file.is_open()) return;

            while (std::getline(file, line)) {
                if (line.find("processor") == 0) {
                    cores++;
                }
                else if (line.find("model name") == 0) {
                    size_t pos = line.find(":");
                    if (pos != std::string::npos) {
                        _data["Model"] = trim(line.substr(pos + 1));
                    }
                }
                else if (line.find("cpu MHz") == 0) {
                    size_t pos = line.find(":");
                    if (pos != std::string::npos) {
                        _data["Frequency"] = trim(line.substr(pos + 1)) + " MHz";
                    }
                }
            }
            _data["Cores"] = std::to_string(cores);
        }

        void updateCpuUsage()
        {
            std::ifstream file("/proc/stat");
            std::string line;
            
            if (!file.is_open()) return;

            std::getline(file, line);
            std::stringstream ss(line);
            std::string cpuLabel;
            
            unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
            
            ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

            unsigned long long currentIdle = idle + iowait;
            unsigned long long currentTotal = user + nice + system + idle + iowait + irq + softirq + steal;

            unsigned long long diffIdle = currentIdle - _prevIdle;
            unsigned long long diffTotal = currentTotal - _prevTotal;

            float usage = 0.0f;
            if (diffTotal > 0) {
                usage = (100.0f * (diffTotal - diffIdle)) / diffTotal;
            }
            _prevTotal = currentTotal;
            _prevIdle = currentIdle;

            int usageInt = (int)usage;
            int usageDec = (int)((usage - usageInt) * 10);
            _data["Usage"] = std::to_string(usageInt) + "." + std::to_string(usageDec) + "%";
        }

        void updateCoresUsage()
        {
            std::ifstream file("/proc/stat");
            std::string line;

            if (!file.is_open()) return;

            while (std::getline(file, line)) {
                if (line.compare(0, 3, "cpu") == 0 && isdigit(line[3])) {
                    std::stringstream ss(line);
                    std::string cpuLabel;
                    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal;
                    
                    ss >> cpuLabel >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

                    unsigned long long currentIdle = idle + iowait;
                    unsigned long long currentTotal = user + nice + system + idle + iowait + irq + softirq + steal;

                    unsigned long long prevIdle = _prevCores[cpuLabel].second;
                    unsigned long long prevTotal = _prevCores[cpuLabel].first;

                    unsigned long long diffIdle = currentIdle - prevIdle;
                    unsigned long long diffTotal = currentTotal - prevTotal;

                    float usage = 0.0f;
                    if (diffTotal > 0) {
                        usage = (100.0f * (diffTotal - diffIdle)) / diffTotal;
                    }

                    _prevCores[cpuLabel] = {currentTotal, currentIdle};

                    int usageInt = (int)usage;
                    int usageDec = (int)((usage - usageInt) * 10);
                    _coresUsage[cpuLabel] = std::to_string(usageInt) + "." + std::to_string(usageDec) + "%";
                }
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
        std::map<std::string, std::string> &getCoreUsage() {return _coresUsage;}

};

#endif /* !CPUMODULE_HPP_ */