// 
// 234218 Data Structures 1.
// Semester: 2026A (Winter).
// Wet Exercise #1.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef TechSystem26WINTER_WET1_H_
#define TechSystem26WINTER_WET1_H_

#include <Course.h>
#include <Student.h>

#include "wet1util.h"
#include "AvlTree.h"

class TechSystem {
private:

    AvlTree<int, Student> studentMap;
    AvlTree<int, Course> courseMap;


public:
    // <DO-NOT-MODIFY> {
    TechSystem();

    ~TechSystem();

    StatusType addStudent(int studentId);

    StatusType removeStudent(int studentId);

    StatusType addCourse(int courseId, int points);

    StatusType removeCourse(int courseId);

    StatusType enrollStudent(int studentId, int courseId);

    StatusType completeCourse(int studentId, int courseId);

    StatusType awardAcademicPoints(int points);

    output_t<int> getStudentPoints(int studentId);

    // } </DO-NOT-MODIFY>
};

#endif // TechSystem26WINTER_WET1_H_
