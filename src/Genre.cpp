#include <Genre.h>

// Function to convert Genre to string
std::string genreToString(Genre genre) {
    switch (genre) {
        case Genre::Fiction: return "Fiction";
        case Genre::NonFiction: return "Non-Fiction";
        case Genre::Mystery: return "Mystery";
        case Genre::SciFi: return "Sci-Fi";
        case Genre::Biography: return "Biography";
        default: return "Unknown";
    }
}