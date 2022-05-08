//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#ifndef COURSE_H
#define COURSE_H

// an exception class
class tooManyTasks{};

class Course{
public:
    // TODO: declare methods and destructor here
    virtual ~Course() {};
    virtual void updateTask(const std::string &type, int index, int due_month, int due_day) = 0;
    // REQUIRES: due_month and due_day are in normal range.
    // MODIFIES: this
    // EFFECTS: adds/updates Task index of type; throw exception if fails to add  Task
    virtual void finishTask(const std::string &type, int index, int finish_month, int finish_day) = 0;
    // REQUIRES: Task index of type exists in tasks. finish_month and finish_day are in normal range.
    // MODIFIES: this
    // EFFECTS: removes Task index of type
    virtual void print() = 0;
    // EFFECTS: prints all unfinished tasks of this Course
};

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size);
// EFFECTS: returns a pointer according to class_type
//          If class_type is not "Technical" or "Upper Level Technical", returns a null pointer.
//          If assignSize is true, the maximum number of tasks is specified by tasksSize;
//          otherwise, the maximum number of tasks is the default value.

#endif //COURSE_H
