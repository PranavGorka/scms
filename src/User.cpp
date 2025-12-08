#include "../include/User.h"
#include <iostream>
using namespace std;

User::User(int id, const string &name, const string &email,
           const string &username, const string &passwordHash,
           const string &salt, Role role)
    : Person(id, name, email),
      username(username),
      passwordHash(passwordHash),
      salt(salt),
      role(role) {}

void User::printProfile() const {
    cout << "User Profile\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Email: " << email << "\n";
    cout << "Username: " << username << "\n";
    cout << "Role: ";
    switch(role) {
        case Role::STUDENT: cout << "STUDENT\n"; break;
        case Role::TEACHER: cout << "TEACHER\n"; break;
        case Role::ADMIN:   cout << "ADMIN\n"; break;
        default: cout << "UNKNOWN\n"; break;
    }
}

string User::getUsername() const { return username; }
void User::setUsername(const string &username_) { username = username_; }

string User::getPasswordHash() const { return passwordHash; }
void User::setPasswordHash(const string &hash_) { passwordHash = hash_; }

string User::getSalt() const { return salt; }
void User::setSalt(const string &salt_) { salt = salt_; }

Role User::getRole() const { return role; }
void User::setRole(Role r) { role = r; }
