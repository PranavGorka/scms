// Simple main-based tests for AuthManager
// Each step prints PASS/FAIL with a brief description

#include <iostream>
#include <filesystem>
#include "AuthManager.h"

int main()
{
    using std::cout;
    using std::endl;

    const std::string testUsers = "data/test_users.csv";

    // Clean previous test data if any
    try
    {
        std::filesystem::remove(testUsers);
    }
    catch (...)
    {
    }

    AuthManager auth(testUsers);

    bool ok = true;

    // 1) Register user
    int uid = -1;
    try
    {
        uid = auth.registerUser("Test User", "test@scms.local", "test_user", "secret", Role::STUDENT);
        cout << "[Auth] Register user: PASS (id=" << uid << ")\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Auth] Register user: FAIL - " << e.what() << "\n";
    }

    // 2) Login success
    try
    {
        int id = auth.login("test_user", "secret");
        cout << "[Auth] Login success: PASS (id=" << id << ")\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Auth] Login success: FAIL - " << e.what() << "\n";
    }

    // 3) Login failure (wrong password)
    try
    {
        (void)auth.login("test_user", "wrongpass");
        ok = false;
        cout << "[Auth] Login failure (expected exception): FAIL - accepted wrong password\n";
    }
    catch (const std::exception &)
    {
        cout << "[Auth] Login failure (wrong password): PASS\n";
    }

    // 4) Change password and re-login
    try
    {
        auth.changePassword(uid, "newsecret");
        // old password should fail
        bool oldRejected = false;
        try
        {
            (void)auth.login("test_user", "secret");
        }
        catch (...)
        {
            oldRejected = true;
        }

        // new password should succeed
        int id2 = auth.login("test_user", "newsecret");
        if (!oldRejected)
        {
            ok = false;
            cout << "[Auth] Change password (old rejected): FAIL\n";
        }
        else
        {
            cout << "[Auth] Change password (old rejected): PASS\n";
        }
        cout << "[Auth] Re-login with new password: PASS (id=" << id2 << ")\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Auth] Change password / re-login: FAIL - " << e.what() << "\n";
    }

    cout << (ok ? "OVERALL: PASS\n" : "OVERALL: FAIL\n");
    return ok ? 0 : 1;
}
