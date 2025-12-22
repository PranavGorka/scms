#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include "Exam.h"

class ExamManager
{
public:
    ExamManager(const std::string &dir = "data/exams/");

    int createExam(int courseId, const std::string &date, int maxMarks);
    void enterMarks(int examId, int studentId, int marks);

    std::vector<Exam> getExamsForCourse(int courseId) const;
    Exam getExamById(int examId) const;

private:
    std::string directory;
    int nextExamId{9001};

    void saveExam(const Exam &exam) const;
    Exam loadExam(const std::string &file) const;
};
