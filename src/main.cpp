#include "StudentApplication.h"
#include "StudentManagement.h"

#include <iostream>

int main() {
    StudentManager manager;
    return runStudentApplication(manager, std::cin);
}
