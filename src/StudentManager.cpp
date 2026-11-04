#include "StudentManagement.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numeric>

bool StudentManager::addStudent(const Student& student) {
    if (student.getId() <= 0 ||
        student.getName().find_first_not_of(" \t\r\n") == std::string::npos ||
        !std::isfinite(student.getMarks()) ||
        student.getMarks() < 0.0 ||
        student.getMarks() > 100.0 ||
        findStudentById(student.getId()).has_value()) {
        return false;
    }

    students_.push_back(student);
    return true;
}

void StudentManager::displayStudents() const {
    if (students_.empty()) {
        std::cout << "No students to display.\n";
        return;
    }

    std::cout << std::left << std::setw(12) << "ID"
              << std::setw(30) << "Name" << "Marks\n";
    std::cout << std::string(50, '-') << '\n';
    for (const Student& student : students_) {
        std::cout << std::left << std::setw(12) << student.getId()
                  << std::setw(30) << student.getName()
                  << std::fixed << std::setprecision(2)
                  << student.getMarks() << '\n';
    }
}

std::optional<Student> StudentManager::findStudentById(int id) const {
    for (const Student& student : students_) {
        if (student.getId() == id) {
            return student;
        }
    }
    return std::nullopt;
}

std::optional<double> StudentManager::calculateAverageMarks() const {
    if (students_.empty()) {
        return std::nullopt;
    }

    const double total = std::accumulate(
        students_.begin(), students_.end(), 0.0,
        [](double sum, const Student& student) {
            return sum + student.getMarks();
        });
    return total / static_cast<double>(students_.size());
}

std::optional<Student> StudentManager::findTopStudent() const {
    if (students_.empty()) {
        return std::nullopt;
    }

    const auto topStudent = std::max_element(
        students_.begin(), students_.end(),
        [](const Student& first, const Student& second) {
            return first.getMarks() < second.getMarks();
        });
    return *topStudent;
}