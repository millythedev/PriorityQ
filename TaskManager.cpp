#include "TaskManager.h"
#include <iostream>        // For terminal output
#include <algorithm>       // For sort()
#include <iomanip>         // For setw() column formatting

// ANSI color codes for terminal output
const std::string RST   = "\033[0m";
const std::string RED_  = "\033[31m";
const std::string YEL_  = "\033[33m";
const std::string GRN_  = "\033[32m";
const std::string CYAN_ = "\033[36m";

// Returns the correct color string based on priority level
static std::string pColor(const std::string& p) {
    if (p == "HIGH")   return RED_;
    if (p == "MEDIUM") return YEL_;
    return GRN_;
}

// Prints a single task as a clean formatted table row

static void printRow(const Task& task) {
    std::string pc     = pColor(task.priorityToString());
    std::string status = task.completed ? "\033[32mDONE   " : "\033[33mPENDING";

    std::cout << CYAN_ << "| " << RST
              << std::setw(2)  << task.id                       << CYAN_ << " | " << RST
              << std::left
              << std::setw(20) << task.title.substr(0, 20)      << CYAN_ << " | " << RST
              << std::setw(10) << task.dueDate                  << CYAN_ << " | " << RST
              << pc << std::setw(6) << task.priorityToString()  << RST
              << CYAN_ << " | "
              << status << RST
              << CYAN_ << " |" << RST << "\n";
}


TaskManager::TaskManager() : nextId(1) {}

// Creates a new Task object and appends it to the tasks vector
void TaskManager::addTask(const std::string& title, const std::string& dueDate, Priority priority) {
    tasks.push_back(Task(nextId++, title, dueDate, priority));
    std::cout << GRN_ << "  Task added successfully.\n" << RST;
}

// Searches for a task by ID and marks it as completed
void TaskManager::completeTask(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            std::cout << GRN_ << "  Task " << id << " marked as complete.\n" << RST;
            return;
        }
    }
    std::cout << RED_ << "  Task not found.\n" << RST;
}

// Searches for a task by ID and removes it from the vector
void TaskManager::deleteTask(int id) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->id == id) {
            tasks.erase(it);
            std::cout << YEL_ << "  Task " << id << " deleted.\n" << RST;
            return;
        }
    }
    std::cout << RED_ << "  Task not found.\n" << RST;
}

// Prints all tasks as formatted table rows
void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << RED_ << "  No tasks found.\n" << RST;
        return;
    }
    for (const auto& task : tasks) printRow(task);
}

// Prints only tasks matching the given priority level
void TaskManager::filterByPriority(Priority priority) const {
    bool found = false;
    for (const auto& task : tasks) {
        if (task.priority == priority) {
            printRow(task);
            found = true;
        }
    }
    if (!found) std::cout << RED_ << "  No tasks found for that priority.\n" << RST;
}

// Prints only tasks that haven't been completed yet
void TaskManager::listIncompleteTasks() const {
    bool found = false;
    for (const auto& task : tasks) {
        if (!task.completed) {
            printRow(task);
            found = true;
        }
    }
    if (!found) std::cout << GRN_ << "  All tasks are complete!\n" << RST;
}

// Sorts the task list by priority — HIGH tasks rise to the top
void TaskManager::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.priority > b.priority;
    });
    std::cout << GRN_ << "  Tasks sorted by priority.\n" << RST;
}

// Sorts the task list by due date — earliest date comes first

void TaskManager::sortByDueDate() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        return a.dueDate < b.dueDate;
    });
    std::cout << GRN_ << "  Tasks sorted by due date.\n" << RST;
}

// Returns a constant reference to the full task list for reading
const std::vector<Task>& TaskManager::getTasks() const {
    return tasks;
}

// Replaces the current task list with tasks loaded from a file

void TaskManager::loadTasks(const std::vector<Task>& loadedTasks) {
    tasks = loadedTasks;
    for (const auto& task : tasks) {
        if (task.id >= nextId) nextId = task.id + 1;
    }
}