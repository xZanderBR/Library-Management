#include "LibraryItem.h"
#include <regex>
#include <stdexcept>

LibraryItem::LibraryItem(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber)
    : title(title), authors(authors), genre(genre), copyrightDate(copyrightDate), isbn(isbn), copyNumber(copyNumber), checkedOut(false) {
    if (!isValidISBN(isbn)) throw std::invalid_argument("Invalid ISBN format.");
    if (!isValidDate(copyrightDate)) throw std::invalid_argument("Invalid Date format.");
}

bool LibraryItem::isValidISBN(const std::string& isbn) const {
    std::regex isbnRegex(R"(\d+-\d+-\d+-[a-zA-Z0-9])");
    return std::regex_match(isbn, isbnRegex);
}

bool LibraryItem::isValidDate(const std::string& date) const {
    std::regex dateFormat(R"(^((0[1-9])|(1[0-2]))/((0[1-9])|([12][0-9])|(3[01]))/\d{4}$)");
    return std::regex_match(date, dateFormat);
}

std::string LibraryItem::getTitle() const { return title; }
std::string LibraryItem::getAuthors() const { return authors; }
Genre LibraryItem::getGenre() const { return genre; }
std::string LibraryItem::getCopyrightDate() const { return copyrightDate; }
std::string LibraryItem::getISBN() const { return isbn; }
int LibraryItem::getCopyNumber() const { return copyNumber; }
bool LibraryItem::isCheckedOut() const { return checkedOut; }

void LibraryItem::checkOut() { checkedOut = true; }
void LibraryItem::returnItem() { checkedOut = false; }
