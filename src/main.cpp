#include "Library.h"
#include "Utility.h"
#include <iostream>

int main(int argc, char* argv[]) {
    std::string libraryFile;
    std::string patronFile;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            showHelp();
            return 0;
        } else if (arg == "-L") {
            if (i + 1 < argc) {
                libraryFile = argv[++i];
            } else {
                std::cerr << "Error: No file specified for -L option\n";
                showHelp();
                return 1;
            }
        } else if (arg == "-P") {
            if (i + 1 < argc) {
                patronFile = argv[++i];
            } else {
                std::cerr << "Error: No file specified for -P option\n";
                showHelp();
                return 1;
            }
        }
    }

    if (libraryFile.empty() || patronFile.empty()) {
        std::cerr << "Error: Both -L and -P options are required\n";
        showHelp();
        return 1;
    }

    try {
        Library library;
        library.loadLibraryItems(libraryFile);
        library.loadPatrons(patronFile);

        while (true) {
            displayMenu();
            int choice;
            std::cin >> choice;

            switch (choice) {
                case 1:
                    addLibraryItem(library);
                    break;
                case 2:
                    addLibraryPatron(library);
                    break;
                case 3:
                    checkoutLibraryItem(library);
                    break;
                case 4:
                    returnLibraryItem(library);
                    break;
                case 5:
                    printReports(library);
                    break;
                case 6:
                    return 0;
                default:
                    std::cerr << "Invalid choice. Please try again.\n";
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
