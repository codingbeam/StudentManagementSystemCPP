#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student(int id, std::string name, double marks);

    int getId() const;
    const std::string& getName() const;
    double getMarks() const;

private:
    int id_;
    std::string name_;
    double marks_;
};

#endif