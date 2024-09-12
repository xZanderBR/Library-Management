#pragma once
#include "Genre.h"
#include <string>

class LibraryItem {
public:
    LibraryItem(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber);
    virtual ~LibraryItem() = default;

    std::string getTitle() const;
    std::string getAuthors() const;
    Genre getGenre() const;
    std::string getCopyrightDate() const;
    std::string getISBN() const;
    int getCopyNumber() const;
    bool isCheckedOut() const;

    void checkOut();
    void returnItem();
    bool isValidDate(const std::string& date) const;

protected:
    bool isValidISBN(const std::string& isbn) const;

private:
    std::string title;
    std::string authors;
    Genre genre;
    std::string copyrightDate;
    std::string isbn;
    int copyNumber;
    bool checkedOut;
};
