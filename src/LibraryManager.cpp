#include "../include/LibraryManager.h"
#include "../include/Logger.h"
#include <fstream>
#include <iostream>
#include <filesystem>

LibraryManager::LibraryManager(const std::string &file,
                               const std::string &logFile)
    : dataFile(file), transactionLog(logFile)
{
    std::filesystem::create_directories("data");
    std::filesystem::create_directories("logs");
    load();
}

void LibraryManager::load()
{
    books.clear();
    std::ifstream in(dataFile, std::ios::binary);
    if (!in.is_open())
        return;

    int id, copies;
    std::string title, author;

    while (in >> id >> title >> author >> copies)
    {
        books[id] = Book(id, title, author, copies);
        if (id >= nextBookId)
            nextBookId = id + 1;
    }
}

void LibraryManager::save() const
{
    std::ofstream out(dataFile, std::ios::binary | std::ios::trunc);
    for (const auto &p : books)
    {
        const Book &b = p.second;
        out << b.getId() << " "
            << b.getTitle() << " "
            << b.getAuthor() << " "
            << b.getCopies() << "\n";
    }
}

void LibraryManager::logTransaction(const std::string &msg) const
{
    std::ofstream out(transactionLog, std::ios::app);
    out << msg << "\n";
}

void LibraryManager::addBook(const std::string &title,
                             const std::string &author,
                             int copies)
{
    Book b(nextBookId++, title, author, copies);
    books[b.getId()] = b;
    save();

    Logger::log("LibraryManager", Logger::Level::INFO,
                "Added book: " + title);
}

void LibraryManager::issueBook(int bookId, int studentId)
{
    if (!books.count(bookId))
        throw std::runtime_error("Book not found");

    books[bookId].decrementCopy();
    save();

    std::string msg = "Issued book " + std::to_string(bookId) +
                      " to student " + std::to_string(studentId);
    logTransaction(msg);
    Logger::log("LibraryManager", Logger::Level::INFO, msg);
}

void LibraryManager::returnBook(int bookId, int studentId)
{
    if (!books.count(bookId))
        throw std::runtime_error("Book not found");

    books[bookId].incrementCopy();
    save();

    std::string msg = "Returned book " + std::to_string(bookId) +
                      " from student " + std::to_string(studentId);
    logTransaction(msg);
    Logger::log("LibraryManager", Logger::Level::INFO, msg);
}

void LibraryManager::listBooks() const
{
    std::cout << "\nAvailable Books:\n";
    for (const auto &p : books)
    {
        const Book &b = p.second;
        std::cout << b.getId() << ") "
                  << b.getTitle() << " by "
                  << b.getAuthor()
                  << " (copies: " << b.getCopies() << ")\n";
    }
}
