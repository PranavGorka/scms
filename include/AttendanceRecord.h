#pragma once
#include <string>
#include <map>
#include <iostream>

class AttendanceRecord
{
public:
    AttendanceRecord() = default;
    AttendanceRecord(int courseId, const std::string &date);

    int getCourseId() const;
    std::string getDate() const;

    void markStudent(int studentId, bool present);
    const std::map<int, bool> &getRecords() const;

    friend std::ostream &operator<<(std::ostream &os, const AttendanceRecord &ar);
    friend std::istream &operator>>(std::istream &is, AttendanceRecord &ar);

private:
    int courseId{0};
    std::string date;               // YYYY-MM-DD
    std::map<int, bool> attendance; // studentId -> present/absent
};
