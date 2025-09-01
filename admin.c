#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include <stdlib.h>
#include"admin.h"

// declaring the structure for exam schedule
exam examS;

//Menu Otpions for exam schedule
void examAndGrade(){
    uint16_t n;
    printf("\t\tAvailable Options:\n\n");
    printf("\t\t\t1. Exam Schedule\n");
    printf("\t\t\t2. Grade Report\n");
    printf("\t\t\t0. Exit\n\n");
    printf("\t\tSelect your proferable option: ");
    scanf("%hd",&n);

    if(n==1){
        system("clear");
        examSchedule();
    } else if(n==2){
        system("clear");
        gradeReport();
    } else if(n==0) {
        system("clear");
        printf("\n\n\t\t\tLogged Out Successfully!\n\n");
        exit(EXIT_SUCCESS);
    } else {
        system("clear");
        printf("\n\n\t\tInvalid Input. Kindly select again!\n\n");
        examAndGrade();
    }

}

// Functions for Exam Schedule

// User input for exam schedule
void examSchedule(){
    uint16_t i;
    printf("\t\tOptions for Exam Schedule:\n\n");
    printf("\t\t\t1. Add a new Exam Schedule\n");
    printf("\t\t\t2. Edit existing Exam Schedule\n");
    printf("\t\t\t3. View Any Exam Schedule\n");
    printf("\t\t\t4. Delete Any Exam Schedule\n");
    printf("\t\t\t5. Exam Schedule Status\n");
    printf("\t\t\t6. Exit\n\n");
    printf("\t\tNow select your preferable option: ");
    scanf("%hd",&i);

    switch (i){
        case 1:
            addExamSchedule();
            examAndGrade();
            break;
        case 2:
            editExamSchedule();
            examAndGrade();
            break;
        case 3:
            viewExamSchedule();
            examAndGrade();
            break;
        case 4:
            deleteExamSchedule();
            examAndGrade();
            break;
        case 5:
            isPublishedES();
            examAndGrade();
            break;;
        case 6:
            system("clear");
            examAndGrade();
            break;
    }
}
// Add new exam schedule
void addExamSchedule(){
    system("clear");
    printf("\t\t\nSchedule the upcoming exams");
    printf("\n\n\t\tWrite the course code to add: ");
    scanf("%s",examS.courseCode);
    printf("\t\tType the Date ( Format: DD/MM/YEAR ): ");
    scanf("%s",examS.date);
    printf("\t\tType the Time ( Format: 10:00 AM ): ");
    scanf("%s",examS.time);
    system("clear");
    printf("\n\n\t\tExam for %s has been scheduled successfully!!\n\n",examS.courseCode);
}

// Edit or Modify the Exam Schedule
void editExamSchedule(){
    system("clear");
    printf("\n\t\tEdit or Modify the scheduled exams");
    char c[12];
    printf("\n\n\t\t\tWrite the course code to edit: ");
    scanf("%s",c);
    
    if(strcmp(c, examS.courseCode) == 0){
        printf("\n\n\t\tType the New Date ( Format: DD/MM/YEAR ): ");
        scanf("%s",examS.date);
        printf("\t\tType the New Time ( Format: 10:00 AM ): ");
        scanf("%s",examS.time);
        printf("\n\n\t\tExam time has been edited for %s sucessfully\n\n",examS.courseCode);
    } else {
        printf("\n\n\t\tThere isn't any scheduled exam for %s course\n\n",examS.courseCode);
    }
}

// View Any Schdeduled Exams
void viewExamSchedule(){

}

// Delete any scheduled Exams
void deleteExamSchedule(){

}

// Check Exam Schedule is published or not
void isPublishedES(){

}

// declaring the structure for grade
struct gradeDetails grades;

// functions for grade
// User input for grade
void gradeReport(){
    uint16_t j;
    printf("\t\tOptions Grade Report:\n\n");
    printf("\t\t\t1. View Grade Report\n");
    printf("\t\t\t2. Edit Grade Report\n");
    printf("\t\t\t3. Pubish Grade Report\n");
    printf("\t\t\t4. Grade Report Status\n");
    printf("\t\t\t5. Exit\n\n");
    printf("\t\tNow select your preferable option: ");
    scanf("%hd",&j);

    switch (j){
        case 1:
            viewGrade();
            examAndGrade();
            break;
        case 2:
            editGrade();
            examAndGrade();
            break;
        case 3:
            publishGrade();
            examAndGrade();
            break;
        case 4:
            isPublishGrade();
            examAndGrade();
            break;
        case 0:
            system("clear");
            examAndGrade();
            break;
    }
}

// View Grade of any course
void viewGrade(){

}

// Edit grade of any course
void editGrade(){

}

// Publish Grade Report for all student
void publishGrade(){

}

// Check Grade Report is published or not
void isPublishGrade(){

}