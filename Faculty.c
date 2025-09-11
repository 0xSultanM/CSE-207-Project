#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Faculty.h"

// Faculty functions
Faculty *createFaculty(uint32_t facultyID, const char *name, const char *email,
                       const char *department, const char *designation,
                       const char *contactNumber) {
    Faculty *f = (Faculty *)malloc(sizeof(Faculty));
    if (!f) return NULL;
    
    f->facultyID = facultyID;
    f->name = strdup(name);
    f->email = strdup(email);
    f->department = strdup(department);
    f->designation = strdup(designation);
    f->contactNumber = strdup(contactNumber);
    f->officeHours = strdup("Not Set");
    f->coursesTaught = NULL;
    f->coursesCount = 0;
    f->researchInterests = NULL;
    f->researchCount = 0;
    
    return f;
}

void freeFaculty(Faculty *f) {
    if (!f) return;
    
    free(f->name);
    free(f->email);
    free(f->department);
    free(f->designation);
    free(f->contactNumber);
    free(f->officeHours);
    
    // Free course nodes
    CourseNode *c = f->coursesTaught;
    while (c) {
        CourseNode *tmp = c;
        c = c->next;
        free(tmp);
    }
    
    // Free research nodes
    ResearchNode *r = f->researchInterests;
    while (r) {
        ResearchNode *tmp = r;
        r = r->next;
        free(tmp->topic);
        free(tmp);
    }
    
    free(f);
}

bool updateContactInfo(Faculty *f, const char *newEmail, const char *newContactNumber) {
    if (!f || !newEmail || !newContactNumber) return false;
    
    free(f->email);
    free(f->contactNumber);
    f->email = strdup(newEmail);
    f->contactNumber = strdup(newContactNumber);
    
    return (f->email && f->contactNumber);
}

 bool addCourseTaught(Faculty *f, uint32_t courseID){
    if (!f) return false;
    
    // Check if course already exists
    if (teachesCourse(f, courseID)) return false;
    
    CourseNode *newNode = (CourseNode *)malloc(sizeof(CourseNode));
    if (!newNode) return false;
    
    newNode->courseID = courseID;
    newNode->next = f->coursesTaught;
    f->coursesTaught = newNode;
    f->coursesCount++;
    
    return true;
}

bool removeCourseTaught(Faculty *f, uint32_t courseID) {
    if (!f || !f->coursesTaught) return false;
    
    CourseNode *current = f->coursesTaught;
    CourseNode *prev = NULL;
    
    while (current) {
        if (current->courseID == courseID) {
            if (prev) {
                prev->next = current->next;
            } else {
                f->coursesTaught = current->next;
            }
            free(current);
            f->coursesCount--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    
    return false;
}

bool teachesCourse(const Faculty *f, uint32_t courseID) {
    if (!f) return false;
    
    CourseNode *current = f->coursesTaught;
    while (current) {
        if (current->courseID == courseID) return true;
        current = current->next;
    }
    
    return false;
}

bool addResearchInterest(Faculty *f, const char *topic) {
    if (!f || !topic) return false;
    
    ResearchNode *newNode = (ResearchNode *)malloc(sizeof(ResearchNode));
    if (!newNode) return false;
    
    newNode->topic = strdup(topic);
    if (!newNode->topic) {
        free(newNode);
        return false;
    }
    
    newNode->next = f->researchInterests;
    f->researchInterests = newNode;
    f->researchCount++;
    
    return true;
}

bool removeResearchInterest(Faculty *f, const char *topic) {
    if (!f || !topic || !f->researchInterests) return false;
    
    ResearchNode *current = f->researchInterests;
    ResearchNode *prev = NULL;
    
    while (current) {
        if (strcmp(current->topic, topic) == 0) {
            if (prev) {
                prev->next = current->next;
            } else {
                f->researchInterests = current->next;
            }
            free(current->topic);
            free(current);
            f->researchCount--;
            return true;
        }
        prev = current;
        current = current->next;
    }
    
    return false;
}

void updateOfficeHours(Faculty *f, const char *newOfficeHours) {
    if (!f || !newOfficeHours) return;
    
    free(f->officeHours);
    f->officeHours = strdup(newOfficeHours);
}

void printFaculty(const Faculty *f) {
    if (!f) {
        printf("No faculty data available.\n");
        return;
    }
    
    printf("\n=== FACULTY INFORMATION ===\n");
    printf("ID: %d\n", f->facultyID);
    printf("Name: %s\n", f->name ? f->name : "N/A");
    printf("Email: %s\n", f->email ? f->email : "N/A");
    printf("Department: %s\n", f->department ? f->department : "N/A");
    printf("Designation: %s\n", f->designation ? f->designation : "N/A");
    printf("Contact: %s\n", f->contactNumber ? f->contactNumber : "N/A");
    printf("Office Hours: %s\n", f->officeHours ? f->officeHours : "N/A");
    
    printf("Courses Taught (%d): ", f->coursesCount);
    CourseNode *c = f->coursesTaught;
    if (!c) {
        printf("None");
    } else {
        while (c) {
            printf("%d", c->courseID);
            if (c->next) printf(", ");
            c = c->next;
        }
    }
    printf("\n");
    
    printf("Research Interests (%d): ", f->researchCount);
    ResearchNode *r = f->researchInterests;
    if (!r) {
        printf("None");
    } else {
        while (r) {
            printf("%s", r->topic);
            if (r->next) printf(", ");
            r = r->next;
        }
    }
    printf("\n");
}

// Grade Record functions
GradeRecord *createGradeRecord(uint32_t studentID, uint32_t courseID, float marks,
                               const char *grade, const char *remarks) {
    GradeRecord *gr = (GradeRecord *)malloc(sizeof(GradeRecord));
    if (!gr) return NULL;
    
    gr->studentID = studentID;
    gr->courseID = courseID;
    gr->marks = marks;
    gr->grade = strdup(grade ? grade : "N/A");
    gr->remarks = strdup(remarks ? remarks : "No remarks");
    
    if (!gr->grade || !gr->remarks) {
        freeGradeRecord(gr);
        return NULL;
    }
    
    return gr;
}

void freeGradeRecord(GradeRecord *gr) {
    if (!gr) return;
    
    free(gr->grade);
    free(gr->remarks);
    free(gr);
}

void printGradeRecord(const GradeRecord *gr) {
    if (!gr) {
        printf("No grade record available.\n");
        return;
    }
    
    printf("Student: %d, Course: %d, Marks: %.2f, Grade: %s, Remarks: %s",
           gr->studentID, gr->courseID, gr->marks,
           gr->grade ? gr->grade : "N/A",
           gr->remarks ? gr->remarks : "N/A");
}

void displayGradeRecordsByStudent(GradeRecord *records[], uint16_t count, uint32_t studentID) {
    printf("\n=== GRADES FOR STUDENT %d ===\n", studentID);
    bool found = false;
    
    for (int i = 0; i < count; i++) {
        if (records[i] && records[i]->studentID == studentID) {
            printGradeRecord(records[i]);
            printf("\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No records found for student %d.\n", studentID);
    }
}

void displayGradeRecordsByCourse(GradeRecord *records[], uint16_t count, uint32_t courseID){
    printf("\n=== GRADES FOR COURSE %d ===\n", courseID);
    bool found = false;
    
    for (int i = 0; i < count; i++) {
        if (records[i] && records[i]->courseID == courseID) {
            printGradeRecord(records[i]);
            printf("\n");
            found = true;
        }
    }
    
    if (!found) {
        printf("No records found for course %d.\n", courseID);
    }
}

float calculateAverageMarks(GradeRecord *records[], uint16_t count, uint32_t studentID) {
    float total = 0;
    uint16_t recordCount = 0;
    
    for (uint16_t i = 0; i < count; i++) {
        if (records[i] && records[i]->studentID == studentID) {
            total += records[i]->marks;
            recordCount++;
        }
    }
    
    return recordCount > 0 ? total / recordCount : -1;
}

char calculateFinalGrade(float marks) {
    if (marks >= 80) return 'A';
    else if (marks >= 70) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 50) return 'D';
    else return 'F';
}

bool updateGrade(GradeRecord *gr, float newMarks, const char *newGrade, const char *newRemarks) {
    if (!gr) return false;
    
    gr->marks = newMarks;
    
    if (newGrade) {
        free(gr->grade);
        gr->grade = strdup(newGrade);
        if (!gr->grade) return false;
    }
    
    if (newRemarks) {
        free(gr->remarks);
        gr->remarks = strdup(newRemarks);
        if (!gr->remarks) return false;
    }
    
    return true;
}

bool isPassingGrade(const GradeRecord *gr) {
    if (!gr || !gr->grade) return false;
    return (gr->grade[0] != 'F' && gr->marks >= 50);
}



// Simple stub for faculty menu
void facultyMenu(Faculty *prof) {
    printf("\n=== Faculty Menu ===\n");
    if (prof) {
        printFaculty(prof);
    } else {
        printf("No faculty data available.\n");
    }
}

// Simple stub for grade menu
void gradeMenu(GradeRecord records[], int *gradeCount) {
    printf("\n=== Grade Menu ===\n");
    if (*gradeCount == 0) {
        printf("No grade records available.\n");
    } else {
        for (int i = 0; i < *gradeCount; i++) {
            printGradeRecord(&records[i]);
            printf("\n");
        }
    }
}
