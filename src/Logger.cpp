#include "../include/Logger.h"
#include <iostream>
#include <format>                            
#include <chrono>
using namespace std;

ofstream Logger::logFile;

void Logger::init(const string& filepath) {
    logFile.open(filepath, ios::app);
    if (!logFile.is_open()) {
        cerr << "Failed to open log file: " << filepath << endl;
    }
}

void Logger::log(const string& module, Level level, const string& message) {
    if (!logFile.is_open()) {
        cerr << "Log file is not open." << endl;
        return;
    }
    logFile << "[" << getCurrentTime() << "] "
            << "[" << levelToString(level) << "] "
            << "[" << module << "] "
            << message << endl;
}

void Logger::close() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

string Logger::levelToString(Level level) {
    switch (level) {
        case Level::DEBUG: return "DEBUG";
        case Level::INFO: return "INFO";
        case Level::WARN: return "WARN";
        case Level::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}

string Logger::getCurrentTime() {
    auto now = chrono::system_clock::now();
    
    auto secs = chrono::time_point_cast<chrono::seconds>(now);
    
    string timestamp = format("{:%Y-%m-%d %H:%M:%S}", secs);
    return timestamp;
}