#include "../include/Admin.h"
#include <iostream>
using namespace std;

Admin::Admin(int id, const string &name, const string &email,
             const string &username, const string &passwordHash)
    : User(id, name, email, username, passwordHash, /*salt*/ string(), Role::ADMIN) {}

void Admin::printProfile() const {
    cout << "Admin Profile\n";
    cout << "ID: " << getId() << "\n";
    cout << "Name: " << getName() << "\n";
    cout << "Email: " << getEmail() << "\n";
    cout << "Username: " << getUsername() << "\n";
    cout << "Privileges: full\n";
}

void Admin::createCoursePlaceholder() const {
    cout << "(admin) createCourse called - implement CourseManager integration later\n";
}
