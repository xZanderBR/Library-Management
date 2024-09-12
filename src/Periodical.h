#pragma once
#include "LibraryItem.h"

class Periodical : public LibraryItem {
public:
    Periodical(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber);
};
