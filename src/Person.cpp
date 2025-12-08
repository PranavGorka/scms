#include "../include/Person.h"
#include <iostream>
using namespace std;

Person::Person(int id, const string &name, const string &email)
    : id(id), name(name), email(email) {}

int Person::getId() const { return id; }
void Person::setId(int id_) { id = id_; }

string Person::getName() const { return name; }
void Person::setName(const string &name_) { name = name_; }

string Person::getEmail() const { return email; }
void Person::setEmail(const string &email_) { email = email_; }
  