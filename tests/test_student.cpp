#include <gtest/gtest.h>

#include "Student.h"

#include <cmath>
#include <limits>
#include <string>

TEST(StudentConstruction, StoresProvidedValues) {
    const Student student(42, "Amina", 87.5);

    ASSERT_EQ(42, student.getId());
    EXPECT_EQ("Amina", student.getName());
    EXPECT_EQ(87.5, student.getMarks());
    EXPECT_FALSE(std::isnan(student.getMarks()));
}

TEST(StudentConstruction, PreservesNegativeAndOutOfRangeValues) {
    // The current class does not validate IDs or marks; it stores them as given.
    const Student student(-7, "Below range", -0.5);

    EXPECT_EQ(-7, student.getId());
    EXPECT_EQ("Below range", student.getName());
    EXPECT_EQ(-0.5, student.getMarks());
}

TEST(StudentConstruction, PreservesNumericLimits) {
    const Student minimumStudent(
        std::numeric_limits<int>::min(),
        "Minimum",
        std::numeric_limits<double>::lowest());
    const Student maximumStudent(
        std::numeric_limits<int>::max(),
        "Maximum",
        std::numeric_limits<double>::max());

    EXPECT_EQ(std::numeric_limits<int>::min(), minimumStudent.getId());
    EXPECT_EQ(std::numeric_limits<double>::lowest(), minimumStudent.getMarks());
    EXPECT_EQ(std::numeric_limits<int>::max(), maximumStudent.getId());
    EXPECT_EQ(std::numeric_limits<double>::max(), maximumStudent.getMarks());
}

TEST(StudentConstruction, PreservesEmptyNameAndZeroValues) {
    const Student student(0, "", 0.0);

    EXPECT_EQ(0, student.getId());
    EXPECT_TRUE(student.getName().empty());
    EXPECT_EQ(0.0, student.getMarks());
}

TEST(StudentConstruction, PreservesSpecialFloatingPointValues) {
    const Student nanStudent(1, "NaN", std::numeric_limits<double>::quiet_NaN());
    const Student infinityStudent(2, "Infinity", std::numeric_limits<double>::infinity());

    EXPECT_TRUE(std::isnan(nanStudent.getMarks()));
    EXPECT_TRUE(std::isinf(infinityStudent.getMarks()));
    EXPECT_FALSE(std::isnan(infinityStudent.getMarks()));
}
