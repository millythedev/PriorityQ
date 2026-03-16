#pragma once 
#include <string> // Include necessary headers


//Enum representing task priority levels


enum class Priority {
    LOW,
    MEDIUM,
    HIGH
};


//struct holds all data for single task
struct Task {
    int id;
    std::string title;
    std::string dueDate;
    Priority priority;
    bool completed;

    Task(int id, std::string title, std::string dueDate, Priority priority);

    std::string priorityToString() const;

    //statoc method to convert string to Priority enum
    static Priority stringToPriority(const std::string& s);
};