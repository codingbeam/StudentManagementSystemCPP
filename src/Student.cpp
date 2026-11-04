#include "Student.h"

#include <utility>

Student::Student(int id, std::string name, double marks)
    : id_(id), name_(std::move(name)), marks_(marks) {}

int Student::getId() const {
    return id_;
}

const std::string& Student::getName() const {
    return name_;
}

double Student::getMarks() const {
    return marks_;
}