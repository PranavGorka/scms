#pragma once
#include <string>
#include <vector>

class Course
{
public:
    Course() = default;
    Course(int id, const std::string &title, int credits, int capacity, int teacherId = -1);

    int getId() const;
    const std::string &getTitle() const;
    int getCredits() const;
    int getCapacity() const;

    void setTitle(const std::string &t);
    void setCredits(int c);
    void setCapacity(int c);

    int getTeacherId() const;
    void setTeacherId(int tid);
    bool hasTeacher() const { return teacherId != -1; }

    const std::vector<int> &getEnrolledStudents() const;

    bool enrollStudent(int studentId);
    bool dropStudent(int studentId);

private:
    int id{0};
    std::string title;
    int credits{0};
    int capacity{0};
    int teacherId{-1}; // -1 means no teacher assigned
    std::vector<int> enrolledStudents;
};
