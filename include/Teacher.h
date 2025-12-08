#pragma once
#include "User.h"
#include <vector>
using namespace std;

class Teacher : public User {
public:
    Teacher() = default;
    Teacher(int id, const string &name, const string &email,
            const string &username, const string &passwordHash);

    void printProfile() const override;

    
    void addCourse(int courseId);
    void removeCourse(int courseId);
    const vector<int>& getTeachingCourses() const;

private:
    vector<int> teachingCourses;
};
