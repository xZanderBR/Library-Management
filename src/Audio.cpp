#include "Audio.h"

Audio::Audio(const std::string& title, const std::string& authors, Genre genre, const std::string& copyrightDate, const std::string& isbn, int copyNumber)
    : LibraryItem(title, authors, genre, copyrightDate, isbn, copyNumber) {}
