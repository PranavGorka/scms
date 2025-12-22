// Simple main-based tests for AttendanceManager & AttendanceRecord
// Steps: mark attendance, read from file, verify present/absent values

#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include "AttendanceManager.h"

int main()
{
    using std::cout;
    using std::endl;

    const std::string testDir = "data/attendance_test/";

    // Clean previous test data directory
    try
    {
        if (std::filesystem::exists(testDir))
            std::filesystem::remove_all(testDir);
    }
    catch (...)
    {
    }

    AttendanceManager am(testDir);

    bool ok = true;

    // 1) Mark attendance
    int courseId = 6001;
    std::string date = "2025-12-22";
    std::vector<int> studentIds{1, 2, 3};
    std::vector<bool> present{true, false, true};
    try
    {
        am.markAttendance(courseId, date, studentIds, present);
        cout << "[Attendance] Mark attendance: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Attendance] Mark attendance: FAIL - " << e.what() << "\n";
    }

    // 2) Read attendance for course
    try
    {
        auto records = am.getAttendanceForCourse(courseId);
        bool found = false;
        for (const auto &rec : records)
        {
            if (rec.getDate() == date)
            {
                found = true;
                const auto &m = rec.getRecords();
                bool v1 = m.at(1) == true;
                bool v2 = m.at(2) == false;
                bool v3 = m.at(3) == true;
                if (v1 && v2 && v3)
                {
                    cout << "[Attendance] Read and verify values: PASS\n";
                }
                else
                {
                    ok = false;
                    cout << "[Attendance] Verify values: FAIL\n";
                }
                break;
            }
        }
        if (!found)
        {
            ok = false;
            cout << "[Attendance] Read file for date: FAIL - not found\n";
        }
        else
        {
            cout << "[Attendance] Read file for date: PASS\n";
        }
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Attendance] Read file: FAIL - " << e.what() << "\n";
    }

    cout << (ok ? "OVERALL: PASS\n" : "OVERALL: FAIL\n");
    return ok ? 0 : 1;
}
