#include "../include/Book.h"
#include <stdexcept>

Book::Book(int id, const std::string &title,
           const std::string &author, int copies)
    : id(id), title(title), author(author), copies(copies) {}

int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
int Book::getCopies() const { return copies; }

void Book::setCopies(int c) { copies = c; }

void Book::decrementCopy()
{
    if (copies <= 0)
        throw std::runtime_error("No copies available");
    copies--;
}

void Book::incrementCopy()
{
    copies++;
}
