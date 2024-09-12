#include "Utility.h"
#include "Periodical.h"
#include "Book.h"
#include "Audio.h"
#include "Video.h"
#include <algorithm>

#include <iostream>

void showHelp() {
    std::cout << "Usage: library_manager -L <library_collection_file> -P <patron_file> [-h]\n"
              << "  -h   Show this text and exit. Optional.\n\n"
              << "  -L   Required. File name containing Library collection.\n"
              << "       If no file is specified, the program will exit.\n\n"
              << "  -P   Required. File name containing Library patrons.\n"
              << "       If no file is specified, the program will exit.\n";
}

void displayMenu() {
    std::cout << "\nLibrary Management System\n";
    std::cout << "1. Add items to the library collection\n";
    std::cout << "2. Add new library patrons\n";
    std::cout << "3. Checkout item\n";
    std::cout << "4. Return item\n";
    std::cout << "5. Print reports\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
}

void printReportMenu() {
    std::cout << "\nPrint Reports\n";
    std::cout << "1. Users who owe fees\n";
    std::cout << "2. Items on the waitlist\n";
    std::cout << "3. Patrons on the waitlist\n";
    std::cout << "4. Return to main menu\n";
    std::cout << "Enter your choice: ";
}

void addLibraryItem(Library& library) {
    std::string type, title, authors, genreStr, copyrightDate, isbn;
    int copyNumber;
    std::cout << "Enter item type (Book, Periodical, Audio, Video): ";
    std::cin >> type;
    std::cin.ignore();
    std::cout << "Enter title: ";
    std::getline(std::cin, title);
    std::cout << "Enter authors: ";
    std::getline(std::cin, authors);
    std::cout << "Enter genre (Fiction, Non-Fiction, Mystery, Sci-Fi, Biography): ";
    std::getline(std::cin, genreStr);
    std::cout << "Enter copyright date (mm/dd/yyyy): ";
    std::getline(std::cin, copyrightDate);
    std::cout << "Enter ISBN (n-n-n-x): ";
    std::getline(std::cin, isbn);
    std::cout << "Enter copy number: ";
    std::cin >> copyNumber;

    Genre genre;
    if (genreStr == "Fiction") genre = Genre::Fiction;
    else if (genreStr == "Non-Fiction") genre = Genre::NonFiction;
    else if (genreStr == "Mystery") genre = Genre::Mystery;
    else if (genreStr == "Sci-Fi") genre = Genre::SciFi;
    else if (genreStr == "Biography") genre = Genre::Biography;
    else {
        std::cerr << "Invalid genre entered.\n";
        return;
    }

    std::unique_ptr<LibraryItem> item;
    if (type == "Book") item = std::unique_ptr<LibraryItem>(new Book(title, authors, genre, copyrightDate, isbn, copyNumber));
    else if (type == "Periodical") item = std::unique_ptr<LibraryItem>(new Periodical(title, authors, genre, copyrightDate, isbn, copyNumber));
    else if (type == "Audio") item = std::unique_ptr<LibraryItem>(new Audio(title, authors, genre, copyrightDate, isbn, copyNumber));
    else if (type == "Video") item = std::unique_ptr<LibraryItem>(new Video(title, authors, genre, copyrightDate, isbn, copyNumber));
    else {
        std::cerr << "Invalid item type entered.\n";
        return;
    }

    library.addItem(std::move(item));
    std::cout << "Item added successfully.\n";
}

void addLibraryPatron(Library& library) {
    std::string name;
    std::string memberId;
    std::cout << "Enter patron name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter member ID: ";
    std::cin >> memberId;

    try {
        if (!(std::all_of(memberId.begin(), memberId.end(), ::isdigit))) {
            throw std::invalid_argument("Member ID can only contain digits!");
        }

        auto patron = std::make_unique<Patron>(name, std::stoi(memberId));
        library.addPatron(std::move(patron));
        std::cout << "Patron added successfully.\n";
    } catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    
}

void checkoutLibraryItem(Library& library) {
    int memberId;
    std::string isbn, dueDate;
    std::cout << "Enter member ID: ";
    std::cin >> memberId;
    std::cout << "Enter ISBN of item to checkout (n-n-n-x): ";
    std::cin >> isbn;
    std::cout << "Enter due date (mm/dd/yyyy): ";
    std::cin >> dueDate;

    try {
        library.checkOutItem(memberId, isbn, dueDate);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void returnLibraryItem(Library& library) {
    int memberId;
    std::string isbn;
    std::string returnDate;
    std::cout << "Enter member ID: ";
    std::cin >> memberId;
    std::cout << "Enter ISBN of item to return (n-n-n-x): ";
    std::cin >> isbn;
    std::cout << "Enter return date (mm/dd/yyyy): ";
    std::cin >> returnDate;

    try {
        library.returnItem(memberId, isbn, returnDate);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void printReports(Library& library) {
    int choice;
    while (true) {
        printReportMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                library.printUsersWhoOweFees();
                break;
            case 2:
                library.printItemsOnWaitlist();
                break;
            case 3:
                library.printPatronsOnWaitlist();
                break;
            case 4:
                return;
            default:
                std::cerr << "Invalid choice. Please try again.\n";
        }
    }
}
