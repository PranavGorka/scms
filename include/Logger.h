#pragma once
#include <string>
#include <fstream>
using namespace std;

class Logger {
public:
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR
    };

    static void init(const string& filepath);
    static void log(const string& module, Level Level, const string& message);
    static void close();

private:
    static ofstream logFile;
    static string levelToString(Level Level);
    static string getCurrentTime();
};