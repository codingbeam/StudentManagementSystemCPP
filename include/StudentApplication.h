#ifndef STUDENT_APPLICATION_H
#define STUDENT_APPLICATION_H

#include "StudentManagerInterface.h"

#include <iosfwd>

int runStudentApplication(StudentManagerInterface& manager, std::istream& input);

#endif
