#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include <stdlib.h>
#include"admin.h"
#include"student.h"

uint16_t choice;

void studentPortal();
void facultyPortal();
void adminPortal();
void endProgram();

int main(){

    system("clear");
    printf("\t\t\t//// Welcome Back to University Portal ////\n\n");

    while (1) {
        printf("\n\t\t\t~~> Select your preferable option <~~\n\n");
        printf("\t\t1. Student\n");
        printf("\t\t2. Faculty\n");
        printf("\t\t3. Admin\n\n");
        printf("\t\t0. Exit\n");

        printf("\n\t\t\tEnter choice: ");
        scanf("%hd", &choice);

        switch ((MenuChoice)choice) {
            case c1: studentPortal(); 
            break;
            case c2: facultyPortal(); 
            break;
            case c3: adminPortal(); 
            break;
            case c0: endProgram();
            default:
            system("clear");
            printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
            break;
        }
    }
    
}

void studentPortal(){

    system("clear");
    while (1) {
        printf("\n\t\t\t<~~ Welcome to Student Portal ~~>\n");
        printf("\t\t1. Create New Account\n");
        printf("\t\t2. Student Login\n");
        printf("\t\t0. Return\n\n");

        printf("\t\tEnter your choice: ");
        scanf("%hd", &choice);

        switch (choice) {
            case c1: {
                createAccount();

                // After account creation, complete the profile
                extern Student_std students[];
                extern int studentCount;
                if (studentCount > 0) {
                    Student_std* newStudent = &students[studentCount - 1];
                    completeProfile(newStudent);
                }
                break;
            }
            case c2: {
                if (studentLogin()) {
                    // Find the logged-in student
                    char studentID[ID_SIZE];
                    printf("\t\tEnter your Student ID again for dashboard access: ");
                    scanf("%s", studentID);

                    Student_std* loggedInStudent = findStudent(studentID);
                    if (loggedInStudent != NULL) {
                        studentMenu(loggedInStudent);
                    } else {
                        printf("\t\tError accessing student dashboard.\n");
                    }
                }
                break;
            }
            case c0:
                system("clear");
                return;
            default:
                printf("\t\tInvalid choice. Please enter 1, 2, or 0.\n");
        }
    }
}

void facultyPortal(){

    system("clear");

}

void adminPortal(){

    system("clear");
    printf("\t\t\t~~> Welcome Back to Admin Portal <~~\n\n");

    while (1) {
        printf("\n\t\t\t~~> Select your preferable option: \n");
        printf("\t\t\t1. Modiy Users\n");
        printf("\t\t\t2. Add New Member\n");
        printf("\t\t\t3. Payment & Invoice\n");
        printf("\t\t\t4. Course Enrollment\n");
        printf("\t\t\t5. Exam & Grade\n");
        printf("\t\t\t0. Return\n");

        printf("\n\n\t\t\tEnter choice: ");
        scanf("%hd", &choice);

        switch ((MenuChoice)choice) {
            case c1: modifyUsers(); 
            break;
            case c2: addNewmember(); 
            break;
            case c3: paymentAndinvoice(); 
            break;
            case c4: courseAndenroll();
            break;
            case c5: examAndGrade();
            break;
            case c0: 
            system("clear");
            return;
            default:
            system("clear");
            printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
            main();
            break;
        }
    }
}

void endProgram() {
    system("clear");
    printf("\n\n\t\t\tHave a great day ahead...");
    printf("\n\n\n");
    exit(0);
}