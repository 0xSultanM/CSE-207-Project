#ifndef ADMIN_H
#define ADMIN_H

//write all the functions in here


//  ~~~~ Exam and Grades ~~~~

void examAndGrade();

// Exam schedule
struct examSchedule {
    char courseCode[12];
    char date[12];
    char time[10];
};

void addExamSchedule();
void editExamSchedule();
void viewExamSchedule();
void deleteExamSchedule();
void isPublishedES();

// Grade Details
struct gradeDetails{
    char studentID[16];
    char courseCode[12];
    char grade[4];
};


void viewGrade();
void editGrade();
void publishGrade();
void isPublishGrade();

#endif