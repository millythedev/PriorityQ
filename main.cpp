#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>     // Needed to enable ANSI color support on Windows terminals
#include "TaskManager.h"
#include "FileHandler.h"

const std::string SAVE_FILE = "forgetask_data.txt";

// Enables ANSI escape code support in Windows terminal
// Without this colors won't render see weird characters
void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

// ANSI color codes stored as constants
const std::string RESET   = "\033[0m";
const std::string RED     = "\033[31m";    // HIGH priority
const std::string YELLOW  = "\033[33m";    // MEDIUM priority
const std::string GREEN   = "\033[32m";    // LOW priority / completed
const std::string CYAN    = "\033[36m";    // Borders and headers
const std::string WHITE   = "\033[37m";    // Normal text
const std::string BOLD    = "\033[1m";     // Bold text for headers


std::string priorityColor(const std::string& p) {
    if (p == "HIGH")   return RED;
    if (p == "MEDIUM") return YELLOW;
    return GREEN;
}

//horizontal border line
void printBorder() {
    std::cout << CYAN << "+----+----------------------+------------+--------+---------+" << RESET << "\n";
}

// Prints the table column headers
void printTableHeader() {
    printBorder();
    std::cout << CYAN << "| " << BOLD << "ID" << RESET
              << CYAN << " | " << BOLD << std::left
              << std::setw(20) << "Title"    << RESET
              << CYAN << " | " << BOLD
              << std::setw(10) << "Due Date"  << RESET
              << CYAN << " | " << BOLD
              << std::setw(6)  << "Prio"     << RESET
              << CYAN << " | " << BOLD
              << std::setw(7)  << "Status"   << RESET
              << CYAN << " |" << RESET << "\n";
    printBorder();
}

// Draws a progress bar showing percentage of completed tasks

void printProgressBar(int completed, int total) {
    if (total == 0) {
        std::cout << CYAN << "\n No tasks to track.\n" << RESET;
        return;
    }
    int percent = (completed * 100) / total;
    int filled  = percent / 5;   // Bar is 20 chars wide, each block = 5%

    std::cout << CYAN << "\n Progress: [" << GREEN;
    for (int i = 0; i < 20; i++) {
        if (i < filled)      std::cout << "=";
        else if (i == filled) std::cout << ">";
        else                  std::cout << " ";
    }
    std::cout << RESET << CYAN << "] " << BOLD << percent << "% complete"
              << " (" << completed << "/" << total << " tasks done)"
              << RESET << "\n\n";
}

// Prints the main menu with clean borders and spacing
void printMenu() {
    std::cout << "\n" << CYAN
              << "  +==========================+\n"
              << "  |  " << BOLD << "    PriorityQ CLI    " << RESET << CYAN << "  |\n"
              << "  +==========================+\n"
              << "  |  1. Add Task             |\n"
              << "  |  2. List All Tasks       |\n"
              << "  |  3. Complete Task        |\n"
              << "  |  4. Delete Task          |\n"
              << "  |  5. Filter by Priority   |\n"
              << "  |  6. List Incomplete      |\n"
              << "  |  7. Sort by Priority     |\n"
              << "  |  8. Sort by Due Date     |\n"
              << "  |  9. Save Tasks           |\n"
              << "  |  0. Exit                 |\n"
              << "  +==========================+\n" << RESET
              << "  Choice: ";
}

int main() {
    enableANSI();   // integrate for color on windows terminals

    TaskManager manager;
    manager.loadTasks(FileHandler::loadTasks(SAVE_FILE));

    int choice;

    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();

        if (choice == 1) {
            std::string title, dueDate, priorityStr;
            std::cout << CYAN << "\n  Title: " << RESET;
            std::getline(std::cin, title);
            std::cout << CYAN << "  Due Date (YYYY-MM-DD): " << RESET;
            std::getline(std::cin, dueDate);
            std::cout << CYAN << "  Priority (LOW/MEDIUM/HIGH): " << RESET;
            std::getline(std::cin, priorityStr);
            manager.addTask(title, dueDate, Task::stringToPriority(priorityStr));

        } else if (choice == 2) {
            // Print table then progress bar
            printTableHeader();
            manager.listTasks();
            printBorder();
            auto tasks = manager.getTasks();
            int done = 0;
            for (const auto& t : tasks) if (t.completed) done++;
            printProgressBar(done, tasks.size());

        } else if (choice == 3) {
            int id;
            std::cout << CYAN << "\n  Task ID to complete: " << RESET;
            std::cin >> id;
            manager.completeTask(id);

        } else if (choice == 4) {
            int id;
            std::cout << CYAN << "\n  Task ID to delete: " << RESET;
            std::cin >> id;
            manager.deleteTask(id);

        } else if (choice == 5) {
            std::string priorityStr;
            std::cout << CYAN << "\n  Priority (LOW/MEDIUM/HIGH): " << RESET;
            std::cin >> priorityStr;
            printTableHeader();
            manager.filterByPriority(Task::stringToPriority(priorityStr));
            printBorder();

        } else if (choice == 6) {
            printTableHeader();
            manager.listIncompleteTasks();
            printBorder();

        } else if (choice == 7) {
            manager.sortByPriority();

        } else if (choice == 8) {
            manager.sortByDueDate();

        } else if (choice == 9) {
            FileHandler::saveTasks(SAVE_FILE, manager.getTasks());

        } else if (choice == 0) {
            FileHandler::saveTasks(SAVE_FILE, manager.getTasks());
            std::cout << GREEN << "\n  Tasks saved. Goodbye.\n" << RESET;
            break;

        } else {
            std::cout << RED << "\n  Invalid choice. Try again.\n" << RESET;
        }
    }
    return 0;
}