#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
/**
* ���ڽ��ɱ�����ŵ��ⲿ������ȥ
**/
class GameConfig {
public:
    // ��ȡ����ʵ��
    static GameConfig& getInstance(const std::string& filename = "") {
        static GameConfig instance(filename);
        return instance;
    }

    // ��ֹ��������͸�ֵ����
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    // ��ȡ������
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

    // ����������
    template<typename T>
    void set(const std::string& section, const std::string& key, const T& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ostringstream oss;
        oss << value;
        configMap[section][key] = oss.str();
    }

    // ���������ļ�
    void saveConfig() {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open config file for writing: " << filename << std::endl;
            return;
        }

        for (const auto& section : configMap) {
            file << "[" << section.first << "]" << std::endl; // д�� Section
            for (const auto& pair : section.second) {
                file << pair.first << "=" << pair.second << std::endl; // д�� Key=Value
            }
            file << std::endl; // Section ֮��������
        }
        file.close();
    }

private:
    std::string filename;
    std::map<std::string, std::map<std::string, std::string>> configMap; // Section -> Key-Value Map
    std::mutex configMutex;

    // ˽�й��캯��
    GameConfig(const std::string& filename) : filename(filename) {
        loadConfig();
    }

    // ���������ļ�
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
            // ���Կ��к�ע��
            if (line.empty() || line[0] == '#') continue;

            // ��� Section
            if (line[0] == '[' && line.back() == ']') {
                currentSection = line.substr(1, line.size() - 2);
                continue;
            }

            // ���� Key=Value
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

