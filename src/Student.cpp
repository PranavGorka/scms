#include "../include/Student.h"
#include <algorithm>
#include <iostream>
using namespace std;

Student::Student(int id, const string &name, const string &email,
                 const string &username, const string &passwordHash)
    : User(id, name, email, username, passwordHash, /*salt*/ string(), Role::STUDENT) {}

void Student::printProfile() const {
    cout << "Student Profile\n";
    cout << "ID: " << getId() << "\n";
    cout << "Name: " << getName() << "\n";
    cout << "Email: " << getEmail() << "\n";
    cout << "Username: " << getUsername() << "\n";
    cout << "Enrolled courses: ";
    if (enrolledCourses.empty()) {
        cout << "(none)\n";
    } else {
        for (size_t i = 0; i < enrolledCourses.size(); ++i) {
            cout << enrolledCourses[i] << (i + 1 < enrolledCourses.size() ? ", " : "\n");
        }
    }
}

void Student::enrollCourse(int courseId) {
    if (find(enrolledCourses.begin(), enrolledCourses.end(), courseId) == enrolledCourses.end()) {
        enrolledCourses.push_back(courseId);
    }
}

void Student::dropCourse(int courseId) {
    auto it = find(enrolledCourses.begin(), enrolledCourses.end(), courseId);
    if (it != enrolledCourses.end()) enrolledCourses.erase(it);
}

const vector<int>& Student::getEnrolledCourses() const { return enrolledCourses; }
