#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "MockStudentManager.h"
#include "StudentApplication.h"

#include <iostream>
#include <optional>
#include <sstream>
#include <streambuf>
#include <string>

namespace {

class CoutCapture {
public:
    CoutCapture()
        : oldBuffer_(std::cout.rdbuf(output_.rdbuf())),
          oldFlags_(std::cout.flags()),
          oldPrecision_(std::cout.precision()) {}

    ~CoutCapture() {
        std::cout.rdbuf(oldBuffer_);
        std::cout.flags(oldFlags_);
        std::cout.precision(oldPrecision_);
    }

    std::string str() const {
        return output_.str();
    }

    CoutCapture(const CoutCapture&) = delete;
    CoutCapture& operator=(const CoutCapture&) = delete;

private:
    std::ostringstream output_;
    std::streambuf* oldBuffer_;
    std::ios::fmtflags oldFlags_;
    std::streamsize oldPrecision_;
};

using ::testing::Return;
using ::testing::StrictMock;

}  // namespace

TEST(StudentApplicationTests, ReportsSuccessfulAdd) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("1\n7\nAmina\n88.5\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, addStudent(::testing::Truly([](const Student& student) {
        return student.getId() == 7 &&
               student.getName() == "Amina" &&
               student.getMarks() == 88.5;
    })))
        .WillOnce(Return(true));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Student added successfully."));
}

TEST(StudentApplicationTests, ReportsRejectedAdd) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("1\n7\nAmina\n88.5\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, addStudent(::testing::_)).WillOnce(Return(false));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos,
              output.str().find("A student with that ID already exists."));
}

TEST(StudentApplicationTests, DisplaysFoundStudent) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("3\n7\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, findStudentById(7))
        .WillOnce(Return(std::optional<Student>(Student(7, "Amina", 88.5))));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Name: Amina"));
}

TEST(StudentApplicationTests, ReportsMissingStudent) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("3\n99\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, findStudentById(99)).WillOnce(Return(std::nullopt));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Student not found."));
}

TEST(StudentApplicationTests, ReportsNoAverageWhenManagerHasNoStudents) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("4\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, calculateAverageMarks()).WillOnce(Return(std::nullopt));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos,
              output.str().find("No students available to calculate an average."));
}

TEST(StudentApplicationTests, DisplaysAverageReturnedByManager) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("4\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, calculateAverageMarks()).WillOnce(Return(87.5));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Average marks: 87.50"));
}

TEST(StudentApplicationTests, DisplaysTopStudentReturnedByManager) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("5\n0\n");
    CoutCapture output;

    EXPECT_CALL(manager, findTopStudent())
        .WillOnce(Return(std::optional<Student>(Student(7, "Amina", 88.5))));

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Top student:"));
    EXPECT_NE(std::string::npos, output.str().find("Name: Amina"));
}

TEST(StudentApplicationTests, DelegatesDisplayRequest) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("2\n0\n");

    EXPECT_CALL(manager, displayStudents()).Times(1);

    EXPECT_EQ(0, runStudentApplication(manager, input));
}

TEST(StudentApplicationTests, RejectsInvalidIdBeforeCallingManager) {
    StrictMock<MockStudentManager> manager;
    std::istringstream input("1\n0\n0\n");
    CoutCapture output;

    EXPECT_EQ(0, runStudentApplication(manager, input));
    EXPECT_NE(std::string::npos, output.str().find("Student ID must be positive."));
}
