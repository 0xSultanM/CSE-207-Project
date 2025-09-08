  #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Faculty.h"

#define MAX_GRADES 100
#define MAX_FACULTY 10
#define BUFFER_SIZE 256

int main() {
    // Create faculty array using macro
    Faculty *faculty[MAX_FACULTY];
    GradeRecord *grades[MAX_GRADES];
    uint16_t facultyCount = 0;
    uint16_t gradeCount = 0;
    
    // Initialize arrays
    for (uint16_t i = 0; i < MAX_FACULTY; i++) faculty[i] = NULL;
    for (uint16_t i = 0; i < MAX_GRADES; i++) grades[i] = NULL;
    
    // Create default faculty
    faculty[facultyCount++] = createFaculty(1, "Dr. Mahir", "mahir@university.edu",
                                           "Computer Science", "Professor", "017XXXXXXXX");
    
    int32_t choice;
    char buffer[BUFFER_SIZE];
    
    printf("=== Faculty & Grade Management System ===\n");
    
    do {
        printf("\n--- MAIN MENU ---\n");
        printf("1. Display Faculty Info\n");
        printf("2. Add Course to Faculty\n");
        printf("3. Add Research Interest\n");
        printf("4. Add Grade Record\n");
        printf("5. View All Grades\n");
        printf("6. View Student Average\n");
        printf("0. Exit\n");
        printf("Choice: ");
        
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: // Display Faculty
                if (facultyCount > 0) {
                    printFaculty(faculty[0]);
                } else {
                    printf("No faculty available.\n");
                }
                break;
                
            case 2: // Add Course
                if (facultyCount > 0) {
                    uint32_t courseID;
                    printf("Enter Course ID: ");
                    scanf("%u", &courseID);
                    if (addCourseTaught(faculty[0], courseID)) {
                        printf("Course %u added successfully!\n", courseID);
                    } else {
                        printf("Failed to add course.\n");
                    }
                }
                break;
                
            case 3: // Add Research Interest
                if (facultyCount > 0) {
                    printf("Enter Research Topic: ");
                    getchar(); // Clear buffer
                    fgets(buffer, BUFFER_SIZE, stdin);
                    buffer[strcspn(buffer, "\n")] = 0; // Remove newline
                    if (addResearchInterest(faculty[0], buffer)) {
                        printf("Research interest added successfully!\n");
                    } else {
                        printf("Failed to add research interest.\n");
                    }
                }
                break;
                
            case 4: // Add Grade Record
                if (gradeCount < MAX_GRADES) {
                    uint32_t studentID, courseID;
                    float marks;
                    printf("Enter Student ID: ");
                    scanf("%u", &studentID);
                    printf("Enter Course ID: ");
                    scanf("%u", &courseID);
                    printf("Enter Marks: ");
                    scanf("%f", &marks);
                    
                    char grade = calculateFinalGrade(marks);
                    char gradeStr[GRADE_LEN];
                    sprintf(gradeStr, "%c", grade);
                    
                    grades[gradeCount] = createGradeRecord(studentID, courseID, marks, 
                                                          gradeStr, "Good work");
                    if (grades[gradeCount]) {
                        gradeCount++;
                        printf("Grade record added! Grade: %c\n", grade);
                    } else {
                        printf("Failed to add grade record.\n");
                    }
                } else {
                    printf("Grade storage full (Max: %d)!\n", MAX_GRADES);
                }
                break;
                
            case 5: // View All Grades
                printf("\n--- ALL GRADE RECORDS ---\n");
                if (gradeCount == 0) {
                    printf("No grade records found.\n");
                } else {
                    for (uint16_t i = 0; i < gradeCount; i++) {
                        if (grades[i]) {
                            printf("Record %u: ", i + 1);
                            printGradeRecord(grades[i]);
                            printf("\n");
                        }
                    }
                }
                break;
                
            case 6: // Student Average
                if (gradeCount > 0) {
                    uint32_t studentID;
                    printf("Enter Student ID: ");
                    scanf("%u", &studentID);
                    float avg = calculateAverageMarks(grades, gradeCount, studentID);
                    if (avg >= 0) {
                        printf("Student %u Average: %.2f (Grade: %c)\n", 
                               studentID, avg, calculateFinalGrade(avg));
                    } else {
                        printf("No records found for student %u.\n", studentID);
                    }
                } else {
                    printf("No grade records available.\n");
                }
                break;
                
            case 0:
                printf("Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice! Try again.\n");
        }
    } while (choice != 0);
    
    // Cleanup using macros
    for (uint16_t i = 0; i < MAX_GRADES; i++) {
        if (grades[i]) freeGradeRecord(grades[i]);
    }
    for (uint16_t i = 0; i < MAX_FACULTY; i++) {
        if (faculty[i]) freeFaculty(faculty[i]);
    }
    
    return 0;
}