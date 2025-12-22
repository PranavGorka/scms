#pragma once
#include <string>

class Book
{
public:
    Book() = default;
    Book(int id, const std::string &title,
         const std::string &author, int copies);

    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    int getCopies() const;

    void setCopies(int c);
    void decrementCopy();
    void incrementCopy();

private:
    int id{0};
    std::string title;
    std::string author;
    int copies{0};
};
