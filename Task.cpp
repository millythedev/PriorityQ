#include "Task.h"  // Pull struct and Priority enum


Task::Task(int id, std::string title, std::string dueDate, Priority priority)
    : id(id), title(title), dueDate(dueDate), priority(priority), completed(false) {}

// Converts the Priority enum value into a human readable string for display
std::string Task::priorityToString() const {
    switch (priority) {
        case Priority::HIGH:   return "HIGH";
        case Priority::MEDIUM: return "MEDIUM";
        case Priority::LOW:    return "LOW";
        default:               return "UNKNOWN";
    }
}

// Converts a string back into a Priority enum value
Priority Task::stringToPriority(const std::string& s) {
    if (s == "HIGH")   return Priority::HIGH;
    if (s == "MEDIUM") return Priority::MEDIUM;
    else               return Priority::LOW;  // Default to LOW if unrecognized
}