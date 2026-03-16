#pragma once
#include <vector>    
#include "Task.h"    

// TaskManager handles all operations on the collection of tasks
//— adding, deleting, listing, filtering all lives here
class TaskManager {
private:
    std::vector<Task> tasks;  
    int nextId;               // Tracks the next available ID to assign to a new task

public:
   
    TaskManager();

  
    void addTask(const std::string& title, const std::string& dueDate, Priority priority);

  
    void completeTask(int id);

    void deleteTask(int id);

   
    void listTasks() const;

    // Displays only tasks that match a given priority level
    void filterByPriority(Priority priority) const;


    void listIncompleteTasks() const;

    // Sorts tasks by priority (HIGH first, LOW last)
    void sortByPriority();

    // Sorts tasks by due date (earliest first)
    void sortByDueDate();

    const std::vector<Task>& getTasks() const;

    void loadTasks(const std::vector<Task>& loadedTasks);
};