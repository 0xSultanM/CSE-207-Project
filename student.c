#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

// =================== GLOBALS ===================
Student_std students[1000000];
int studentCount = 0;
Advisor advisor; // zero-initialized

// =================== HELPERS ===================
static void consume_stdin_line(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { /* discard */ }
}

const char* getDepartmentName(Department dept) {
    static const char* departments[] = {"CSE", "EEE", "BBA", "ENG", "Civil", "Other"};
    if (dept < CSE || dept > Other_dept) return "Other";
    return departments[dept];
}

const char* getSemesterName(Semester sem) {
    static const char* semesters[] = {"Spring", "Summer", "Fall"};
    if (sem < Spring || sem > Fall) return "Spring";
    return semesters[sem];
}

void inputPassword(char* password) {
    // NOTE: simple masked input (console only)
    // Assumes trailing newline already handled by caller (we do in create/login/change)
    char ch;
    int i = 0;

    printf("\t\tEnter Password: ");
    fflush(stdout);
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (i < PASSWORD_SIZE - 1 && ch != '\r') {
            password[i++] = ch;
            putchar('*');
            fflush(stdout);
        }
    }
    password[i] = '\0';
    printf("\n");
}

// =================== AUTH / ACCOUNTS ===================
int accountExists(const char* studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) return 1;
    }
    return 0;
}

void createAccount(void) {
    system("clear");
    Student_std newStudent;
    memset(&newStudent, 0, sizeof(newStudent));

    printf("\t\tEnter Student ID: ");
    scanf("%19s", newStudent.id);
    consume_stdin_line();

    if (accountExists(newStudent.id)) {
        printf("\t\t\tAccount with this ID already exists.\n");
        return;
    }

    inputPassword(newStudent.password);

    students[studentCount++] = newStudent;
    printf("\t\t\tAccount created successfully!\n");
}

int studentLogin(void) {
    char studentID[ID_SIZE];
    char password[PASSWORD_SIZE];

    printf("\t\tEnter Student ID: ");
    scanf("%19s", studentID);
    consume_stdin_line();

    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) { index = i; break; }
    }
    if (index == -1) {
        printf("\t\t\tAccount not found.\n");
        return 0;
    }

    inputPassword(password);

    if (strcmp(students[index].password, password) == 0) {
        printf("\t\t\tLogin successful!\n");
        return 1;
    } else {
        printf("\t\t\tIncorrect password.\n");
        return 0;
    }
}

void changePassword(void) {
    char studentID[ID_SIZE];
    char oldPassword[PASSWORD_SIZE], newPassword[PASSWORD_SIZE];

    printf("Enter Student ID: ");
    scanf("%19s", studentID);
    consume_stdin_line();

    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) { index = i; break; }
    }
    if (index == -1) {
        printf("Account not found.\n");
        return;
    }

    inputPassword(oldPassword);
    if (strcmp(students[index].password, oldPassword) != 0) {
        printf("\t\tIncorrect old password.\n");
        return;
    }

    inputPassword(newPassword);
    strcpy(students[index].password, newPassword);
    printf("\t\tPassword changed successfully!\n");
}

// =================== PROFILE ===================
void viewProfile(const Student_std* s) {
    if (!s) { printf("No student profile found.\n"); return; }

    static const char* bloodGroups[] = {"A_POS","A_NEG","B_POS","B_NEG","O_POS","O_NEG","AB_POS","AB_NEG"};
    static const char* disciplineStatus[] = {"CLEAR", "WARNING", "FINE", "SUSPENDED"};

    printf("\n===== Student Profile =====\n");
    printf("ID: %s\n", s->id);
    printf("Name: %s\n", s->name);
    printf("Department: %s\n", getDepartmentName(s->department));
    printf("Semester: %s\n", getSemesterName(s->semester));
    printf("DOB: %s\n", s->dob);
    printf("Blood Group: %s\n", bloodGroups[s->bloodGroup]);
    printf("Address: %s\n", s->address);
    printf("Email: %s\n", s->email);
    printf("Phone: %s\n", s->phone);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("Fee Status: %s\n", s->feesPaid == FEES_PAID ? "Paid" : "Unpaid");
    printf("Disciplinary: %s\n", disciplineStatus[s->disciplinaryStatus]);
    printf("Advisor: %s\n", s->advisorName);
    printf("===========================\n\n");
}

bool editProfile(Student_std* s, const char* newAddress, const char* newPhone, const char* newEmail) {
    if (!s) return false;

    if (newAddress && strlen(newAddress) < ADDRESS_SIZE) strcpy(s->address, newAddress);
    if (newPhone   && strlen(newPhone)   < PHONE_SIZE)   strcpy(s->phone, newPhone);
    if (newEmail   && strlen(newEmail)   < EMAIL_SIZE)   strcpy(s->email, newEmail);

    return true;
}

void autoFillFromID(const char* studentID, Department* dept, Semester* sem) {
    if (!studentID || !dept || !sem) return;

    if      (strncmp(studentID, "CSE", 3) == 0) *dept = CSE;
    else if (strncmp(studentID, "EEE", 3) == 0) *dept = EEE;
    else if (strncmp(studentID, "BBA", 3) == 0) *dept = BBA;
    else if (strncmp(studentID, "ENG", 3) == 0) *dept = ENG;
    else if (strncmp(studentID, "CIV", 3) == 0) *dept = Civil;
    else *dept = Other_dept;

    char semCode = studentID[3];
    switch (semCode) {
        case '1': *sem = Spring; break;
        case '2': *sem = Summer; break;
        case '3': *sem = Fall;   break;
        default:  *sem = Spring;
    }
}

// =================== COURSES / TRANSCRIPT ===================
bool enrollCourse(Student_std* s, const char* courseCode) {
    if (!s || !courseCode) return false;

    // already enrolled?
    for (int i = 0; i < COURSE_SIZE; i++) {
        if (strcmp(s->Course[i].courseCode, courseCode) == 0) {
            return false;
        }
    }

    // find empty slot
    for (int i = 0; i < COURSE_SIZE; i++) {
        if (s->Course[i].courseCode[0] == '\0') {
            strncpy(s->Course[i].courseCode, courseCode, COURSE_CODE_SIZE - 1);
            s->Course[i].courseCode[COURSE_CODE_SIZE - 1] = '\0';
            snprintf(s->Course[i].courseName, COURSE_NAME_SIZE, "Course - %s", courseCode);
            s->Course[i].courseFee = 1000;
            printf("%s successfully enrolled in %s.\n", s->name, courseCode);
            return true;
        }
    }
    return false;
}

bool dropCourse(Student_std* s, const char* courseCode) {
    if (!s || !courseCode) return false;

    for (int i = 0; i < COURSE_SIZE; i++) {
        if (strcmp(s->Course[i].courseCode, courseCode) == 0) {
            s->Course[i].courseCode[0] = '\0';
            s->Course[i].courseName[0] = '\0';
            s->Course[i].courseFee = 0;
            printf("%s successfully dropped %s.\n", s->name, courseCode);
            return true;
        }
    }
    return false;
}

bool downloadTranscript(const Student_std* s, const char* filePath) {
    if (!s || !filePath) return false;

    FILE* file = fopen(filePath, "w");
    if (!file) {
        printf("Could not save transcript.\n");
        return false;
    }

    printf("\n==== Academic Transcript ====\n");
    printf("Name       : %s\n", s->name);
    printf("Student ID : %s\n", s->id);
    printf("Department : %s\n", getDepartmentName(s->department));
    printf("Semester   : %s\n", getSemesterName(s->semester));
    printf("CGPA       : %.2f\n", s->cgpa);
    printf("\nCurrently Enrolled Courses:\n");

    fprintf(file, "        Academic Transcript    \n\n");
    fprintf(file, "Name       : %s\n", s->name);
    fprintf(file, "Student ID : %s\n", s->id);
    fprintf(file, "Department : %s\n", getDepartmentName(s->department));
    fprintf(file, "Semester   : %s\n", getSemesterName(s->semester));
    fprintf(file, "CGPA       : %.2f\n\n", s->cgpa);
    fprintf(file, "Currently Enrolled Courses:\n");

    int found = 0;
    for (int i = 0; i < COURSE_SIZE; i++) {
        if (s->Course[i].courseCode[0] != '\0') {
            printf("%s - %s | Fee: %d\n", s->Course[i].courseCode, s->Course[i].courseName, s->Course[i].courseFee);
            fprintf(file, "%s - %s | Fee: %d\n", s->Course[i].courseCode, s->Course[i].courseName, s->Course[i].courseFee);
            found = 1;
        }
    }

    if (!found) {
        printf("No active enrollments.\n");
        fprintf(file, "No active enrollments.\n");
    }

    fclose(file);
    printf("\nTranscript for %s has been saved to '%s'.\n", s->name, filePath);
    return true;
}

// =================== ACADEMICS ===================
void viewAcademicPerformance(const Student_std* s) {
    if (!s) return;
    printf("=== Academic Performance ===\n");
    printf("Name: %s\n", s->name);
    printf("ID: %s\n", s->id);
    printf("CGPA: %.2f\n", s->cgpa);
}

void viewExamSchedules(const Student_std* s) {
    if (!s) return;
    printf("=== Exam Schedule ===\n");
    printf("Name: %s\n", s->name);
    printf("ID: %s\n", s->id);

    for (int i = 0; i < COURSE_SIZE; i++) {
        if (s->Course[i].courseFee > 0) {
            printf("Course: %s (%s)\n", s->Course[i].courseName, s->Course[i].courseCode);
            printf("Exam Date: [To be determined]\n");
        }
    }
}

void viewCoursesAndTimeTable(const Student_std* s) {
    if (!s) return;
    printf("=== Courses and Timetable ===\n");
    printf("Name: %s\n", s->name);
    printf("ID: %s\n", s->id);

    for (int i = 0; i < COURSE_SIZE; i++) {
        if (s->Course[i].courseFee > 0) {
            printf("Course: %s (%s)\n", s->Course[i].courseName, s->Course[i].courseCode);
            printf("Class Time: [To be assigned]\n");
        }
    }
}

// =================== FEES ===================
void viewFeesStatus(Student_std* s) {
    if (!s) return;
    if (s->feesPaid == FEES_PAID) {
        printf("Fees Status: Paid ✅\n");
    } else {
        printf("Fees Status: Unpaid ❌\n");
    }
}

float calculateTotalFees(Student_std* s) {
    if (!s) return 0.0f;
    float total = 0.0f;
    for (int i = 0; i < COURSE_SIZE; i++) {
        if (s->Course[i].courseCode[0] != '\0') {
            total += s->Course[i].courseFee;
        }
    }
    return total;
}

bool payFees(Student_std* s, int amount, PaymentMode mode) {
    (void)mode; // not used yet
    if (!s) return false;

    float totalFees = calculateTotalFees(s);

    printf("\n\t\t\t--- Payment Summary ---\n");
    printf("\t\tTotal Fees: %.2f\n", totalFees);
    printf("\t\tPaid Amount: %d\n", amount);

    if ((float)amount == totalFees) {
        s->feesPaid = FEES_PAID;
        printf("Payment successful ✅ (Exact Amount).\n");
        return true;
    } else if ((float)amount < totalFees) {
        float due = totalFees - (float)amount;
        s->feesPaid = FEES_UNPAID;
        printf("Partial Payment received ❌ | Due Remaining: %.2f\n", due);
        return false;
    } else {
        float refund = (float)amount - totalFees;
        s->feesPaid = FEES_PAID;
        printf("Payment successful ✅ | Refund: %.2f\n", refund);
        return true;
    }
}

// =================== ADVISOR ===================
Status addAdvisee(char id, const char* name) {
    if (advisor.adviceCount >= ADVICE_LIST_SIZE) return FAILURE;

    advisor.adviceList[advisor.adviceCount] = (int)id;
    advisor.adviceCount++;

    printf("Advisee added: ID = %c | Name = %s\n", id, name);
    return SUCCESS;
}

void viewAdviseeList(void) {
    if (advisor.adviceCount == 0) {
        printf("No advisees found.\n");
        return;
    }

    printf("\n--- Advisee List ---\n");
    for (int i = 0; i < advisor.adviceCount; i++) {
        printf("%d. Advisee ID: %d\n", i + 1, advisor.adviceList[i]);
    }
}

Status removeAdvisee(char id) {
    int found = -1;
    for (int i = 0; i < advisor.adviceCount; i++) {
        if (advisor.adviceList[i] == (int)id) { found = i; break; }
    }
    if (found == -1) return FAILURE;

    for (int j = found; j < advisor.adviceCount - 1; j++) {
        advisor.adviceList[j] = advisor.adviceList[j + 1];
    }
    advisor.adviceCount--;

    printf("\t\tAdvisee with ID %c removed successfully.\n", id);
    return SUCCESS;
}

void viewAdvisor(const Advisor* a) {
    if (!a) { printf("No advisor information.\n"); return; }
    printf("\n=== Advisor Information ===\n");
    printf("\t\t\tAdvisor ID : %s\n", a->advisorID);
    printf("\t\t\tName       : %s\n", a->name);
    printf("\t\t\tDepartment : %s\n", getDepartmentName(a->department));
    printf("\t\t\tEmail      : %s\n", a->email);
    printf("\t\t\tPhone      : %s\n", a->phone);
    printf("\t\t\tOffice Hrs : %s\n", a->officeHours);
    printf("\t\t\tAdvisees   : %d\n", a->adviceCount);
    for (int i = 0; i < a->adviceCount; i++) {
        printf("  - Advisee ID (int code): %d\n", a->adviceList[i]);
    }
    printf("===========================\n");
}

// =================== FUNCTIONS USED BY main.c ===================
Student_std* findStudent(const char* studentID) {
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            return &students[i];
        }
    }
    return NULL;
}

void completeProfile(Student_std* s) {
    if (!s) return;

    printf("\n\t\t<~~ Complete Your Profile ~~>\n");

    printf("\t\tEnter your full name: ");
    consume_stdin_line();          // clear leftover newline
    fgets(s->name, NAME_SIZE, stdin);
    s->name[strcspn(s->name, "\n")] = 0;

    // Auto-fill from ID
    autoFillFromID(s->id, &s->department, &s->semester);

    printf("\t\tEnter date of birth (DD/MM/YYYY): ");
    fgets(s->dob, DOB_SIZE, stdin);
    s->dob[strcspn(s->dob, "\n")] = 0;

    printf("\t\tSelect blood group:\n");
    printf("\t\t\t0-A+, 1-A-, 2-B+, 3-B-, 4-O+, 5-O-, 6-AB+, 7-AB-\n");
    printf("\t\tEnter choice (0-7): ");
    int bloodChoice = 0;
    scanf("%d", &bloodChoice);
    consume_stdin_line();
    if (bloodChoice < 0) bloodChoice = 0;
    if (bloodChoice > 7) bloodChoice = 7;
    s->bloodGroup = (BloodGroup)bloodChoice;

    printf("\t\tEnter address: ");
    fgets(s->address, ADDRESS_SIZE, stdin);
    s->address[strcspn(s->address, "\n")] = 0;

    printf("\t\tEnter email: ");
    fgets(s->email, EMAIL_SIZE, stdin);
    s->email[strcspn(s->email, "\n")] = 0;

    printf("\t\tEnter phone number: ");
    fgets(s->phone, PHONE_SIZE, stdin);
    s->phone[strcspn(s->phone, "\n")] = 0;

    // Defaults
    s->cgpa = 0.0f;
    s->feesPaid = FEES_UNPAID;
    s->disciplinaryStatus = DISCIPLINE_CLEAR;
    strcpy(s->advisorName, "Dr. Default Advisor");

    // Clear courses
    for (int i = 0; i < COURSE_SIZE; i++) {
        s->Course[i].courseCode[0] = '\0';
        s->Course[i].courseName[0] = '\0';
        s->Course[i].courseFee = 0;
    }

    printf("\t\t\tProfile completed successfully!\n\n");
}

void studentMenu(Student_std* currentStudent) {
    system("clear");
    int choice;
    char courseCode[COURSE_CODE_SIZE];
    char newAddress[ADDRESS_SIZE], newPhone[PHONE_SIZE], newEmail[EMAIL_SIZE];
    char filename[64];

    while (1) {
        printf("\n\t\t\t<~~ Student Dashboard ~~>\n");
        printf("\t\tWelcome back, %s!\n", currentStudent->name);
        printf("\t\t1. View Profile\n");
        printf("\t\t2. Edit Profile\n");
        printf("\t\t3. Enroll in Course\n");
        printf("\t\t4. Drop Course\n");
        printf("\t\t5. View Academic Performance\n");
        printf("\t\t6. View Exam Schedule\n");
        printf("\t\t7. View Courses & Timetable\n");
        printf("\t\t8. Download Transcript\n");
        printf("\t\t9. View Fees Status\n");
        printf("\t\t10. Pay Fees\n");
        printf("\t\t11. Change Password\n");
        printf("\t\t0. Return\n\n");

        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewProfile(currentStudent);
                break;

            case 2:
                printf("\t\tEnter new address (or press Enter to skip): ");
                consume_stdin_line();
                fgets(newAddress, ADDRESS_SIZE, stdin);
                newAddress[strcspn(newAddress, "\n")] = 0;

                printf("\t\tEnter new phone (or press Enter to skip): ");
                fgets(newPhone, PHONE_SIZE, stdin);
                newPhone[strcspn(newPhone, "\n")] = 0;

                printf("\t\tEnter new email (or press Enter to skip): ");
                fgets(newEmail, EMAIL_SIZE, stdin);
                newEmail[strcspn(newEmail, "\n")] = 0;

                editProfile(currentStudent,
                            strlen(newAddress) > 0 ? newAddress : NULL,
                            strlen(newPhone) > 0 ? newPhone : NULL,
                            strlen(newEmail) > 0 ? newEmail : NULL);
                printf("\t\tProfile updated successfully!\n");
                break;

            case 3:
                printf("\t\tEnter course code to enroll: ");
                scanf("%5s", courseCode);
                if (!enrollCourse(currentStudent, courseCode)) {
                    printf("\t\tFailed to enroll. Course may already be enrolled or course list is full.\n");
                }
                break;

            case 4:
                printf("\t\tEnter course code to drop: ");
                scanf("%5s", courseCode);
                if (!dropCourse(currentStudent, courseCode)) {
                    printf("\t\tCourse not found in your enrollment list.\n");
                }
                break;

            case 5:
                viewAcademicPerformance(currentStudent);
                break;

            case 6:
                viewExamSchedules(currentStudent);
                break;

            case 7:
                viewCoursesAndTimeTable(currentStudent);
                break;

            case 8:
                printf("\t\tEnter filename for transcript (e.g., transcript.txt): ");
                scanf("%63s", filename);
                downloadTranscript(currentStudent, filename);
                break;

            case 9:
                viewFeesStatus(currentStudent);
                printf("\t\tTotal Fees: %.2f\n", calculateTotalFees(currentStudent));
                break;

            case 10: {
                int amount;
                int paymentMode;
                printf("\t\tTotal fees due: %.2f\n", calculateTotalFees(currentStudent));
                printf("\t\tEnter amount to pay: ");
                scanf("%d", &amount);
                printf("\t\tSelect payment mode (0-Cash, 1-Card, 2-Online): ");
                scanf("%d", &paymentMode);
                payFees(currentStudent, amount, (PaymentMode)paymentMode);
                break;
            }

            case 11:
                changePassword();
                break;

            case 0:
                system("clear");
                return;

            default:
                printf("\t\tInvalid choice. Please try again.\n");
        }
    }
}
