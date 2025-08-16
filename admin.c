#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include"admin.h"

// declaring the structure for exam schedule
struct examSchedule exam;

//Menu Otpions for exam schedule
void examAndGrade(){
    int n,i,j;
    printf("\t\tAvailable Options:\n\n");
    printf("\t\t\t1. Exam Schedule\n");
    printf("\t\t\t2. Grade Report\n");
    printf("\t\t\t3. Exit\n\n");
    printf("\t\tSelect your proferable option: ");
    scanf("%d",&n);

    if(n==1){
        system("clear");
        printf("\t\tOptions for Exam Schedule:\n\n");
        printf("\t\t\t1. Add a new Exam Schedule\n");
        printf("\t\t\t2. Edit existing Exam Schedule\n");
        printf("\t\t\t3. View Any Exam Schedule\n");
        printf("\t\t\t4. Delete Any Exam Schedule\n");
        printf("\t\t\t5. Exam Schedule Status\n");
        printf("\t\t\t0. Exit\n");
        printf("\t\tNow select your preferable option: ");
        scanf("%d",&i);

        switch (i)
        {
            case 1:
                addExamSchedule();
                break;
            case 2:
                editExamSchedule();
                break;
            case 3:
                viewExamSchedule();
                break;
            case 4:
                deleteExamSchedule();
                break;
            case 5:
                isPublishedES();
                break;;
            case 0:
                system("clear");
                examAndGrade();
                break;
        }
    } else if(n==2){
        system("clear");
        printf("\t\tOptions Grade Report:\n\n");
        printf("\t\t\t1. View Grade Report\n");
        printf("\t\t\t2. Edit Grade Report\n");
        printf("\t\t\t3. Pubish Grade Report\n");
        printf("\t\t\t4. Grade Report Status\n");
        printf("\t\t\t0. Exit\n");
        printf("\t\tNow select your preferable option: ");
        scanf("%d",&j);

        switch (j)
        {
            case 1:
                viewGrade();
                break;
            case 2:
                editGrade();
                break;
            case 3:
                publishGrade();
                break;
            case 4:
                isPublishGrade();
                break;
            case 0:
                system("clear");
                examAndGrade();
                break;
        }

    } else if(n==3) {
        system("clear");
        printf("Logged Out Successfully!");
        exit(EXIT_SUCCESS);
    } else {
        system("clear");
        printf("\t\tInvalid Input. Kindly select again!\n\n");
        examAndGrade();
    }

}

// Add new exam schedule
void addExamSchedule(){
    system("clear");
    printf("\t\tWrite the course code: ");
    scanf("%s",exam.courseCode);
    printf("\t\tType the Date ( Format: DD/MM/YEAR ): ");
    scanf("%s",exam.date);
    printf("\t\tType the Time ( Format: 10:00 AM ): ");
    scanf("%s",exam.time);
}

// Edit or Modify the Exam Schedule
void editExamSchedule(){
    system("clear");
    char c[12];
    printf("Write the course code: ");
    scanf("%s",c);
    
    if(strcmp(c, exam.courseCode) == 0){
        printf("\t\tType the New Date ( Format: DD/MM/YEAR ): ");
        scanf("%s",exam.date);
        printf("\t\tType the New Time ( Format: 10:00 AM ): ");
        scanf("%s",exam.time);
    } else {
        printf("There isn't any scheduled exam for %s course",exam.courseCode);
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