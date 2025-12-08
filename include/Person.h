#pragma once
#include <string>
using namespace std;

class Person {
public:
    Person() = default;
    Person(int id, const string &name, const string &email);
    virtual ~Person() = default;

    virtual void printProfile() const = 0;

    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string &name);

    string getEmail() const;
    void setEmail(const string &email);

protected:
    int id{0};
    string name;
    string email;
};
