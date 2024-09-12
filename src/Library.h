#pragma once
#include "LibraryItem.h"
#include "Patron.h"
#include <memory>
#include <map>
#include <queue>
#include <string>
#include <vector>

class Library {
public:
    void addItem(std::unique_ptr<LibraryItem> item);
    void addPatron(std::unique_ptr<Patron> patron);

    void checkOutItem(int memberId, const std::string& isbn, const std::string& dueDate);
    void returnItem(int memberId, const std::string& isbn, const std::string& returnDate);
    void collectFees(int memberId, double amount);
    void printUsersWhoOweFees() const;
    void printItemsOnWaitlist() const;
    void printPatronsOnWaitlist() const;

    void loadLibraryItems(const std::string& filename);
    void loadPatrons(const std::string& filename);

private:
    std::map<std::string, std::vector<std::unique_ptr<LibraryItem>>> collection;
    std::map<int, std::unique_ptr<Patron>> patrons;
    std::map<std::string, std::queue<int>> waitlist;
};
