#include <gtest/gtest.h>

#include "StudentManagement.h"

#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <streambuf>
#include <string>

namespace {

class CoutCapture {
public:
    explicit CoutCapture(std::ostream& output)
        : oldBuffer_(std::cout.rdbuf(output.rdbuf())),
          oldFlags_(std::cout.flags()),
          oldPrecision_(std::cout.precision()) {}

    ~CoutCapture() {
        std::cout.rdbuf(oldBuffer_);
        std::cout.flags(oldFlags_);
        std::cout.precision(oldPrecision_);
    }

    CoutCapture(const CoutCapture&) = delete;
    CoutCapture& operator=(const CoutCapture&) = delete;

private:
    std::streambuf* oldBuffer_;
    std::ios::fmtflags oldFlags_;
    std::streamsize oldPrecision_;
};

}  // namespace

TEST(StudentManagerTests, AddsValidStudent) {
    StudentManager manager;
    const Student student(1, "Amina", 87.5);

    EXPECT_TRUE(manager.addStudent(student));

    const auto found = manager.findStudentById(1);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Amina", found->getName());
    EXPECT_EQ(87.5, found->getMarks());
}

TEST(StudentManagerTests, RejectsDuplicateStudentId) {
    StudentManager manager;
    const Student first(1, "Amina", 87.5);
    const Student duplicate(1, "Other Name", 75.0);

    ASSERT_TRUE(manager.addStudent(first));
    EXPECT_FALSE(manager.addStudent(duplicate));

    const auto found = manager.findStudentById(1);
    ASSERT_TRUE(found.has_value());
    EXPECT_EQ("Amina", found->getName());
    EXPECT_EQ(87.5, found->getMarks());
}

TEST(StudentManagerTests, FindsExistingStudentById) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(12, "Ravi", 91.0)));

    const auto found = manager.findStudentById(12);

    ASSERT_TRUE(found.has_value());
    EXPECT_EQ(12, found->getId());
    EXPECT_EQ("Ravi", found->getName());
    EXPECT_EQ(91.0, found->getMarks());
}

TEST(StudentManagerTests, ReturnsEmptyWhenStudentIdIsNotFound) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(12, "Ravi", 91.0)));

    EXPECT_FALSE(manager.findStudentById(99).has_value());
}

TEST(StudentManagerTests, EmptyCollectionHasNoSearchAverageOrTopStudent) {
    StudentManager manager;

    EXPECT_FALSE(manager.findStudentById(1).has_value());
    EXPECT_FALSE(manager.calculateAverageMarks().has_value());
    EXPECT_FALSE(manager.findTopStudent().has_value());
}

TEST(StudentManagerTests, DisplaysMessageForEmptyCollection) {
    StudentManager manager;
    std::ostringstream output;
    CoutCapture capture(output);

    manager.displayStudents();

    EXPECT_EQ("No students to display.\n", output.str());
}

TEST(StudentManagerTests, DisplaysAddedStudent) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(5, "Lina", 82.25)));
    std::ostringstream output;
    CoutCapture capture(output);

    manager.displayStudents();

    EXPECT_NE(std::string::npos, output.str().find("Lina"));
    EXPECT_NE(std::string::npos, output.str().find("82.25"));
}

TEST(StudentManagerTests, CalculatesAverageMarks) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Amina", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Ravi", 100.0)));

    const auto average = manager.calculateAverageMarks();

    ASSERT_TRUE(average.has_value());
    EXPECT_EQ(90.0, *average);
}

TEST(StudentManagerTests, FindsStudentWithHighestMarks) {
    StudentManager manager;
    ASSERT_TRUE(manager.addStudent(Student(1, "Amina", 80.0)));
    ASSERT_TRUE(manager.addStudent(Student(2, "Ravi", 100.0)));
    ASSERT_TRUE(manager.addStudent(Student(3, "Lina", 90.0)));

    const auto topStudent = manager.findTopStudent();

    ASSERT_TRUE(topStudent.has_value());
    EXPECT_EQ(2, topStudent->getId());
    EXPECT_EQ("Ravi", topStudent->getName());
    EXPECT_EQ(100.0, topStudent->getMarks());
}

TEST(StudentManagerTests, RejectsInvalidStudentInputs) {
    const Student invalidStudents[] = {
        Student(0, "Valid Name", 50.0),
        Student(-1, "Valid Name", 50.0),
        Student(1, "", 50.0),
        Student(2, " \t\r\n", 50.0),
        Student(3, "Valid Name", -0.01),
        Student(4, "Valid Name", 100.01),
        Student(5, "Valid Name", std::numeric_limits<double>::quiet_NaN()),
        Student(6, "Valid Name", std::numeric_limits<double>::infinity())
    };

    for (const Student& student : invalidStudents) {
        StudentManager manager;
        EXPECT_FALSE(manager.addStudent(student))
            << "Unexpectedly accepted student ID " << student.getId();
        EXPECT_FALSE(manager.findStudentById(student.getId()).has_value());
    }
}

TEST(StudentManagerTests, AcceptsValidInputBoundaries) {
    StudentManager manager;

    EXPECT_TRUE(manager.addStudent(Student(1, "Minimum marks", 0.0)));
    EXPECT_TRUE(manager.addStudent(Student(2, "Maximum marks", 100.0)));
}
