// You can edit anything you want in this file.
// However you need to implement all public StudentCourseManager function, as provided below as a template

#include "TechSystem26a1.h"


TechSystem::TechSystem() {
}

TechSystem::~TechSystem() {
}

StatusType TechSystem::addStudent(const int studentId) {
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        const bool hasInserted = studentMap.insert(studentId, {});
        if (!hasInserted) {
            return StatusType::FAILURE;
        }
    }
    catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::removeStudent(int studentId) {
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto* toRemove = studentMap.find(studentId);
    if (toRemove == nullptr || toRemove->getValue().hasAnyCourses()) {
        return StatusType::FAILURE;
    }
    studentMap.erase(toRemove);
    return StatusType::SUCCESS;
}

StatusType TechSystem::addCourse(int courseId, int points) {
    if (courseId <= 0 || points <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        const bool hasInserted = courseMap.insert(courseId, Course(points));
        if (!hasInserted) {
            // already in map
            return StatusType::FAILURE;
        }
    }
    catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::removeCourse(int courseId) {
    if (courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto* toRemove = courseMap.find(courseId);
    if (toRemove == nullptr || !toRemove->getValue().isEmpty()) {
        return StatusType::FAILURE;
    }
    courseMap.erase(toRemove);
    return StatusType::SUCCESS;
}

StatusType TechSystem::enrollStudent(int studentId, int courseId) {
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto* studentN = studentMap.find(studentId);
    auto* courseN = courseMap.find(courseId);
    if (courseN == nullptr || studentN == nullptr) {
        return StatusType::FAILURE;
    }
    // course is in course map

    try {
        const bool hasInserted = courseN->getValue().enroll(studentId, studentN->getValue());
        if (!hasInserted) {
            return StatusType::FAILURE;
        }
    }
    catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::completeCourse(int studentId, int courseId) {
    if (studentId <= 0 || courseId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto* courseN = courseMap.find(courseId);

    if (courseN == nullptr) {
        return StatusType::FAILURE;
    }
    bool hasCompleted = courseN->getValue().complete(studentId);
    if (!hasCompleted) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType TechSystem::awardAcademicPoints(int points) {
    if (points <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Student::addToGlobalBonus(points);
    return StatusType::SUCCESS;
}

output_t<int> TechSystem::getStudentPoints(int studentId) {
    if (studentId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    auto * studentN = studentMap.find(studentId);
    if (studentN == nullptr) {
        return StatusType::FAILURE;
    }
    return studentN->getValue().getStudentPoints();
}
