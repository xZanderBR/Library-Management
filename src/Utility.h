#pragma once

#include "Library.h"

void showHelp();
void displayMenu();
void printReportMenu();
void addLibraryItem(Library& library);
void addLibraryPatron(Library& library);
void checkoutLibraryItem(Library& library);
void returnLibraryItem(Library& library);
void printReports(Library& library);
