#include<stdio.h>
#include<string.h>
#include"admin.h"

// declaring the structure for exam schedule
struct examSchedule exam;

//fuctions for exam schedule
void addExamSchedule(){
    printf("\t\tWrite the course code: ");
    scanf("%s",&exam.courseCode);
    printf("\t\tType the Date ( Format: DD/MM/YEAR ): ");
    scanf("%s",&exam.date);
    printf("\t\tType the Date ( Format: 10:00 AM ): ");
    scanf("%s",&exam.time);
};
void editExamSchedule(){
    printf("Write the course code: ");
    scanf("%s",&exam.courseCode);
};
void viewExamSchedule();
void deleteExamSchedule();
int isPublishedES();

// declaring the structure for grade
struct gradeDetails grades;

// functions for grade
void viewGrade();
void editGrade();
void publishGrade();
int isPublishGrade();