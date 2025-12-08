#include <iostream>
#include <limits>
#include <memory>

#include "../include/Logger.h"
#include "../include/AuthManager.h"
#include "../include/CourseManager.h"
#include "../include/User.h"

// simple input helpers
static void clearStdin()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int readInt(const std::string &prompt)
{
    int x;
    while (true)
    {
        std::cout << prompt;
        if (std::cin >> x)
        {
            clearStdin();
            return x;
        }
        std::cout << "Invalid number, try again.\n";
        std::cin.clear();
        clearStdin();
    }
}

static std::string readLine(const std::string &prompt)
{
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

static void pause()
{
    std::cout << "Press Enter to continue...";
    std::cin.get();
}

int main()
{
    Logger::init("logs/scms.log");
    Logger::log("System", Logger::Level::INFO, "Application started");

    AuthManager auth("data/users.csv");
    CourseManager cm("data/courses.csv");

    int currentUserId = -1;

    while (true)
    {
        if (currentUserId < 0)
        {
            std::cout << "\n==== Smart CMS ====\n";
            std::cout << "1) Login\n";
            std::cout << "2) Register\n";
            std::cout << "3) Exit\n";
            int opt = readInt("Choose: ");
            if (opt == 1)
            {
                std::string username = readLine("Username: ");
                std::string password = readLine("Password: ");
                try
                {
                    currentUserId = auth.login(username, password);
                    Logger::log("Main", Logger::Level::INFO, "User logged in: " + username);
                }
                catch (const std::exception &e)
                {
                    std::cout << "Login failed: " << e.what() << "\n";
                }
            }
            else if (opt == 2)
            {
                std::string name = readLine("Full name: ");
                std::string email = readLine("Email: ");
                std::string username = readLine("Choose username: ");
                std::string password = readLine("Choose password: ");
                std::cout << "Role: 1) Student 2) Teacher 3) Admin\n";
                int r = readInt("Choose role: ");
                Role role = Role::STUDENT;
                if (r == 2)
                    role = Role::TEACHER;
                else if (r == 3)
                    role = Role::ADMIN;
                try
                {
                    int id = auth.registerUser(name, email, username, password, role);
                    std::cout << "Registered with id=" << id << "\n";
                }
                catch (const std::exception &e)
                {
                    std::cout << "Register failed: " << e.what() << "\n";
                }
            }
            else if (opt == 3)
            {
                break;
            }
            else
            {
                std::cout << "Invalid choice\n";
            }
        }
        else
        {

            auto user = auth.getUserById(currentUserId);
            if (!user)
            {
                std::cout << "Internal error: user not found. Logging out.\n";
                currentUserId = -1;
                continue;
            }

            bool isStudent = (user->getRole() == Role::STUDENT);
            bool isTeacher = (user->getRole() == Role::TEACHER);
            bool isAdmin = (user->getRole() == Role::ADMIN);

            int changePasswordChoice = 3;
            int nextChoice = 4;

            int studentEnrollChoice = -1;
            int studentDropChoice = -1;

            int teacherMyCoursesChoice = -1;
            int teacherStudentsChoice = -1;

            int adminAddChoice = -1;
            int adminUpdateChoice = -1;
            int adminDeleteChoice = -1;
            int adminAssignChoice = -1;

            std::cout << "\n==== Main Menu (" << user->getUsername() << ") ====\n";
            std::cout << "1) View profile\n";
            std::cout << "2) List all courses\n";
            std::cout << changePasswordChoice << ") Change password\n";

            if (isStudent)
            {
                studentEnrollChoice = nextChoice++;
                studentDropChoice = nextChoice++;
                std::cout << studentEnrollChoice << ") Enroll in course\n";
                std::cout << studentDropChoice << ") Drop course\n";
            }

            if (isTeacher)
            {
                teacherMyCoursesChoice = nextChoice++;
                teacherStudentsChoice = nextChoice++;
                std::cout << teacherMyCoursesChoice << ") My courses\n";
                std::cout << teacherStudentsChoice << ") View students in my course\n";
            }

            if (isAdmin)
            {
                adminAddChoice = nextChoice++;
                adminUpdateChoice = nextChoice++;
                adminDeleteChoice = nextChoice++;
                adminAssignChoice = nextChoice++;
                std::cout << adminAddChoice << ") Add course\n";
                std::cout << adminUpdateChoice << ") Update course\n";
                std::cout << adminDeleteChoice << ") Delete course\n";
                std::cout << adminAssignChoice << ") Assign teacher to course\n";
            }

            std::cout << "0) Logout\n";
            int choice = readInt("Choose: ");

            if (choice == 1)
            {
                user->printProfile();
                pause();
            }
            else if (choice == 2)
            {
                auto list = cm.listAllCourses();
                std::cout << "Courses:\n";
                for (auto &c : list)
                {
                    std::cout << c->getId() << ") " << c->getTitle()
                              << " (credits:" << c->getCredits()
                              << " cap:" << c->getCapacity()
                              << " teacherId:" << c->getTeacherId()
                              << " enrolled:" << c->getEnrolledStudents().size()
                              << ")\n";
                }
                pause();
            }
            else if (choice == changePasswordChoice)
            {
                std::string newPass = readLine("Enter new password: ");
                try
                {
                    auth.changePassword(currentUserId, newPass);
                    std::cout << "Password changed successfully.\n";
                    Logger::log("Main", Logger::Level::INFO,
                                "Password changed for user " + user->getUsername());
                }
                catch (const std::exception &e)
                {
                    std::cout << "Failed to change password: " << e.what() << "\n";
                }
                pause();
            }
            else if (isStudent && choice == studentEnrollChoice)
            {
                int courseId = readInt("Course ID to enroll: ");
                bool ok = cm.enrollStudent(courseId, currentUserId);
                if (ok)
                    std::cout << "Enrolled successfully\n";
                else
                    std::cout << "Enroll failed (course full or already enrolled?)\n";
                pause();
            }
            else if (isStudent && choice == studentDropChoice)
            {
                int courseId = readInt("Course ID to drop: ");
                bool ok = cm.dropStudent(courseId, currentUserId);
                if (ok)
                    std::cout << "Dropped successfully\n";
                else
                    std::cout << "Drop failed (not enrolled?)\n";
                pause();
            }
            else if (isTeacher && choice == teacherMyCoursesChoice)
            {
                auto my = cm.listCoursesByTeacher(currentUserId);
                if (my.empty())
                {
                    std::cout << "You are not assigned to any courses.\n";
                }
                else
                {
                    std::cout << "Your courses:\n";
                    for (auto &c : my)
                    {
                        std::cout << c->getId() << ") " << c->getTitle()
                                  << " (credits:" << c->getCredits()
                                  << " cap:" << c->getCapacity()
                                  << " enrolled:" << c->getEnrolledStudents().size()
                                  << ")\n";
                    }
                }
                pause();
            }
            else if (isTeacher && choice == teacherStudentsChoice)
            {
                int courseId = readInt("Course ID: ");
                auto c = cm.getCourseById(courseId);
                if (!c || c->getTeacherId() != currentUserId)
                {
                    std::cout << "You are not assigned to this course or course does not exist.\n";
                }
                else
                {
                    const auto &st = c->getEnrolledStudents();
                    if (st.empty())
                    {
                        std::cout << "No students enrolled in this course.\n";
                    }
                    else
                    {
                        std::cout << "Students enrolled (IDs): ";
                        for (int sid : st)
                            std::cout << sid << " ";
                        std::cout << "\n";
                    }
                }
                pause();
            }
            else if (isAdmin && choice == adminAddChoice)
            {
                std::string title = readLine("Course title: ");
                int credits = readInt("Credits: ");
                int cap = readInt("Capacity: ");
                int id = cm.addCourse(title, credits, cap);
                std::cout << "Added course id=" << id << "\n";
                pause();
            }
            else if (isAdmin && choice == adminUpdateChoice)
            {
                int id = readInt("Course id to update: ");
                std::string title = readLine("New title: ");
                int credits = readInt("New credits: ");
                int cap = readInt("New capacity: ");
                if (cm.updateCourse(id, title, credits, cap))
                    std::cout << "Updated\n";
                else
                    std::cout << "Update failed (id invalid)\n";
                pause();
            }
            else if (isAdmin && choice == adminDeleteChoice)
            {
                int id = readInt("Course id to delete: ");
                if (cm.deleteCourse(id))
                    std::cout << "Deleted\n";
                else
                    std::cout << "Delete failed\n";
                pause();
            }
            else if (isAdmin && choice == adminAssignChoice)
            {
                int courseId = readInt("Course id: ");
                int teacherId = readInt("Teacher user id (-1 to unassign): ");
                bool ok;
                if (teacherId == -1)
                {
                    ok = cm.unassignTeacher(courseId);
                }
                else
                {
                    ok = cm.assignTeacher(courseId, teacherId);
                }
                if (ok)
                    std::cout << "Assignment updated.\n";
                else
                    std::cout << "Assignment failed (course id invalid?)\n";
                pause();
            }
            else if (choice == 0)
            {
                Logger::log("Main", Logger::Level::INFO,
                            "User logged out: " + user->getUsername());
                currentUserId = -1;
            }
            else
            {
                std::cout << "Invalid choice\n";
            }
        }
    }

    Logger::log("System", Logger::Level::INFO, "Application shutting down");
    Logger::close();
    return 0;
}
