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

void Course::complete(const int studentId) {

    Student** compStudent = enrolledStudents.find(studentId);
    if (compStudent) {
        // student found in course
        (*compStudent) -> Student::unenroll();
        (*compStudent) -> Student::addCompletionPoints(courseCredit);
        enrolledStudents.erase(studentId); // should return true,

    }
    // student not found in course
    // do something

    //check if course tree empty? why?
}
