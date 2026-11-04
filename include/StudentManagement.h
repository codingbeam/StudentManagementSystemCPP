#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include "StudentManagerInterface.h"

#include <vector>

class StudentManager : public StudentManagerInterface {
public:
    bool addStudent(const Student& student) override;
    void displayStudents() const override;
    std::optional<Student> findStudentById(int id) const override;
    std::optional<double> calculateAverageMarks() const override;
    std::optional<Student> findTopStudent() const override;

private:
    std::vector<Student> students_;
};

#endif