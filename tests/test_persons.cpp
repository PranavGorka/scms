#include <iostream>
#include "AuthManager.h"
#include "Logger.h"

int main() {
    Logger::init("logs/scms.log");
    AuthManager am("data/users.csv");

    try {
        int id = am.registerUser("Alice Student", "alice@uni.edu", "alice", "alicepass", Role::STUDENT);
        std::cout << "Registered alice id=" << id << "\n";
    } catch (const std::exception &e) {
        std::cout << "Register: " << e.what() << "\n";
    }

    try {
        int id = am.login("alice", "alicepass");
        std::cout << "Login success alice id=" << id << "\n";
        am.changePassword(id, "newpass");
        std::cout << "Password changed\n";
        // test login with old password -> should throw
        try {
            am.login("alice", "alicepass");
        } catch (...) {
            std::cout << "Old password rejected\n";
        }
        // login with new password
        int id2 = am.login("alice", "newpass");
        std::cout << "Login success with new password id=" << id2 << "\n";
    } catch (const std::exception &e) {
        std::cout << "Login: " << e.what() << "\n";
    }

    Logger::close();
    return 0;
}
