//
// Created by Nadav Oved on 06/12/2025.
//

#ifndef DS_WET_1_COURSE_H
#define DS_WET_1_COURSE_H


#include "Student.h"


class Course
{
    AvlTree<int, Student &> students;

    void enroll(Student &student);

    void complete(int studentId);
};


#endif //DS_WET_1_COURSE_H