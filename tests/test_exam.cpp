// Simple main-based tests for Exam & ExamManager & ReportGenerator
// Steps: create exam, enter marks, invalid marks exception, generate report

#include <iostream>
#include <filesystem>
#include <vector>
#include <stdexcept>
#include "ExamManager.h"
#include "ReportGenerator.h"

int main()
{
    using std::cout;
    using std::endl;

    const std::string testDir = "data/exams_test/";

    // Clean previous test dir
    try
    {
        if (std::filesystem::exists(testDir))
            std::filesystem::remove_all(testDir);
    }
    catch (...)
    {
    }

    ExamManager em(testDir);

    bool ok = true;

    // 1) Create exam
    int courseId = 7001;
    int examId = -1;
    try
    {
        examId = em.createExam(courseId, "2025-12-22", 100);
        auto exam = em.getExamById(examId);
        if (exam.getExamId() == examId && exam.getCourseId() == courseId && exam.getMaxMarks() == 100)
        {
            cout << "[Exam] Create exam: PASS (id=" << examId << ")\n";
        }
        else
        {
            ok = false;
            cout << "[Exam] Create exam: FAIL - mismatched data\n";
        }
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Exam] Create exam: FAIL - " << e.what() << "\n";
    }

    // 2) Enter marks (valid)
    try
    {
        em.enterMarks(examId, 42, 85);
        auto ex = em.getExamById(examId);
        auto it = ex.getMarks().find(42);
        if (it != ex.getMarks().end() && it->second == 85)
        {
            cout << "[Exam] Enter marks (valid): PASS\n";
        }
        else
        {
            ok = false;
            cout << "[Exam] Enter marks (valid): FAIL - not saved\n";
        }
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Exam] Enter marks (valid): FAIL - " << e.what() << "\n";
    }

    // 3) Invalid marks exception
    try
    {
        em.enterMarks(examId, 42, 150); // > maxMarks -> should throw
        ok = false;
        cout << "[Exam] Invalid marks (expected exception): FAIL - accepted invalid\n";
    }
    catch (const std::invalid_argument &)
    {
        cout << "[Exam] Invalid marks exception: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Exam] Invalid marks exception: FAIL - " << e.what() << "\n";
    }

    // 4) Generate report using ReportGenerator<Exam>
    try
    {
        auto exams = em.getExamsForCourse(courseId);
        ReportGenerator<Exam>::generate(exams, "Exam Report for course 7001");
        cout << "[Exam] Report generation: PASS (see printed report)\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Exam] Report generation: FAIL - " << e.what() << "\n";
    }

    cout << (ok ? "OVERALL: PASS\n" : "OVERALL: FAIL\n");
    return ok ? 0 : 1;
}
