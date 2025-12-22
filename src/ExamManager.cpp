#include "../include/ExamManager.h"
#include "../include/Logger.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

ExamManager::ExamManager(const std::string &dir)
    : directory(dir)
{
    std::filesystem::create_directories(directory);
}

int ExamManager::createExam(int courseId, const std::string &date, int maxMarks)
{
    int id = nextExamId++;
    Exam exam(id, courseId, date, maxMarks);
    saveExam(exam);

    Logger::log("ExamManager", Logger::Level::INFO,
                "Created exam " + std::to_string(id) +
                    " for course " + std::to_string(courseId));
    return id;
}

void ExamManager::enterMarks(int examId, int studentId, int marks)
{
    std::string file = directory + "exam_" + std::to_string(examId) + ".dat";
    Exam exam = loadExam(file);
    exam.addMarks(studentId, marks);
    saveExam(exam);

    Logger::log("ExamManager", Logger::Level::INFO,
                "Marks entered: exam " + std::to_string(examId) +
                    ", student " + std::to_string(studentId));
}

std::vector<Exam> ExamManager::getExamsForCourse(int courseId) const
{
    std::vector<Exam> exams;

    for (auto &e : std::filesystem::directory_iterator(directory))
    {
        Exam exam = loadExam(e.path().string());
        if (exam.getCourseId() == courseId)
            exams.push_back(exam);
    }
    std::sort(exams.begin(), exams.end()); // uses operator<
    return exams;
}

Exam ExamManager::getExamById(int examId) const
{
    std::string file = directory + "exam_" + std::to_string(examId) + ".dat";
    return loadExam(file);
}

void ExamManager::saveExam(const Exam &exam) const
{
    std::ofstream out(directory + "exam_" +
                          std::to_string(exam.getExamId()) + ".dat",
                      std::ios::binary | std::ios::trunc);

    out << exam.getExamId() << "\n"
        << exam.getCourseId() << "\n"
        << exam.getDate() << "\n"
        << exam.getMaxMarks() << "\n"
        << exam.getMarks().size() << "\n";

    for (auto &p : exam.getMarks())
    {
        out << p.first << " " << p.second << "\n";
    }
}

Exam ExamManager::loadExam(const std::string &file) const
{
    std::ifstream in(file, std::ios::binary);
    if (!in.is_open())
        throw std::runtime_error("Exam file not found");

    int examId, courseId, maxMarks;
    std::string date;
    size_t count;

    in >> examId >> courseId >> date >> maxMarks >> count;
    Exam exam(examId, courseId, date, maxMarks);

    for (size_t i = 0; i < count; ++i)
    {
        int sid, m;
        in >> sid >> m;
        exam.addMarks(sid, m);
    }
    return exam;
}
