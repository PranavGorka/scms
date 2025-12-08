#pragma once
#include "../include/User.h"
#include <vector>
using namespace std;

class Student : public User {
public:
    Student() = default;
    Student(int id, const string &name, const string &email,
            const string &username, const string &passwordHash);

    void printProfile() const override;


    void enrollCourse(int courseId);
    void dropCourse(int courseId);
    const vector<int>& getEnrolledCourses() const;

private:
    vector<int> enrolledCourses;
};
