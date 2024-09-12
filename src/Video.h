#pragma once
#include "LibraryItem.h"

class Video : public LibraryItem {
public:
    Video(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber);
};
