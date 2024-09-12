#pragma once
#include <string>

enum class Genre { Fiction, NonFiction, Mystery, SciFi, Biography };

std::string genreToString(Genre genre);
