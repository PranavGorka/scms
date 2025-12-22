#pragma once
#include <string>
#include <map>
#include <iostream>

class Exam
{
public:
    Exam() = default;
    Exam(int examId, int courseId, const std::string &date, int maxMarks);

    int getExamId() const;
    int getCourseId() const;
    std::string getDate() const;
    int getMaxMarks() const;

    friend std::ostream &operator<<(std::ostream &os, const Exam &e);

    void addMarks(int studentId, int marks);
    const std::map<int, int> &getMarks() const;

    bool operator<(const Exam &other) const;

private:
    int examId{0};
    int courseId{0};
    std::string date; // YYYY-MM-DD
    int maxMarks{0};
    std::map<int, int> marks;
};
