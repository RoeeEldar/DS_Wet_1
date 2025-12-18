//
// Created by Nadav Oved on 06/12/2025.
//

#ifndef DS_WET_1_COURSE_H
#define DS_WET_1_COURSE_H


#include "Student.h"
#include "AvlTree.h"

class Course
{
    const int courseCredit;

    AvlTree<int, Student *> enrolledStudents;

public:

    explicit Course(int courseCredit);

    void enroll(int studentId, Student &student);

    bool complete(int studentId);
    bool isEmpty() const;
};


#endif //DS_WET_1_COURSE_H