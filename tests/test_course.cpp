// Simple main-based tests for Course & CourseManager
// Steps: add course, assign teacher, enroll student, prevent over-enrollment

#include <iostream>
#include <filesystem>
#include "CourseManager.h"

int main()
{
    using std::cout;
    using std::endl;

    const std::string testCourses = "data/test_courses.csv";

    // Clean previous test data
    try
    {
        std::filesystem::remove(testCourses);
    }
    catch (...)
    {
    }

    CourseManager cm(testCourses);

    bool ok = true;

    // 1) Add course
    int cid = cm.addCourse("Math-101", 3, 1); // capacity = 1 to test over-enrollment
    auto cptr = cm.getCourseById(cid);
    if (cptr && cptr->getCapacity() == 1 && cptr->getTitle() == "Math-101")
        cout << "[Course] Add course: PASS (id=" << cid << ")\n";
    else
    {
        ok = false;
        cout << "[Course] Add course: FAIL\n";
    }

    // 2) Assign teacher
    int teacherUserId = 2001;
    bool assigned = cm.assignTeacher(cid, teacherUserId);
    cptr = cm.getCourseById(cid);
    if (assigned && cptr && cptr->getTeacherId() == teacherUserId)
        cout << "[Course] Assign teacher: PASS\n";
    else
    {
        ok = false;
        cout << "[Course] Assign teacher: FAIL\n";
    }

    // 3) Enroll student (should succeed, capacity 1)
    int s1 = 3001;
    bool e1 = cm.enrollStudent(cid, s1);
    if (e1 && cptr && cptr->getEnrolledStudents().size() == 1)
        cout << "[Course] Enroll student: PASS\n";
    else
    {
        ok = false;
        cout << "[Course] Enroll student: FAIL\n";
    }

    // 4) Prevent over-enrollment (second student should fail)
    int s2 = 3002;
    bool e2 = cm.enrollStudent(cid, s2);
    if (!e2)
        cout << "[Course] Prevent over-enrollment: PASS\n";
    else
    {
        ok = false;
        cout << "[Course] Prevent over-enrollment: FAIL\n";
    }

    cout << (ok ? "OVERALL: PASS\n" : "OVERALL: FAIL\n");
    return ok ? 0 : 1;
}
