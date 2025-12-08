#pragma once
#include "User.h"
using namespace std;

class Admin : public User {
public:
    Admin() = default;
    Admin(int id, const string &name, const string &email,
          const string &username, const string &passwordHash);

    void printProfile() const override;

    
    void createCoursePlaceholder() const;
};
