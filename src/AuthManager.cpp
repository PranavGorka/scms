#include "../include/Logger.h"
#include "../include/AuthManager.h"
#include "../include/utils.h"
#include <fstream>
#include <sstream>
#include <filesystem>
using namespace std;

AuthManager::AuthManager(const string &dataFile) : dataFilePath(dataFile)
{
    ensureDataDirExists();
    load();
}

AuthManager::~AuthManager()
{
    save();
}

void AuthManager::ensureDataDirExists()
{
    try
    {
        filesystem::path p = filesystem::path(dataFilePath).parent_path();
        if (!p.empty() && !filesystem::exists(p))
        {
            filesystem::create_directories(p);
        }
    }
    catch (...)
    {
    }
}

void AuthManager::load()
{
    usersById.clear();
    idByUsername.clear();

    ifstream ifs(dataFilePath);
    if (!ifs.is_open())
    {
        Logger::log("AuthManager", Logger::Level::INFO, "No users file found; starting fresh.");
        return;
    }

    string line;
    bool firstLine = true;
    while (getline(ifs, line))
    {
        if (line.empty())
            continue;
        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        istringstream iss(line);
        string id_s, username, hash, salt, role_s, name, email;

        getline(iss, id_s, ',');
        getline(iss, username, ',');
        getline(iss, hash, ',');
        getline(iss, salt, ',');
        getline(iss, role_s, ',');
        getline(iss, name, ',');
        getline(iss, email, ',');

        int id = stoi(id_s);

        Role role = Role::UNKNOWN;
        if (role_s == "STUDENT")
            role = Role::STUDENT;
        else if (role_s == "TEACHER")
            role = Role::TEACHER;
        else if (role_s == "ADMIN")
            role = Role::ADMIN;

        auto userPtr = make_shared<User>(id, name, email, username, hash, salt, role);

        usersById[id] = userPtr;
        idByUsername[username] = id;

        if (id >= nextId)
            nextId = id + 1;
    }

    Logger::log("AuthManager", Logger::Level::INFO, "Loaded users from " + dataFilePath);
}

void AuthManager::save()
{
    ofstream ofs(dataFilePath, ios::trunc);
    if (!ofs.is_open())
    {
        Logger::log("AuthManager", Logger::Level::ERROR, "Failed to write users file.");
        return;
    }

    ofs << "id,username,passwordHash,salt,role,name,email\n";

    for (auto &p : usersById)
    {
        auto u = p.second;
        string roleStr = "UNKNOWN";
        switch (u->getRole())
        {
        case Role::STUDENT:
            roleStr = "STUDENT";
            break;
        case Role::TEACHER:
            roleStr = "TEACHER";
            break;
        case Role::ADMIN:
            roleStr = "ADMIN";
            break;
        }

        ofs << u->getId() << ","
            << u->getUsername() << ","
            << u->getPasswordHash() << ","
            << u->getSalt() << ","
            << roleStr << ","
            << u->getName() << ","
            << u->getEmail() << "\n";
    }

    Logger::log("AuthManager", Logger::Level::INFO, "Saved users to " + dataFilePath);
}

int AuthManager::registerUser(const string &name,
                              const string &email,
                              const string &username,
                              const string &password,
                              Role role)
{
    if (idByUsername.count(username))
    {
        throw AuthException("Username already exists");
    }

    int id = nextId++;
    string salt = utils::makeSalt();
    string hash = utils::hashPassword(password, salt);

    auto userPtr = make_shared<User>(
        id, name, email, username, hash, salt, role);

    usersById[id] = userPtr;
    idByUsername[username] = id;

    Logger::log("AuthManager", Logger::Level::INFO,
                "Registered user '" + username + "' (id " + to_string(id) + ")");

    save();
    return id;
}

int AuthManager::login(const string &username, const string &password)
{
    if (!idByUsername.count(username))
    {
        Logger::log("AuthManager", Logger::Level::WARN,
                    "Login failed (no username): " + username);
        throw AuthException("Invalid username or password");
    }

    int id = idByUsername.at(username);
    auto u = usersById.at(id);

    // compute attempt hash using user’s stored salt
    string attemptHash = utils::hashPassword(password, u->getSalt());

    if (attemptHash != u->getPasswordHash())
    {
        Logger::log("AuthManager", Logger::Level::WARN,
                    "Login failed (bad password): " + username);
        throw AuthException("Invalid username or password");
    }

    Logger::log("AuthManager", Logger::Level::INFO, "Login success for " + username);
    return id;
}

void AuthManager::changePassword(int userId, const string &newPassword)
{
    auto it = usersById.find(userId);
    if (it == usersById.end())
        throw AuthException("User not found");

    string salt = utils::makeSalt();
    string hash = utils::hashPassword(newPassword, salt);

    it->second->setPasswordHash(hash);
    it->second->setSalt(salt);

    Logger::log("AuthManager", Logger::Level::INFO,
                "Password changed for userId=" + to_string(userId));

    save();
}

shared_ptr<User> AuthManager::getUserById(int userId) const
{
    auto it = usersById.find(userId);
    if (it == usersById.end())
        return nullptr;
    return it->second;
}

shared_ptr<User> AuthManager::getUserByUsername(const string &username) const
{
    auto it = idByUsername.find(username);
    if (it == idByUsername.end())
        return nullptr;
    return getUserById(it->second);
}
