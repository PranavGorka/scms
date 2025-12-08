#include "../include/Teacher.h"
#include <algorithm>
#include <iostream>
using namespace std;

Teacher::Teacher(int id, const string &name, const string &email,
                 const string &username, const string &passwordHash)
    : User(id, name, email, username, passwordHash, /*salt*/ string(), Role::TEACHER) {}

void Teacher::printProfile() const {
    cout << "Teacher Profile\n";
    cout << "ID: " << getId() << "\n";
    cout << "Name: " << getName() << "\n";
    cout << "Email: " << getEmail() << "\n";
    cout << "Username: " << getUsername() << "\n";
    cout << "Teaching courses: ";
    if (teachingCourses.empty()) {
        cout << "(none)\n";
    } else {
        for (size_t i = 0; i < teachingCourses.size(); ++i) {
            cout << teachingCourses[i] << (i + 1 < teachingCourses.size() ? ", " : "\n");
        }
    }
}

void Teacher::addCourse(int courseId) {
    if (find(teachingCourses.begin(), teachingCourses.end(), courseId) == teachingCourses.end()) {
        teachingCourses.push_back(courseId);
    }
}

void Teacher::removeCourse(int courseId) {
    auto it = find(teachingCourses.begin(), teachingCourses.end(), courseId);
    if (it != teachingCourses.end()) teachingCourses.erase(it);
}

const vector<int>& Teacher::getTeachingCourses() const { return teachingCourses; }
