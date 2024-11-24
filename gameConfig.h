#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>

#ifndef GAME_CONFIG_H
#define GAME_CONFIG_H

/*
* put some game parameters into external configuration
* By X  
*/

class GameConfig {
public:
    // Get a singleton instance
    static GameConfig& getInstance(const std::string& filename = "") {
        static GameConfig instance(filename);
        return instance;
    }

    // Prevent copy construction and assignment operations
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    // get configure items
    template<typename T>
    T get(const std::string& section, const std::string& key, const T& defaultValue) {
        std::lock_guard<std::mutex> lock(configMutex);
        if (configMap.find(section) != configMap.end() && configMap[section].find(key) != configMap[section].end()) {
            std::istringstream iss(configMap[section][key]);
            T value;
            iss >> value;
            return value;
        }
        return defaultValue;
    }

    // Set Configuration Items
    template<typename T>
    void set(const std::string& section, const std::string& key, const T& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ostringstream oss;
        oss << value;
        configMap[section][key] = oss.str();
    }

    // Save the configuration file
    void saveConfig() {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open config file for writing: " << filename << std::endl;
            return;
        }

        for (const auto& section : configMap) {
            file << "[" << section.first << "]" << std::endl; // write Section
            for (const auto& pair : section.second) {
                file << pair.first << "=" << pair.second << std::endl; // write Key=Value
            }
            file << std::endl; // spaces between the Section 
        }
        file.close();
    }

private:
    std::string filename;
    std::map<std::string, std::map<std::string, std::string>> configMap; // Section -> Key-Value Map
    std::mutex configMutex;

    // private constructor
    GameConfig(const std::string& filename) : filename(filename) {
        loadConfig();
    }

    // load configuration
    void loadConfig() {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open config file: " << filename << std::endl;
            return;
        }

        std::string line;
        std::string currentSection;

        while (std::getline(file, line)) {
            // ignore spaces and comments
            if (line.empty() || line[0] == '#') continue;

            // check Section
            if (line[0] == '[' && line.back() == ']') {
                currentSection = line.substr(1, line.size() - 2);
                continue;
            }

            // process Key=Value
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos && !currentSection.empty()) {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                configMap[currentSection][key] = value;
            }
        }
        file.close();
    }
};

#endif GAME_CONFIG_H