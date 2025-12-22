#include "../include/AttendanceRecord.h"

AttendanceRecord::AttendanceRecord(int cid, const std::string &d)
    : courseId(cid), date(d) {}

int AttendanceRecord::getCourseId() const { return courseId; }
std::string AttendanceRecord::getDate() const { return date; }

void AttendanceRecord::markStudent(int studentId, bool present)
{
    attendance[studentId] = present;
}

const std::map<int, bool> &AttendanceRecord::getRecords() const
{
    return attendance;
}

std::ostream &operator<<(std::ostream &os, const AttendanceRecord &ar)
{
    os << ar.courseId << "\n";
    os << ar.date << "\n";
    os << ar.attendance.size() << "\n";
    for (auto &p : ar.attendance)
    {
        os << p.first << " " << p.second << "\n";
    }
    return os;
}

std::istream &operator>>(std::istream &is, AttendanceRecord &ar)
{
    size_t count;
    is >> ar.courseId;
    is >> ar.date;
    is >> count;
    ar.attendance.clear();
    for (size_t i = 0; i < count; ++i)
    {
        int sid;
        bool present;
        is >> sid >> present;
        ar.attendance[sid] = present;
    }
    return is;
}
