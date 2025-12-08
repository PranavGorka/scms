#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

#include "../include/Course.h"
#include "../include/Logger.h"

class CourseManager
{
public:
    CourseManager(const std::string &file = "data/courses.csv");
    ~CourseManager();

    void load();
    void save();

    // CRUD
    int addCourse(const std::string &title, int credits, int capacity);
    bool updateCourse(int courseId, const std::string &newTitle, int newCredits, int newCapacity);
    bool deleteCourse(int courseId);

    // Enrollment
    bool enrollStudent(int courseId, int studentId);
    bool dropStudent(int courseId, int studentId);

    // Teacher assignment
    bool assignTeacher(int courseId, int teacherUserId);
    bool unassignTeacher(int courseId);

    // Query
    std::shared_ptr<Course> getCourseById(int id) const;
    std::vector<std::shared_ptr<Course>> listAllCourses() const;
    std::vector<std::shared_ptr<Course>> listCoursesByTeacher(int teacherUserId) const;

private:
    std::string filepath;
    int nextId{5001};

    std::unordered_map<int, std::shared_ptr<Course>> courses;
};
