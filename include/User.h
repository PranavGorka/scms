#pragma once
#include "../include/Person.h"
#include <string>
using namespace std;

enum class Role { STUDENT, TEACHER, ADMIN, UNKNOWN };

class User : public Person {
public:
    User() = default;
    User(int id, const string &name, const string &email,
         const string &username, const string &passwordHash,
         const string &salt, Role role = Role::UNKNOWN);

    virtual ~User() = default;

    void printProfile() const override;

    // Username
    string getUsername() const;
    void setUsername(const string &username_);

    // Password hash + salt
    string getPasswordHash() const;
    void setPasswordHash(const string &hash_);

    string getSalt() const;
    void setSalt(const string &salt_);

    // Role
    Role getRole() const;
    void setRole(Role r);

private:
    string username;
    string passwordHash; 
    string salt;
    Role role{Role::UNKNOWN};
};
