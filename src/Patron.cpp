#include "Patron.h"
#include "LibraryItem.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

Patron::Patron() = default;

Patron::Patron(const std::string& new_name, int new_membId, double fees)
    : name(new_name), memberId(new_membId), feesOwed(fees) 
    {
        if (std::all_of(new_name.begin(), new_name.end(), ::isspace)) {
            throw std::invalid_argument("No patron name given!");
        }

        if (std::all_of(new_name.begin(), new_name.end(), ::isdigit)) {
            throw std::invalid_argument("Patron names can't only be digits!");
        }
    }

std::string Patron::getName() const { return name; }
int Patron::getMemberId() const { return memberId; }
const std::map<LibraryItem*, std::string>& Patron::getCheckedOutItems() const { return checkedOutItems; }
double Patron::getFeesOwed() const { return feesOwed; }

void Patron::checkOutItem(LibraryItem* item, const std::string& dueDate) {
    if (!(item->isValidDate(dueDate))) {
        throw std::runtime_error("Invalid date format!");
    }
    if (feesOwed == 0) {
        checkedOutItems[item] = dueDate;
        item->checkOut();
        std::cout << "ISBN: " << item->getISBN() << ", checked out successfully.\n";
    } else {
        throw std::runtime_error("Fees owed! Can't checkout new items.");
    }
}

void Patron::returnItem(LibraryItem* item, const std::string& returnDate, const std::string& dueDate) {
    if (returnDate > dueDate) {
        addFee(5);
        std::cout << name << ", member ID: " << memberId << ", incurred a $5 fee for turning in an item late.\n";
    }
    checkedOutItems.erase(item);
    item->returnItem();
    std::cout << "ISBN: " << item->getISBN() << ", returned successfully.\n";
}

void Patron::addFee(double amount) {
    feesOwed += amount;
}
