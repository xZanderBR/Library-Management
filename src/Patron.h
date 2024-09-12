#pragma once
#include "LibraryItem.h"
#include <string>
#include <map>

class Patron {
public:
    Patron();
    Patron(const std::string& new_name, int new_membId, double fees = 0);

    std::string getName() const;
    int getMemberId() const;
    const std::map<LibraryItem*, std::string>& getCheckedOutItems() const;
    double getFeesOwed() const;

    void checkOutItem(LibraryItem* item, const std::string& dueDate);
    void returnItem(LibraryItem* item, const std::string& returnDate, const std::string& dueDate);
    void addFee(double amount);

private:
    std::string name = "Fido";
    int memberId = 10;
    std::map<LibraryItem*, std::string> checkedOutItems;
    double feesOwed = 0;
};
