#pragma once
#include "LibraryItem.h"

class Book : public LibraryItem {
public:
    Book(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber);
};
