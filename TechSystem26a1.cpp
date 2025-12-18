// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem()
{
    
}

TechSystem::~TechSystem()
{
    
}

StatusType TechSystem::addStudent(const int studentId)
{
    if (studentId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        const bool hasInserted = studentMap.insert(studentId, {});
        if (!hasInserted)
        {
            return StatusType::FAILURE;
        }

    } catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::removeStudent(int studentId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::addCourse(int courseId, int points)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::removeCourse(int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::completeCourse(int studentId, int courseId)
{
    return StatusType::FAILURE;
}

StatusType TechSystem::awardAcademicPoints(int points)
{
    return StatusType::FAILURE;
}

output_t<int> TechSystem::getStudentPoints(int studentId)
{
    return 0;
}