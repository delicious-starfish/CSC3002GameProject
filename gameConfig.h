#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <mutex>
/**
* 用于将可变参数放到外部配置中去
**/
class GameConfig {
public:
    // 获取单例实例
    static GameConfig& getInstance(const std::string& filename = "") {
        static GameConfig instance(filename);
        return instance;
    }

    // 禁止拷贝构造和赋值操作
    GameConfig(const GameConfig&) = delete;
    GameConfig& operator=(const GameConfig&) = delete;

    // 获取配置项
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

    // 设置配置项
    template<typename T>
    void set(const std::string& section, const std::string& key, const T& value) {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ostringstream oss;
        oss << value;
        configMap[section][key] = oss.str();
    }

    // 保存配置文件
    void saveConfig() {
        std::lock_guard<std::mutex> lock(configMutex);
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open config file for writing: " << filename << std::endl;
            return;
        }

        for (const auto& section : configMap) {
            file << "[" << section.first << "]" << std::endl; // 写入 Section
            for (const auto& pair : section.second) {
                file << pair.first << "=" << pair.second << std::endl; // 写入 Key=Value
            }
            file << std::endl; // Section 之间留空行
        }
        file.close();
    }

private:
    std::string filename;
    std::map<std::string, std::map<std::string, std::string>> configMap; // Section -> Key-Value Map
    std::mutex configMutex;

    // 私有构造函数
    GameConfig(const std::string& filename) : filename(filename) {
        loadConfig();
    }

    // 加载配置文件
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
            // 忽略空行和注释
            if (line.empty() || line[0] == '#') continue;

            // 检测 Section
            if (line[0] == '[' && line.back() == ']') {
                currentSection = line.substr(1, line.size() - 2);
                continue;
            }

            // 处理 Key=Value
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

