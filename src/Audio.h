#pragma once
#include "LibraryItem.h"

class Audio : public LibraryItem {
public:
    Audio(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber);
};
