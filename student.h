#ifndef STUDENT_H
#define STUDENT_H

#include <stdbool.h>

// =================== CONSTANTS ===================
#define ID_SIZE 20
#define NAME_SIZE 60
#define DOB_SIZE 12
#define ADDRESS_SIZE 150
#define EMAIL_SIZE 50
#define PHONE_SIZE 13
#define PASSWORD_SIZE 30
#define COURSE_SIZE 10
#define ADVICE_LIST_SIZE 100
#define OFFICE_HOURS_SIZE 50
#define COURSE_NAME_SIZE 50
#define COURSE_CODE_SIZE 6

// =================== ENUMS ===================
typedef enum { CSE, EEE, BBA, ENG, Civil, Other_dept } Department;
typedef enum { Spring, Summer, Fall } Semester;
typedef enum { A_POS, A_NEG, B_POS, B_NEG, O_POS, O_NEG, AB_POS, AB_NEG } BloodGroup;
typedef enum { FEES_PAID, FEES_UNPAID } FeeStatus;
typedef enum { DISCIPLINE_CLEAR, WARNING, FINE, SUSPENDED } DisciplineStatus;
typedef enum { CASH, CARD, ONLINE } PaymentMode;
typedef enum { SUCCESS, FAILURE } Status;

// =================== STRUCTS ===================
typedef struct {
    char courseName[COURSE_NAME_SIZE];
    char courseCode[COURSE_CODE_SIZE];
    int courseFee;
} Course_std;

typedef struct {
    char id[ID_SIZE];
    char name[NAME_SIZE];
    Department department;
    Semester semester;
    char dob[DOB_SIZE];
    BloodGroup bloodGroup;
    char address[ADDRESS_SIZE];
    char email[EMAIL_SIZE];
    char phone[PHONE_SIZE];
    char password[PASSWORD_SIZE];
    float cgpa;
    Course_std Course[COURSE_SIZE];
    FeeStatus feesPaid;
    DisciplineStatus disciplinaryStatus;
    char advisorName[NAME_SIZE];
} Student_std;

typedef struct {
    char advisorID[ID_SIZE];
    char name[NAME_SIZE];
    Department department;
    char email[EMAIL_SIZE];
    char phone[PHONE_SIZE];
    int adviceList[ADVICE_LIST_SIZE];
    int adviceCount;
    char officeHours[OFFICE_HOURS_SIZE];
} Advisor;

// =================== FUNCTION DECLARATIONS ===================
// Auth / accounts
void inputPassword(char* password);
int accountExists(const char* studentID);
void createAccount(void);
int studentLogin(void);
void changePassword(void);
void logout(void);

// Student profile
void viewProfile(const Student_std* s);
bool editProfile(Student_std* s, const char* newAddress, const char* newPhone, const char* newEmail);
void autoFillFromID(const char* studentID, Department* dept, Semester* sem);

// Courses / transcript
bool enrollCourse(Student_std* s, const char* courseCode);
bool dropCourse(Student_std* s, const char* courseCode);
bool downloadTranscript(const Student_std* s, const char* filePath);

// Academic info
void viewAcademicPerformance(const Student_std* s);
void viewExamSchedules(const Student_std* s);
void viewCoursesAndTimeTable(const Student_std* s);

// Fees
void viewFeesStatus(Student_std* s);
float calculateTotalFees(Student_std* s);
bool payFees(Student_std* s, int amount, PaymentMode mode);

// Advisor
Status addAdvisee(char id, const char* name);
void viewAdviseeList(void);
Status removeAdvisee(char id);
void viewAdvisor(const Advisor* a);

// Helpers
const char* getDepartmentName(Department dept);
const char* getSemesterName(Semester sem);

// ===== Functions used by main.c (moved out of main) =====
Student_std* findStudent(const char* studentID);
void completeProfile(Student_std* s);
void studentMenu(Student_std* currentStudent);

#endif
