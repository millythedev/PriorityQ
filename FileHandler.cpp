#include "FileHandler.h"
#include <fstream>     
#include <sstream>     
#include <vector>
#include <iostream>    


// Saves each task to a file, one task per line
// Format: id,title,dueDate,priority,completed
void FileHandler::saveTasks(const std::string& filename, const std::vector<Task>& tasks) {
    std::ofstream file(filename);           // Open file for writing
    if (!file.is_open()) {
        std::cout << "Error saving tasks.\n";
        return;
    }
    for (const auto& task : tasks) {        // Write each task as a comma separated line
        file << task.id << ","
             << task.title << ","
             << task.dueDate << ","
             << task.priorityToString() << ","
             << task.completed << "\n";
    }
    file.close();
    std::cout << "Tasks saved.\n";
}

// Reads the file line by line and reconstructs Task objects from each line
std::vector<Task> FileHandler::loadTasks(const std::string& filename) {
    std::vector<Task> tasks;
    std::ifstream file(filename);           // Open file for reading
    if (!file.is_open()) {
        std::cout << "No saved tasks found. Starting fresh.\n";
        return tasks;                       // Return empty vector if file DNE or can't be opened
    }

    std::string line;
    while (std::getline(file, line)) {      
        std::stringstream ss(line);         
        std::string idStr, title, dueDate, priorityStr, completedStr;

        // Split the line by commas into each field
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, dueDate, ',');
        std::getline(ss, priorityStr, ',');
        std::getline(ss, completedStr, ',');

        // Reconstruct the Task object from the parsed fields
        Task task(std::stoi(idStr), title, dueDate, Task::stringToPriority(priorityStr));
        task.completed = (completedStr == "1");  // "1" means completed, "0" means hell nah
        tasks.push_back(task);
    }
    file.close();
    return tasks;
}