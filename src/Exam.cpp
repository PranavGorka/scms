#include "../include/Exam.h"
#include <stdexcept>
#include <iostream>

Exam::Exam(int eid, int cid, const std::string &d, int maxM)
    : examId(eid), courseId(cid), date(d), maxMarks(maxM) {}

int Exam::getExamId() const { return examId; }
int Exam::getCourseId() const { return courseId; }
std::string Exam::getDate() const { return date; }
int Exam::getMaxMarks() const { return maxMarks; }

void Exam::addMarks(int studentId, int m)
{
    if (m < 0 || m > maxMarks)
    {
        throw std::invalid_argument("Marks out of range");
    }
    marks[studentId] = m;
}

const std::map<int, int> &Exam::getMarks() const
{
    return marks;
}

bool Exam::operator<(const Exam &other) const
{
    return date < other.date;
}

std::ostream &operator<<(std::ostream &os, const Exam &e)
{
    os << "Exam ID: " << e.getExamId()
       << ", Course ID: " << e.getCourseId()
       << ", Date: " << e.getDate()
       << ", Max Marks: " << e.getMaxMarks();

    return os;
}