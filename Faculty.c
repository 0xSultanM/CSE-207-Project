#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Faculty.h"

// -------------------- Faculty Functions --------------------

#define MAX_GRADES 100

// ---------------- Faculty Menu ----------------
void facultyMenu(Faculty *prof) {
    int choice, courseID;
    char input[200];

    do {
        printf("\n\t\t\t--- Faculty Menu ---\n");
        printf("\t\t1. Show Faculty Info\n");
        printf("\t\t2. Update Contact Info\n");
        printf("\t\t3. Update Office Hours\n");
        printf("\t\t4. Add Course\n");
        printf("\t\t5. Remove Course\n");
        printf("\t\t6. Add Research Interest\n");
        printf("\t\t7. Remove Research Interest\n");
        printf("\t\t0. Back to Main Menu\n\n");
        printf("\t\tEnter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                system("clear");
                printFaculty(prof);
                break;
            case 2: {
                system("clear");
                char newEmail[EMAIL_LEN], newContact[CONTACT_LEN];
                printf("\t\tEnter new email: ");
                fgets(newEmail, sizeof(newEmail), stdin);
                newEmail[strcspn(newEmail, "\n")] = 0;

                printf("\t\tEnter new contact number: ");
                fgets(newContact, sizeof(newContact), stdin);
                newContact[strcspn(newContact, "\n")] = 0;

                updateContactInfo(prof, newEmail, newContact);
                break;
            }
            case 3:
                system("clear");
                printf("\t\tEnter new office hours: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                updateOfficeHours(prof, input);
                break;
            case 4:
                system("clear");
                printf("\t\tEnter course ID to add: ");
                scanf("%d", &courseID);
                addCourseTaught(prof, courseID);
                break;
            case 5:
                system("clear");
                printf("\t\tEnter course ID to remove: ");
                scanf("%d", &courseID);
                removeCourseTaught(prof, courseID);
                break;
            case 6:
                system("clear");
                printf("\t\tEnter research topic: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                addResearchInterest(prof, input);
                break;
            case 7:
                system("clear");
                printf("\t\tEnter research topic to remove: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                removeResearchInterest(prof, input);
                break;
        }
    } while (choice != 0);
}

// ---------------- Grade Records Menu ----------------
void gradeMenu(GradeRecord records[], int *count) {
    int choice, studentID, courseID;
    float marks;
    char grade[GRADE_LEN], remarks[REMARKS_LEN];

    do {
        printf("\n\t\t\t--- Grade Records Menu ---\n");
        printf("\t\t1. Add Grade Record\n");
        printf("\t\t2. Show All Records\n");
        printf("\t\t3. Show Records by Student\n");
        printf("\t\t4. Show Records by Course\n");
        printf("\t\t5. Calculate Average Marks\n");
        printf("\t\t6. Update Grade\n");
        printf("\t\t0. Back to Main Menu\n\n");
        printf("\t\tEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                system("clear");
                if (*count < MAX_GRADES) {
                    printf("\t\tEnter student ID: ");
                    scanf("%d", &studentID);
                    printf("\t\tEnter course ID: ");
                    scanf("%d", &courseID);
                    printf("\t\tEnter marks: ");
                    scanf("%f", &marks);
                    getchar();
                    printf("\t\tEnter grade (A/B/C/D/F): ");
                    fgets(grade, sizeof(grade), stdin);
                    grade[strcspn(grade, "\n")] = 0;
                    printf("\t\tEnter remarks: ");
                    fgets(remarks, sizeof(remarks), stdin);
                    remarks[strcspn(remarks, "\n")] = 0;

                    initGradeRecord(&records[*count], studentID, courseID, marks, grade, remarks);
                    (*count)++;
                } else {
                    printf("\t\tMax records reached!\n");
                }
                break;
            case 2:
                system("clear");
                for (int i = 0; i < *count; i++) {
                    printGradeRecord(&records[i]);
                }
                break;
            case 3:
                system("clear");
                printf("\t\tEnter student ID: ");
                scanf("%d", &studentID);
                displayGradeRecordsByStudent(records, *count, studentID);
                break;
            case 4:
                system("clear");
                printf("\t\tEnter course ID: ");
                scanf("%d", &courseID);
                displayGradeRecordsByCourse(records, *count, courseID);
                break;
            case 5:
                system("clear");
                printf("\t\tEnter student ID: ");
                scanf("%d", &studentID);
                float avg = calculateAverageMarks(records, *count, studentID);
                printf("\t\tAverage Marks: %.2f | Final Grade: %c\n", avg, calculateFinalGrade(avg));
                break;
            case 6: {
                system("clear");
                printf("\t\tEnter record index (0 to %d): ", *count - 1);
                int idx;
                scanf("%d", &idx);
                if (idx >= 0 && idx < *count) {
                    printf("\t\tEnter new marks: ");
                    scanf("%f", &marks);
                    getchar();
                    printf("\t\tEnter new grade: ");
                    fgets(grade, sizeof(grade), stdin);
                    grade[strcspn(grade, "\n")] = 0;
                    printf("\t\tEnter new remarks: ");
                    fgets(remarks, sizeof(remarks), stdin);
                    remarks[strcspn(remarks, "\n")] = 0;
                    updateGrade(&records[idx], marks, grade, remarks);
                } else {
                    system("clear");
                    printf("\t\tInvalid index!\n");
                }
                break;
            }
        }
    } while (choice != 0);
}

void initFaculty(Faculty *f, int facultyID, const char *name, const char *email,
                 const char *department, const char *designation,
                 const char *contactNumber) {
    if (!f) return;

    f->facultyID = facultyID;
    strncpy(f->name, name, NAME_LENF);
    strncpy(f->email, email, EMAIL_LEN);
    strncpy(f->department, department, DEPT_LEN);
    strncpy(f->designation, designation, DESIG_LEN);
    strncpy(f->contactNumber, contactNumber, CONTACT_LEN);

    f->coursesTaught = NULL;
    f->coursesCount = 0;
    f->researchInterests = NULL;
    f->researchCount = 0;
    strcpy(f->officeHours, "Not Set");
}

bool updateContactInfo(Faculty *f, const char *newEmail, const char *newContactNumber) {
    if (!f) return false;
    if (newEmail) strncpy(f->email, newEmail, EMAIL_LEN);
    if (newContactNumber) strncpy(f->contactNumber, newContactNumber, CONTACT_LEN);
    return true;
}

bool addCourseTaught(Faculty *f, int courseID) {
    if (!f) return false;

    // check if course already exists
    CourseNode *curr = f->coursesTaught;
    while (curr) {
        if (curr->courseID == courseID) return false;
        curr = curr->next;
    }

    CourseNode *newNode = (CourseNode *)malloc(sizeof(CourseNode));
    if (!newNode) return false;
    newNode->courseID = courseID;
    newNode->next = f->coursesTaught;
    f->coursesTaught = newNode;
    f->coursesCount++;
    return true;
}

bool removeCourseTaught(Faculty *f, int courseID) {
    if (!f || !f->coursesTaught) return false;

    CourseNode *curr = f->coursesTaught, *prev = NULL;
    while (curr) {
        if (curr->courseID == courseID) {
            if (prev) prev->next = curr->next;
            else f->coursesTaught = curr->next;
            free(curr);
            f->coursesCount--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

bool teachesCourse(const Faculty *f, int courseID) {
    if (!f) return false;
    CourseNode *curr = f->coursesTaught;
    while (curr) {
        if (curr->courseID == courseID) return true;
        curr = curr->next;
    }
    return false;
}

bool addResearchInterest(Faculty *f, const char *topic) {
    if (!f) return false;

    ResearchNode *newNode = (ResearchNode *)malloc(sizeof(ResearchNode));
    if (!newNode) return false;
    strncpy(newNode->topic, topic, RESEARCH_TOPIC_LEN);
    newNode->next = f->researchInterests;
    f->researchInterests = newNode;
    f->researchCount++;
    return true;
}

bool removeResearchInterest(Faculty *f, const char *topic) {
    if (!f || !f->researchInterests) return false;

    ResearchNode *curr = f->researchInterests, *prev = NULL;
    while (curr) {
        if (strcmp(curr->topic, topic) == 0) {
            if (prev) prev->next = curr->next;
            else f->researchInterests = curr->next;
            free(curr);
            f->researchCount--;
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false;
}

void updateOfficeHours(Faculty *f, const char *newOfficeHours) {
    if (!f) return;
    strncpy(f->officeHours, newOfficeHours, OFFICE_HOURS);
}

void printFaculty(const Faculty *f) {
    if (!f) return;

    printf("Faculty ID: %d\n", f->facultyID);
    printf("Name: %s\n", f->name);
    printf("Email: %s\n", f->email);
    printf("Department: %s\n", f->department);
    printf("Designation: %s\n", f->designation);
    printf("Contact: %s\n", f->contactNumber);
    printf("Office Hours: %s\n", f->officeHours);

    printf("Courses Taught (%d): ", f->coursesCount);
    CourseNode *c = f->coursesTaught;
    while (c) {
        printf("%d ", c->courseID);
        c = c->next;
    }
    printf("\n");

    printf("Research Interests (%d): ", f->researchCount);
    ResearchNode *r = f->researchInterests;
    while (r) {
        printf("%s | ", r->topic);
        r = r->next;
    }
    printf("\n");
}

// -------------------- GradeRecord Functions --------------------

void initGradeRecord(GradeRecord *gr, int studentID, int courseID, float marks,
                     const char *grade, const char *remarks) {
    if (!gr) return;
    gr->studentID = studentID;
    gr->courseID = courseID;
    gr->marks = marks;
    strncpy(gr->grade, grade, GRADE_LEN);
    strncpy(gr->remarks, remarks, REMARKS_LEN);
}

void printGradeRecord(const GradeRecord *gr) {
    if (!gr) return;
    printf("Student ID: %d | Course ID: %d | Marks: %.2f | Grade: %s | Remarks: %s\n",
           gr->studentID, gr->courseID, gr->marks, gr->grade, gr->remarks);
}

void displayGradeRecordsByStudent(const GradeRecord records[], int count, int studentID) {
    for (int i = 0; i < count; i++) {
        if (records[i].studentID == studentID) {
            printGradeRecord(&records[i]);
        }
    }
}

void displayGradeRecordsByCourse(const GradeRecord records[], int count, int courseID) {
    for (int i = 0; i < count; i++) {
        if (records[i].courseID == courseID) {
            printGradeRecord(&records[i]);
        }
    }
}

float calculateAverageMarks(const GradeRecord records[], int count, int studentID) {
    int total = 0, cnt = 0;
    for (int i = 0; i < count; i++) {
        if (records[i].studentID == studentID) {
            total += records[i].marks;
            cnt++;
        }
    }
    return (cnt > 0) ? (float)total / cnt : 0.0f;
}

char calculateFinalGrade(float marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 80) return 'B';
    else if (marks >= 70) return 'C';
    else if (marks >= 60) return 'D';
    else return 'F';
}

bool updateGrade(GradeRecord *gr, float newMarks, const char *newGrade, const char *newRemarks) {
    if (!gr) return false;
    gr->marks = newMarks;
    if (newGrade) strncpy(gr->grade, newGrade, GRADE_LEN);
    if (newRemarks) strncpy(gr->remarks, newRemarks, REMARKS_LEN);
    return true;
}

bool isPassingGrade(const GradeRecord *gr) {
    if (!gr) return false;
    return (strcmp(gr->grade, "F") != 0 && strcmp(gr->grade, "D") != 0);
}