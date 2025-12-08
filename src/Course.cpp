#include "../include/Course.h"
#include <algorithm>

Course::Course(int id, const std::string &title, int credits, int capacity, int teacherId)
    : id(id), title(title), credits(credits), capacity(capacity), teacherId(teacherId) {}

int Course::getId() const { return id; }
const std::string &Course::getTitle() const { return title; }
int Course::getCredits() const { return credits; }
int Course::getCapacity() const { return capacity; }

void Course::setTitle(const std::string &t) { title = t; }
void Course::setCredits(int c) { credits = c; }
void Course::setCapacity(int c) { capacity = c; }

int Course::getTeacherId() const { return teacherId; }
void Course::setTeacherId(int tid) { teacherId = tid; }

const std::vector<int> &Course::getEnrolledStudents() const
{
    return enrolledStudents;
}

bool Course::enrollStudent(int studentId)
{
    if ((int)enrolledStudents.size() >= capacity)
        return false;
    if (std::find(enrolledStudents.begin(), enrolledStudents.end(), studentId) != enrolledStudents.end())
        return false;

    enrolledStudents.push_back(studentId);
    return true;
}

bool Course::dropStudent(int studentId)
{
    auto it = std::find(enrolledStudents.begin(), enrolledStudents.end(), studentId);
    if (it == enrolledStudents.end())
        return false;
    enrolledStudents.erase(it);
    return true;
}
