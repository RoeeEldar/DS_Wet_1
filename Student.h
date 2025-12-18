//
// Created by Nadav Oved on 06/12/2025.
//

#ifndef DS_WET_1_STUDENT_H
#define DS_WET_1_STUDENT_H

class Student
{
    static int globalBonus;


    const int bonusPenalty; // to account for coming later than past bonuses
    int completionPoints = 0; // number of points student got by finishing courses.
    int courseCnt = 0;

public:
    static void addToGlobalBonus(int points);

    Student();

    void enroll();

    void unenroll();

    void addCompletionPoints(int points);

    int getStudentPoints() const;
    bool hasAnyCourses() const;
};


#endif //DS_WET_1_STUDENT_H
