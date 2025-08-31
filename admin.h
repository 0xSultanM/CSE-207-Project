#ifndef ADMIN_H
#define ADMIN_H

//write all the functions in here


//  ~~~~ Exam and Grades ~~~~

void examAndGrade();

// Exam schedule
typedef struct examSchedule {
    char courseCode[12];
    char date[12];
    char time[10];
}exam;

void examSchedule();

void addExamSchedule();
void editExamSchedule();
void viewExamSchedule();
void deleteExamSchedule();
void isPublishedES();

// Grade Details
typedef struct gradeDetails{
    char studentID[16];
    char courseCode[12];
    char grade[4];
}grade;

void gradeReport();

void viewGrade();
void editGrade();
void publishGrade();
void isPublishGrade();

#endif