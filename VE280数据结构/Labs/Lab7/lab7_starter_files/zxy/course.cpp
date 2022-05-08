//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#include <iostream>
#include "course.h"
#include "../../../../../../../../../../CLionProjects/VE280/Lab7_ex1/course.h"


typedef struct task{
    std::string type;
    int index; // Task index of type
    int due_month;
    int due_day;
} Task;
/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * due_month and due_day specifies its due date
 */

const int MAXTASKS = 4; // default maximum number of tasks in a course at a time
class TechnicalCourse : public Course {
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;
public:
    // TODO: implement the constructor
    TechnicalCourse(const std::string &course_code, int size = MAXTASKS);
    TechnicalCourse();
    // TODO: declare and implement the destructor
    ~TechnicalCourse();
    // TODO: declare updateTask method
    void updateTask(const std::string &type, int index, int due_month, int due_day);
    void finishTask(const std::string &type, int index, int finish_month, int finish_day);
    void print();
};

TechnicalCourse::TechnicalCourse(const std::string &course_code, int size):numTasks(0), sizeTasks(size), course_code(course_code) {
    tasks = new Task[size];
}

TechnicalCourse::~TechnicalCourse() {
    delete [] tasks;
}

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its due_month & due_day ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    // TODO: implement this function
    for (int i = 0; i < numTasks; ++i) {
        if (tasks[i].index == index && tasks[i].type == type) {
            tasks[i].due_day = due_day;
            tasks[i].due_month = due_month;
            return;
        }
    }
    if (sizeTasks == numTasks) {
        tooManyTasks err;
        throw err;
    }
    tasks[numTasks++] = {type, index, due_month, due_day};
    if (type == "Lab" || type == "Project")
        std::cout << course_code << " " << type << " " << index << " is released! Submit it via oj!" << std::endl;
    else
        std::cout << course_code << " " << type << " " << index << " is released! Submit it via canvas!" << std::endl;
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
// REQUIRES: Task index of type is in tasks. finish_month and finish_day are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // TODO: implement this function
    for (int i = 0; i < numTasks; ++i) {
        if (tasks[i].index == index && tasks[i].type == type) {
            if (finish_month < tasks[i].due_month || (finish_day <= tasks[i].due_day && finish_month == tasks[i].due_month))
                std::cout << course_code << " " << type << " " << index << " is finished!" << std::endl;
            else
                std::cout << course_code << " " << type << " " << index << " is overdue!" << std::endl;
            for (int j = i; j < numTasks - 1; ++j) {
                tasks[j] = tasks[j + 1];
            }
            --numTasks;
            return;
        }
    }
}

void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for(int i = 0; i < numTasks; ++i){
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

TechnicalCourse::TechnicalCourse() {}


class UpperlevelTechnicalCourse : public TechnicalCourse {
public:
    // TODO: implement the constructor
    UpperlevelTechnicalCourse(const std::string &course_code, int size = MAXTASKS);
    UpperlevelTechnicalCourse();
    // TODO: declare and implement the destructor
    ~UpperlevelTechnicalCourse() {};
    void updateTask(const std::string &type, int index, int due_month, int due_day);
};

UpperlevelTechnicalCourse::UpperlevelTechnicalCourse(const std::string &course_code, int size) : TechnicalCourse(
        course_code, size) {

}

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    // TODO: implement this function
    for (int i = 0; i < numTasks; ++i) {
        if (tasks[i].index == index && tasks[i].type == type) {
            if (tasks[i].due_day == due_day && tasks[i].due_month == due_month)
                return;
            tasks[i].due_day = due_day;
            tasks[i].due_month = due_month;
            for (int j = i; j < numTasks - 1; ++j) {
                if (tasks[j].due_month > tasks[j + 1].due_month || (tasks[j].due_day >= tasks[j + 1].due_day && tasks[j].due_month == tasks[j + 1].due_month)){
                    Task tem = tasks[j];
                    tasks[j] = tasks[j+1];
                    tasks[j + 1] = tem;
                } else
                    return;
            }
            return;
        }
    }
    if (sizeTasks == numTasks) {
        tooManyTasks err;
        throw err;
    }
    int k = 0;
    for (; k < numTasks; ++k) {
        if (due_month < tasks[k].due_month || (due_day < tasks[k].due_day && due_month == tasks[k].due_month)) {
            for (int l = numTasks - 1; l >= k; --l) {
                tasks[l + 1] = tasks[l];
            }
            break;
        }
    }
    ++numTasks;
    tasks[k] = {type, index, due_month, due_day};
    if (type == "Lab" || type == "Project")
        std::cout << course_code << " " << type << " " << index << " is released! Submit it via oj!" << std::endl;
    else if (type == "Team Project")
        std::cout << course_code << " " << type << " " << index << " is released! Submit it via github!" << std::endl;
    else
        std::cout << course_code << " " << type << " " << index << " is released! Submit it via canvas!" << std::endl;
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if(class_type == "Technical"){
        if(assign_size){
            return new TechnicalCourse(course_code, tasks_size);
        }
        else{
            return new TechnicalCourse(course_code);
        }
    }
    else if(class_type == "Upper Level Technical"){
        if(assign_size){
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else{
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else{
        return nullptr;
    }
}

