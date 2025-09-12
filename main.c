#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include<stdlib.h>
#include"admin.h"
#include"student.h"
#include"Faculty.h"
#include"Attendence.h"
#include"course.h"

#define MAX_GRADES 100
uint16_t choice;

void studentPortal();
void facultyPortal();
void adminPortal();
void endProgram();

int main(){

    system("cls");
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
            case c1: system("cls"); studentPortal(); 
            break;
            case c2: system("cls"); facultyPortal(); 
            break;
            case c3: system("cls"); adminPortal(); 
            break;
            case c0: system("cls"); endProgram();
            default:
                system("cls");
                printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
            break;
        }
    }
    
}

void studentPortal(){


    while (1) {
        printf("\n\t\t\t<~~ Welcome to Student Portal ~~>\n");
        printf("\t\t1. Create New Account\n");
        printf("\t\t2. Student Login\n");
        printf("\t\t0. Return\n\n");

        printf("\t\tEnter your choice: ");
        scanf("%hd", &choice);

        switch (choice) {
            case c1: {
                system("cls"); 
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
                system("cls"); 
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
                system("cls");
                return;
            default:
                printf("\t\tInvalid choice. Please enter 1, 2, or 0.\n");
        }
    }
}

void facultyPortal(){

    Faculty prof;
    GradeRecord records[MAX_GRADES];
    Node_a* attendanceHead = NULL;
    Course_f* courseHead = NULL;
    int gradeCount = 0;

    do {
        printf("\n\t\t\t===== MAIN MENU =====\n");
        printf("\t\t1. Faculty\n");
        printf("\t\t2. Grade Records\n");
        printf("\t\t3. Attendance\n");
        printf("\t\t4. Course\n");
        printf("\t\t0. Return\n\n");
        printf("\t\tEnter choice: ");
        scanf("%hd", &choice);

        switch (choice) {
            case 1:
                system("cls");
                facultyMenu(&prof);
                break;
            case 2:
                system("cls");
                gradeMenu(records, &gradeCount);
                break;
            case 3:
                system("cls");
                attendanceMenu(&attendanceHead);
                break;
            case 4:
                system("cls");
                courseMenu(&courseHead);
                break;
            case 0:
                system("cls");
                return;
            default:
                system("cls");
                printf("\t\tInvalid choice. Try again.\n");
        }
    } while (choice != 0);

}

void adminPortal(){


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
            case c1: system("cls"); modifyUsers(); 
            break;
            case c2: system("cls"); addNewmember(); 
            break;
            case c3: system("cls"); paymentAndinvoice(); 
            break;
            case c4: system("cls"); courseAndenroll();
            break;
            case c5: system("cls"); examAndGrade();
            break;
            case c0: 
                system("cls");
                return;
            default:
                system("cls");
                printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
            break;
        }
    }
}

void endProgram() {
    system("cls");
    printf("\n\n\t\t\tHave a great day ahead...");
    printf("\n\n\n");
    exit(0);
}