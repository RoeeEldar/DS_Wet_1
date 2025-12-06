//
// Created by Nadav Oved on 06/12/2025.
//

#ifndef DS_WET_1_STUDENT_H
#define DS_WET_1_STUDENT_H

class Student
{
    static int globalBonus;
    const int bonusPenalty;
    int completionPoints = 0;

public:
    Student();
    int getStudentPoints() const;
    void addCompletionPoints(int points);
    static void addToGlobalBonus(int points);
};


#endif //DS_WET_1_STUDENT_H
