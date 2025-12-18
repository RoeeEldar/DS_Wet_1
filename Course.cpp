//
// Created by Nadav Oved on 06/12/2025.
//

#include "Course.h"

Course::Course(const int courseCredit): courseCredit(courseCredit)
{
}

void Course::enroll(const int studentId, Student& student)
{
    student.enroll(); // update student
    enrolledStudents.insert(studentId, &student);
}

void Course::complete(const int studentId)
{
    enrolledStudents.find(studentId);
}
