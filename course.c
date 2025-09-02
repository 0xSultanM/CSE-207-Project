#include "course.h"

// Get semester name
const char* getSemesterNameC(Semester s) {
    switch (s) {
        case Spring: return "Spring";
        case Summer: return "Summer";
        case Fall:   return "Fall";
        default:     return "Unknown";
    }
}

int courseMenu(Course_f** head) {
    int choice;
    uint16_t id, studentId;
    char material[100];

    while (1) {
        printf("\n\t\t\t==== Course Management System ====\n");
        printf("\t\t1. Add New Course\n");
        printf("\t\t2. Update Course\n");
        printf("\t\t3. Delete Course\n");
        printf("\t\t4. Display All Courses\n");
        printf("\t\t5. Add Student to Course\n");
        printf("\t\t6. Add Material to Course\n");
        printf("\t\t0. Back to Main Menu\n\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("clear");
                *head = insertCourse(*head);
                break;

            case 2:
                system("clear");
                printf("\t\tEnter Course ID to update: ");
                scanf("%hu", &id);
                updateCourse(*head, id);
                break;

            case 3:
                system("clear");
                printf("\t\tEnter Course ID to delete: ");
                scanf("%hu", &id);
                *head = deleteCourse(*head, id);
                break;

            case 4:
                system("clear");
                displayAllCourses(*head);
                break;

            case 5:
                system("clear");
                printf("\t\tEnter Course ID: ");
                scanf("%hu", &id);
                printf("\t\tEnter Student ID: ");
                scanf("%hu", &studentId);
                addStudentToCourse(*head, id, studentId);
                break;

            case 6:
                system("clear");
                printf("\t\tEnter Course ID: ");
                scanf("%hu", &id);
                printf("\t\tEnter Material name: ");
                scanf(" %[^\n]", material);
                addMaterialToCourse(*head, id, material);
                break;

            case 0:
                system("clear");
                return 0;

            default:            
                system("clear");
                printf("\t\tInvalid choice!\n");
        }
    }
}

// Take input from user and create a new course
Course_f* inputCourse(void) {
    Course_f* newCourse = (Course_f*)malloc(sizeof(Course_f));
    if (!newCourse) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    printf("Enter Course ID: ");
    scanf("%hu", &newCourse->courseId);

    printf("Enter Course Name: ");
    scanf(" %[^\n]", newCourse->courseName);

    printf("Enter Credit Hours: ");
    scanf("%hu", &newCourse->creditHours);

    int semChoice;
    printf("Enter Semester (0=Spring, 1=Summer, 2=Fall): ");
    scanf("%d", &semChoice);
    newCourse->semester = (semChoice == 0 ? Spring : (semChoice == 1 ? Summer : Fall));

    printf("Enter Class Schedule: ");
    scanf(" %[^\n]", newCourse->classSchedule);

    newCourse->enrolledStudents = NULL;
    newCourse->studentCount = 0;
    newCourse->courseMaterials = NULL;
    newCourse->materialCount = 0;
    newCourse->next = NULL;

    return newCourse;
}

// Insert course
Course_f* insertCourse(Course_f* head) {
    Course_f* newCourse = inputCourse();
    newCourse->next = head;
    return newCourse;
}

// Delete course
Course_f* deleteCourse(Course_f* head, uint16_t id) {
    Course_f* temp = head;
    Course_f* prev = NULL;

    while (temp) {
        if (temp->courseId == id) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            freeCourse(temp);
            printf("Course deleted successfully.\n");
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Course not found.\n");
    return head;
}

// Update course
void updateCourse(Course_f* head, uint16_t id) {
    Course_f* temp = head;
    while (temp) {
        if (temp->courseId == id) {
            printf("Updating Course %hu...\n", id);
            printf("Enter New Course Name: ");
            scanf(" %[^\n]", temp->courseName);
            printf("Enter New Credit Hours: ");
            scanf("%hu", &temp->creditHours);
            printf("Enter New Schedule: ");
            scanf(" %[^\n]", temp->classSchedule);
            return;
        }
        temp = temp->next;
    }
    printf("Course not found.\n");
}

// Display one course
void displayCourse(const Course_f* c) {
    printf("ID: %hu | Name: %s | Credits: %hu | Semester: %s | Schedule: %s\n",
           c->courseId, c->courseName, c->creditHours,
           getSemesterNameC(c->semester), c->classSchedule);

    printf("  Students enrolled: %hu\n", c->studentCount);
    for (int i = 0; i < c->studentCount; i++) {
        printf("   - Student ID: %hu\n", c->enrolledStudents[i]);
    }

    printf("  Materials: %hu\n", c->materialCount);
    for (int i = 0; i < c->materialCount; i++) {
        printf("   - %s\n", c->courseMaterials[i]);
    }
}

// Display all courses
void displayAllCourses(const Course_f* head) {
    if (!head) {
        printf("No courses available.\n");
        return;
    }
    const Course_f* temp = head;
    while (temp) {
        displayCourse(temp);
        temp = temp->next;
    }
}

// Free one course
void freeCourse(Course_f* c) {
    if (!c) return;
    free(c->enrolledStudents);

    for (int i = 0; i < c->materialCount; i++) {
        free(c->courseMaterials[i]);
    }
    free(c->courseMaterials);

    free(c);
}

// Free all courses
void freeAllCourses(Course_f* head) {
    Course_f* temp;
    while (head) {
        temp = head;
        head = head->next;
        freeCourse(temp);
    }
}

// Add student to course
void addStudentToCourse(Course_f* head, uint16_t courseId, uint16_t studentId) {
    Course_f* temp = head;
    while (temp) {
        if (temp->courseId == courseId) {
            temp->enrolledStudents = realloc(temp->enrolledStudents, (temp->studentCount + 1) * sizeof(uint16_t));
            temp->enrolledStudents[temp->studentCount] = studentId;
            temp->studentCount++;
            printf("Student %hu added to course %hu.\n", studentId, courseId);
            return;
        }
        temp = temp->next;
    }
    printf("Course not found.\n");
}

// Add material to course
void addMaterialToCourse(Course_f* head, uint16_t courseId, const char* material) {
    Course_f* temp = head;
    while (temp) {
        if (temp->courseId == courseId) {
            temp->courseMaterials = realloc(temp->courseMaterials, (temp->materialCount + 1) * sizeof(char*));
            temp->courseMaterials[temp->materialCount] = strdup(material);
            temp->materialCount++;
            printf("Material added to course %hu.\n", courseId);
            return;
        }
        temp = temp->next;
    }
    printf("Course not found.\n");
}