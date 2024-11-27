#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <ctime>
#include <iomanip>
#include "gameConfig.h"

/**
* 用于日志输出
**/
class Logger {
public:
    enum LogLevel {
        DEBUG,
        INFO,
        WARNING,
        ERR,
    };
    // 获取单例实例
    static Logger& getInstance(const std::string& filename = "") {
        static Logger instance(filename);
        return instance;
    }

    // 禁止拷贝构造和赋值操作
    Logger(const GameConfig&) = delete;
    Logger& operator=(const Logger&) = delete;

    Logger(const std::string& filename) : logFile(filename, std::ios::app) {
        if (!logFile.is_open()) {
            std::cerr << "Unable to open log file: " << filename << std::endl;
        }
    }

    ~Logger() {
        if (logFile.is_open()) {
            logFile.close();
        }
    }

    void log(LogLevel level, const std::string& message) {
        std::lock_guard<std::mutex> lock(logMutex);
        if (logFile.is_open()) {
            logFile << getCurrentTime() << 
                " [" << logLevelToString(level) << "] " <<
                "|" << __FILE__ << "|" << __LINE__ << "|" <<
                 message << std::endl;
        }
    }

private:
    std::ofstream logFile;
    std::mutex logMutex;

    inline std::tm localtime_xp(std::time_t timer)
    {
        std::tm bt{};
#if defined(__unix__)
        localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
        localtime_s(&bt, &timer);
#else
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        bt = *std::localtime(&timer);
#endif
        return bt;
    }

    // default = "YYYY-MM-DD HH:MM:SS"
    inline std::string time_stamp(const std::string& fmt = "%F %T")
    {
        auto bt = localtime_xp(std::time(0));
        char buf[64];
        return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
    }


    std::string getCurrentTime() {
        return time_stamp();
    }

    std::string logLevelToString(LogLevel level) {
        switch (level) {
        case DEBUG:   return "DEBUG";
        case INFO:    return "INFO";
        case WARNING: return "WARNING";
        case ERR:   return "ERROR";
        default:      return "UNKNOWN";
        }
    }
};


/**
int main() {
    Logger::getInstance("game.log");

    Logger::getInstance()（.log(Logger::DEBUG, "This is a debug message.");
    Logger::getInstance().log(Logger::INFO, "Game started successfully.");
    Logger::getInstance().log(Logger::WARNING, "Low memory warning.");
    Logger::getInstance().log(Logger::ERR, "Failed to load resource.");

    return 0;
}

**/