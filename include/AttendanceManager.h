#pragma once
#include <string>
#include <vector>
#include "AttendanceRecord.h"

class AttendanceManager
{
public:
    AttendanceManager(const std::string &dir = "data/attendance/");

    // Teacher action
    void markAttendance(int courseId,
                        const std::string &date,
                        const std::vector<int> &studentIds,
                        const std::vector<bool> &presentFlags);

    // Student
    std::vector<AttendanceRecord> getAttendanceForCourse(int courseId) const;

private:
    std::string directory;
    std::string makeFilename(int courseId, const std::string &date) const;
};
