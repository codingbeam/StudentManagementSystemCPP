#ifndef STUDENT_MANAGER_INTERFACE_H
#define STUDENT_MANAGER_INTERFACE_H

#include "Student.h"

#include <optional>

class StudentManagerInterface {
public:
    virtual ~StudentManagerInterface() = default;

    virtual bool addStudent(const Student& student) = 0;
    virtual void displayStudents() const = 0;
    virtual std::optional<Student> findStudentById(int id) const = 0;
    virtual std::optional<double> calculateAverageMarks() const = 0;
    virtual std::optional<Student> findTopStudent() const = 0;
};

#endif
