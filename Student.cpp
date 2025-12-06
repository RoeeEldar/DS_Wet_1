//
// Created by Nadav Oved on 06/12/2025.
//

#include "Student.h"

int Student::globalBonus = 0;
Student::Student(): bonusPenalty(globalBonus)
{
}

int Student::getStudentPoints() const
{
    return completionPoints + (globalBonus - bonusPenalty);
}

void Student::addCompletionPoints(const int points)
{
    completionPoints += points;
}

void Student::addToGlobalBonus(const int points)
{
    globalBonus += points;
}