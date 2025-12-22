#include "../include/AttendanceManager.h"
#include "Logger.h"
#include <fstream>
#include <filesystem>

AttendanceManager::AttendanceManager(const std::string &dir)
    : directory(dir)
{
    std::filesystem::create_directories(directory);
}

std::string AttendanceManager::makeFilename(int courseId,
                                            const std::string &date) const
{
    return directory + "course_" + std::to_string(courseId) + "_" + date + ".dat";
}

void AttendanceManager::markAttendance(int courseId,
                                       const std::string &date,
                                       const std::vector<int> &studentIds,
                                       const std::vector<bool> &presentFlags)
{
    AttendanceRecord record(courseId, date);

    for (size_t i = 0; i < studentIds.size(); ++i)
    {
        record.markStudent(studentIds[i], presentFlags[i]);
    }

    std::string filename = makeFilename(courseId, date);

    std::fstream fs(filename, std::ios::out | std::ios::binary);
    fs << record; // uses operator<<
    fs.close();

    Logger::log("AttendanceManager", Logger::Level::INFO,
                "Attendance marked for course " +
                    std::to_string(courseId) + " on " + date);
}

// Reads all attendance files for a course
std::vector<AttendanceRecord>
AttendanceManager::getAttendanceForCourse(int courseId) const
{

    std::vector<AttendanceRecord> records;

    for (auto &entry : std::filesystem::directory_iterator(directory))
    {
        std::string fname = entry.path().filename().string();
        if (fname.find("course_" + std::to_string(courseId) + "_") == 0)
        {
            std::fstream fs(entry.path(), std::ios::in | std::ios::binary);
            AttendanceRecord ar;
            fs.seekg(0);
            fs >> ar;
            fs.close();
            records.push_back(ar);
        }
    }
    return records;
}
