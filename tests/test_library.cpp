// Simple main-based tests for LibraryManager & Book
// Steps: add book, issue book, no-copies exception, return book

#include <iostream>
#include <filesystem>
#include <stdexcept>
#include "LibraryManager.h"

int main()
{
    using std::cout;
    using std::endl;

    const std::string testData = "data/books_test.dat";
    const std::string testLog = "logs/transaction_test.log";

    // Clean previous test artifacts
    try
    {
        std::filesystem::remove(testData);
    }
    catch (...)
    {
    }
    try
    {
        std::filesystem::remove(testLog);
    }
    catch (...)
    {
    }

    LibraryManager lm(testData, testLog);

    bool ok = true;

    // 1) Add book (1 copy)
    try
    {
        lm.addBook("Dune", "Herbert", 1);
        cout << "[Library] Add book: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Library] Add book: FAIL - " << e.what() << "\n";
    }

    // Since we cleared data, first book id should be 3001
    int bookId = 3001;

    // 2) Issue book (should succeed)
    try
    {
        lm.issueBook(bookId, 4001);
        cout << "[Library] Issue book: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Library] Issue book: FAIL - " << e.what() << "\n";
    }

    // 3) Issue again (no copies -> exception)
    try
    {
        lm.issueBook(bookId, 4002);
        ok = false;
        cout << "[Library] No-copies exception: FAIL - second issue succeeded\n";
    }
    catch (const std::runtime_error &)
    {
        cout << "[Library] No-copies exception: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Library] No-copies exception: FAIL - " << e.what() << "\n";
    }

    // 4) Return book, then issue again (should succeed now)
    try
    {
        lm.returnBook(bookId, 4001);
        lm.issueBook(bookId, 4003);
        cout << "[Library] Return then issue again: PASS\n";
    }
    catch (const std::exception &e)
    {
        ok = false;
        cout << "[Library] Return/issue: FAIL - " << e.what() << "\n";
    }

    cout << (ok ? "OVERALL: PASS\n" : "OVERALL: FAIL\n");
    return ok ? 0 : 1;
}
