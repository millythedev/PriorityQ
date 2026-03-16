#pragma once
#include <string>      // For filename parameter
#include <vector>      // For returning a vector of tasks
#include "Task.h"      // So we know what a Task looks like

// FileHandler is responsible for reading and writing tasks to disk
// This is what makes tasks persist between program sessions
class FileHandler {
public:
    // Saves the entire task list to a file at the given path
    static void saveTasks(const std::string& filename, const std::vector<Task>& tasks);

    // Loads tasks from a file and returns them as a vector
    static std::vector<Task> loadTasks(const std::string& filename);
};