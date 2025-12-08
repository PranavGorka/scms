#include "../include/CourseManager.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;

CourseManager::CourseManager(const string &file) : filepath(file)
{
    filesystem::create_directories("data");
    load();
}

CourseManager::~CourseManager()
{
    save();
}

void CourseManager::load()
{
    courses.clear();

    std::ifstream in(filepath);
    if (!in.is_open())
    {
        Logger::log("CourseManager", Logger::Level::INFO, "No course file found, starting empty.");
        return;
    }

    std::string line;
    bool skipHeader = true;
    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        if (skipHeader)
        {
            skipHeader = false;
            continue;
        }

        std::istringstream ss(line);
        std::vector<std::string> parts;
        std::string tok;
        while (std::getline(ss, tok, ','))
        {
            parts.push_back(tok);
        }
        if (parts.size() < 5)
            continue;

        int id = std::stoi(parts[0]);
        std::string title = parts[1];
        int credits = std::stoi(parts[2]);
        int capacity = std::stoi(parts[3]);

        int teacherId = -1;
        std::string enrolledStr;

        if (parts.size() == 5)
        {

            enrolledStr = parts[4];
        }
        else
        {

            teacherId = std::stoi(parts[4]);
            enrolledStr = parts[5];
        }

        auto course = std::make_shared<Course>(id, title, credits, capacity, teacherId);

        std::stringstream es(enrolledStr);
        std::string st;
        while (std::getline(es, st, ';'))
        {
            if (!st.empty())
            {

                course->enrollStudent(std::stoi(st));
            }
        }

        courses[id] = course;
        if (id >= nextId)
            nextId = id + 1;
    }

    Logger::log("CourseManager", Logger::Level::INFO, "Loaded courses.");
}

void CourseManager::save()
{
    std::ofstream out(filepath, std::ios::trunc);
    if (!out.is_open())
    {
        Logger::log("CourseManager", Logger::Level::ERROR, "Cannot write courses file!");
        return;
    }

    out << "id,title,credits,capacity,teacherId,enrolled\n";
    for (auto &[id, cptr] : courses)
    {
        out << id << ","
            << cptr->getTitle() << ","
            << cptr->getCredits() << ","
            << cptr->getCapacity() << ","
            << cptr->getTeacherId() << ",";

        const auto &vec = cptr->getEnrolledStudents();
        for (size_t i = 0; i < vec.size(); ++i)
        {
            out << vec[i];
            if (i + 1 < vec.size())
                out << ";";
        }
        out << "\n";
    }
}

int CourseManager::addCourse(const string &title, int credits, int capacity)
{
    int id = nextId++;
    auto ptr = make_shared<Course>(id, title, credits, capacity);
    courses[id] = ptr;

    Logger::log("CourseManager", Logger::Level::INFO,
                "Added course id=" + to_string(id));

    save();
    return id;
}

bool CourseManager::updateCourse(int courseId, const string &newTitle, int newCredits, int newCapacity)
{
    auto c = getCourseById(courseId);
    if (!c)
        return false;

    c->setTitle(newTitle);
    c->setCredits(newCredits);
    c->setCapacity(newCapacity);

    Logger::log("CourseManager", Logger::Level::INFO,
                "Updated course id=" + to_string(courseId));

    save();
    return true;
}

bool CourseManager::deleteCourse(int courseId)
{
    if (courses.erase(courseId) == 0)
        return false;

    Logger::log("CourseManager", Logger::Level::INFO,
                "Deleted course id=" + to_string(courseId));

    save();
    return true;
}

bool CourseManager::enrollStudent(int courseId, int studentId)
{
    auto c = getCourseById(courseId);
    if (!c)
        return false;

    bool ok = c->enrollStudent(studentId);
    if (ok)
    {
        Logger::log("CourseManager", Logger::Level::INFO,
                    "Enrolled student " + to_string(studentId) +
                        " in course " + to_string(courseId));
        save();
    }
    return ok;
}

bool CourseManager::dropStudent(int courseId, int studentId)
{
    auto c = getCourseById(courseId);
    if (!c)
        return false;

    bool ok = c->dropStudent(studentId);
    if (ok)
    {
        Logger::log("CourseManager", Logger::Level::INFO,
                    "Dropped student " + to_string(studentId) +
                        " from course " + to_string(courseId));
        save();
    }
    return ok;
}

std::shared_ptr<Course> CourseManager::getCourseById(int id) const
{
    auto it = courses.find(id);
    if (it == courses.end())
        return nullptr;
    return it->second;
}

std::vector<std::shared_ptr<Course>> CourseManager::listAllCourses() const
{
    std::vector<std::shared_ptr<Course>> v;
    for (auto &p : courses)
        v.push_back(p.second);
    return v;
}

bool CourseManager::assignTeacher(int courseId, int teacherUserId)
{
    auto c = getCourseById(courseId);
    if (!c)
        return false;
    c->setTeacherId(teacherUserId);
    Logger::log("CourseManager", Logger::Level::INFO,
                "Assigned teacher " + std::to_string(teacherUserId) +
                    " to course " + std::to_string(courseId));
    save();
    return true;
}

bool CourseManager::unassignTeacher(int courseId)
{
    auto c = getCourseById(courseId);
    if (!c)
        return false;
    c->setTeacherId(-1);
    Logger::log("CourseManager", Logger::Level::INFO,
                "Unassigned teacher from course " + std::to_string(courseId));
    save();
    return true;
}

std::vector<std::shared_ptr<Course>> CourseManager::listCoursesByTeacher(int teacherUserId) const
{
    std::vector<std::shared_ptr<Course>> v;
    for (auto &p : courses)
    {
        if (p.second->getTeacherId() == teacherUserId)
        {
            v.push_back(p.second);
        }
    }
    return v;
}
