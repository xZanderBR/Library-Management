#include "Library.h"
#include "Periodical.h"
#include "Book.h"
#include "Audio.h"
#include "Video.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

void Library::addItem(std::unique_ptr<LibraryItem> item) {
    std::string isbn = item->getISBN();
    collection[isbn].push_back(std::move(item));
}

void Library::addPatron(std::unique_ptr<Patron> patron) {
    patrons.insert({patron->getMemberId(), std::move(patron)});
}

void Library::checkOutItem(int memberId, const std::string& isbn, const std::string& dueDate) {
    if (patrons.find(memberId) == patrons.end()) {
        throw std::runtime_error("Patron not found.");
    }

    Patron* patron = patrons[memberId].get();
    if (collection.find(isbn) == collection.end() || collection[isbn].empty()) {
        throw std::runtime_error("Item not found.");
    }

    for (const auto& item : collection[isbn]) {
        if (!item->isCheckedOut()) {
            patron->checkOutItem(item.get(), dueDate);
            return;
        }
    }

    // If no available copies, add patron to the waitlist
    waitlist[isbn].push(memberId);
    std::cout << "All copies are currently checked out. Patron has been added to the waitlist.\n";
}

void Library::returnItem(int memberId, const std::string& isbn, const std::string& returnDate) {
    if (patrons.find(memberId) == patrons.end()) {
        throw std::runtime_error("Patron not found.");
    }

    Patron* patron = patrons[memberId].get();
    for (const auto& item : collection[isbn]) {
        if (patron->getCheckedOutItems().find(item.get()) != patron->getCheckedOutItems().end()) {
            patron->returnItem(item.get(), returnDate, patron->getCheckedOutItems().at(item.get()));

            // If there are patrons in the waitlist, allow the next patron to check out the item
            if (!waitlist[isbn].empty()) {
                int nextMemberId = waitlist[isbn].front();
                waitlist[isbn].pop();
                patrons[nextMemberId]->checkOutItem(item.get(), "12/30/9999"); // TODO: Date with automatic due date logic
                std::cout << "Checked out by member ID: " << nextMemberId << " from the waitlist.\n";
            }

            return;
        }
    }

    throw std::runtime_error("Item not checked out by this patron.");
}

void Library::collectFees(int memberId, double amount) {
    if (patrons.find(memberId) == patrons.end()) {
        throw std::runtime_error("Patron not found.");
    }

    patrons[memberId]->addFee(amount);
}

void Library::printUsersWhoOweFees() const {
    std::cout << "Users who owe fees:\n";
    for (const auto& [id, patron] : patrons) {
        if (patron->getFeesOwed() > 0) {
            std::cout << "Name: " << patron->getName() << ", member ID: " << patron->getMemberId() << ", Fees Owed: $" << std::fixed << std::setprecision(2) << patron->getFeesOwed() << "\n";
        }
    }
}

void Library::printItemsOnWaitlist() const {
    std::cout << "Items on the waitlist:\n";
    for (const auto& [isbn, patronsQueue] : waitlist) {
        if (!patronsQueue.empty()) {
            std::cout << "ISBN: " << isbn << " - Waitlist count: " << patronsQueue.size() << "\n";
        }
    }
}

void Library::printPatronsOnWaitlist() const {
    std::cout << "Patrons on the waitlist:\n";
    for (const auto& [isbn, queue] : waitlist) {
        std::queue<int> tempQueue = queue;
        while (!tempQueue.empty()) {
            int patronId = tempQueue.front();
            tempQueue.pop();
            const auto& patron = patrons.at(patronId);
            std::cout << "Patron Name: " << patron->getName() << ", member ID: " << patron->getMemberId() << ", ISBN: " << isbn << "\n";
        }
    }
}

void Library::loadLibraryItems(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open library collection file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string type, title, authors, genreStr, copyrightDate, isbn;
        int copyNumber;
        if (!(iss >> type >> std::quoted(title) >> std::quoted(authors) >> std::quoted(genreStr) >> std::quoted(copyrightDate) >> std::quoted(isbn) >> copyNumber)) {
            continue;
        }

        Genre genre;
        if (genreStr == "Fiction") genre = Genre::Fiction;
        else if (genreStr == "Non-Fiction") genre = Genre::NonFiction;
        else if (genreStr == "Mystery") genre = Genre::Mystery;
        else if (genreStr == "Sci-Fi") genre = Genre::SciFi;
        else if (genreStr == "Biography") genre = Genre::Biography;
        else continue;

        std::unique_ptr<LibraryItem> item;
        if (type == "Book") item = std::unique_ptr<LibraryItem>(new Book(title, authors, genre, copyrightDate, isbn, copyNumber));
        else if (type == "Periodical") item = std::unique_ptr<LibraryItem>(new Periodical(title, authors, genre, copyrightDate, isbn, copyNumber));
        else if (type == "Audio") item = std::unique_ptr<LibraryItem>(new Audio(title, authors, genre, copyrightDate, isbn, copyNumber));
        else if (type == "Video") item = std::unique_ptr<LibraryItem>(new Video(title, authors, genre, copyrightDate, isbn, copyNumber));

        if (item) addItem(std::move(item));
    }
}

void Library::loadPatrons(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Unable to open library patrons file.");
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int memberId;
        double fees;
        if (!(iss >> std::quoted(name) >> memberId >> fees)) {
            continue;
        }
        auto patron = std::make_unique<Patron>(name, memberId, fees);
        addPatron(std::move(patron));
    }
}
