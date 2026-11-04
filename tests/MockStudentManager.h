#ifndef MOCK_STUDENT_MANAGER_H
#define MOCK_STUDENT_MANAGER_H

#include "StudentManagerInterface.h"

#include <gmock/gmock.h>

class MockStudentManager : public StudentManagerInterface {
public:
    MOCK_METHOD(bool, addStudent, (const Student& student), (override));
    MOCK_METHOD(void, displayStudents, (), (const, override));
    MOCK_METHOD(std::optional<Student>, findStudentById, (int id), (const, override));
    MOCK_METHOD(std::optional<double>, calculateAverageMarks, (), (const, override));
    MOCK_METHOD(std::optional<Student>, findTopStudent, (), (const, override));
};

#endif
