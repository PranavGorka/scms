#pragma once
#include <string>
#include <unordered_map>
#include "../include/User.h"
#include <optional>
#include <memory>
#include <stdexcept>
using namespace std;

class AuthException : public runtime_error {
public:
    explicit AuthException(const string &msg) : runtime_error(msg) {}
};

class AuthManager {
public:
    AuthManager(const string &dataFile = "data/users.csv");
    ~AuthManager();

    void load();   
    void save();  

    int registerUser(const string &name,
                     const string &email,
                     const string &username,
                     const string &password,
                     Role role = Role::STUDENT);

    int login(const string &username, const string &password);

    void changePassword(int userId, const string &newPassword);

    shared_ptr<User> getUserById(int userId) const;
    shared_ptr<User> getUserByUsername(const string &username) const;

private:
    string dataFilePath;
    int nextId{1001};

    unordered_map<int, shared_ptr<User>> usersById;
    unordered_map<string, int> idByUsername;

    void ensureDataDirExists();
};
