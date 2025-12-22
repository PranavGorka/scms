#pragma once
#include <unordered_map>
#include <string>
#include "Book.h"

class LibraryManager
{
public:
    LibraryManager(const std::string &file = "data/books.dat",
                   const std::string &logFile = "logs/transaction.log");

    void addBook(const std::string &title,
                 const std::string &author,
                 int copies);

    void issueBook(int bookId, int studentId);
    void returnBook(int bookId, int studentId);

    void listBooks() const;

private:
    std::string dataFile;
    std::string transactionLog;
    int nextBookId{3001};

    std::unordered_map<int, Book> books;

    void load();
    void save() const;
    void logTransaction(const std::string &msg) const;
};
