/*
** EPITECH PROJECT, 2025
** G-PDG-300-LIL-3-1-PDGRUSH4-17
** File description:
** DiskModule.hpp
*/

#ifndef DISKMODULE_HPP_
#define DISKMODULE_HPP_

#include "interfaces/IModule.hpp"
#include <sys/statvfs.h>
#include <string>
#include <map>
#include <cmath>

class DiskModule : public Krell::IModule {
    private:
        std::string _name;
        std::map<std::string, std::string> _data;

        std::string formatBytes(unsigned long long bytes)
        {
            float sizeGB = bytes / (1024 *1024 *1024);
            int integer = (int)sizeGB;
            int decimal = (int)((sizeGB - integer) * 10);
            return std::to_string(integer) + "." + std::to_string(decimal) + " GB";
        }

    public:
        DiskModule() : _name("Disk")
        {
            _data["Total"] = "Unknown";
            _data["Free"]  = "Unknown";
            _data["Used"]  = "Unknown";
            _data["Percent"] = "0%";
            update();
        }
        virtual ~DiskModule() = default;

        void update() override
        {
            struct statvfs buffer;

            if (statvfs("/", &buffer) == 0) {                
                unsigned long long totalBytes = buffer.f_blocks * buffer.f_frsize;
                unsigned long long availableBytes = buffer.f_bavail * buffer.f_frsize;
                unsigned long long usedBytes = totalBytes - availableBytes;

                int percent = 0;
                if (totalBytes > 0) {
                    percent = (usedBytes * 100) / totalBytes;
                }

                _data["Total"] = formatBytes(totalBytes);
                _data["Free"]  = formatBytes(availableBytes);
                _data["Used"]  = formatBytes(usedBytes);
                _data["Percent"] = std::to_string(percent) + "%";
            } 
            else {
                _data["Total"] = "Error";
                _data["Percent"] = "---";
            }
        }

        std::string getName() const override {return _name;}
        const std::map<std::string, std::string> &getData() const override {return _data;}
};

#endif /* !DISKMODULE_HPP_ */