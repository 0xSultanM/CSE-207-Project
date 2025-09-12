#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include"student.h"

#define MAX_NAME_LEN 50
#define MAX_SCHEDULE_LEN 30

typedef struct Course {
    uint16_t courseId;
    char courseName[MAX_NAME_LEN];
    uint16_t creditHours;
    Semester semester;
    char classSchedule[MAX_SCHEDULE_LEN];

    uint16_t* enrolledStudents;
    uint16_t studentCount;

    char** courseMaterials;
    uint16_t materialCount;

    struct Course* next;
} Course_f;

int courseMenu(Course_f** head);

Course_f* inputCourse(void);
Course_f* insertCourse(Course_f* head);
Course_f* deleteCourse(Course_f* head, uint16_t id);
void updateCourse(Course_f* head, uint16_t id);
void displayCourse(const Course_f* c);
void displayAllCourses(const Course_f* head);
void freeCourse(Course_f* c);
void freeAllCourses(Course_f* head);
const char* getSemesterNameC(Semester s);

void addStudentToCourse(Course_f* head, uint16_t courseId, uint16_t studentId);
void addMaterialToCourse(Course_f* head, uint16_t courseId, const char* material);

#endif