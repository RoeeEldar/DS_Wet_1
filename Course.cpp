//
// Created by Nadav Oved on 06/12/2025.
//

#include "Course.h"

Course::Course(const int courseCredit) : courseCredit(courseCredit)
{
}

bool Course::enroll(const int studentId, Student& student)
{
    student.enroll(); // update student
    return enrolledStudents.insert(studentId, &student);
}

bool Course::complete(const int studentId)
{
    auto* findResult = enrolledStudents.find(studentId);

    if (!findResult) return false;

    Student* student = findResult->getValue();
    student->unenroll();
    student->addCompletionPoints(courseCredit);
    enrolledStudents.erase(findResult);
    return true;
}

bool Course::isEmpty() const
{
    return enrolledStudents.isEmpty();
}
