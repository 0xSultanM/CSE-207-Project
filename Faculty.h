#ifndef Faculty_H
#define Faculty_H

#include <stdbool.h>

#define NAME_LENF 100       // Full name length
#define EMAIL_LEN 100      // Email Address length
#define DEPT_LEN 50        // Department name length 
#define DESIG_LEN 50       // Job title name length 
#define OFFICE_HOURS 50    // Office hours 
#define CONTACT_LEN 20     // Phone number length
#define RESEARCH_TOPIC_LEN 100
#define REMARKS_LEN 200    // Faculty remarks length 
#define GRADE_LEN 3        // Letter grade length

typedef struct ResearchNode {
    char topic[RESEARCH_TOPIC_LEN];
    struct ResearchNode *next;
} ResearchNode;


typedef struct CourseNode {
    int courseID;
    struct CourseNode *next;
} CourseNode;


typedef struct {
    int facultyID;                      
    char name[NAME_LENF];         
    char email[EMAIL_LEN];                     
    char department[DEPT_LEN];                
    char designation[DESIG_LEN];                
    CourseNode *coursesTaught;   
    int coursesCount;                   
    char officeHours[OFFICE_HOURS];                
    ResearchNode *researchInterests;   
    int researchCount;                   
    char contactNumber[CONTACT_LEN];             
} Faculty;


typedef struct {
    int studentID;           
    int courseID;                   
    float marks;                   
    char grade[GRADE_LEN];         
    char remarks[REMARKS_LEN];    
} GradeRecord;

// Departments
typedef enum {
    DEPT_CSE,
    DEPT_EEE,
    DEPT_ME,
    DEPT_CE,
    DEPT_BBA,
    DEPT_UNKNOWN
} Department_f;

// Designations
typedef enum {
    DESIGNATION_PROFESSOR,
    DESIGNATION_ASSOC_PROFESSOR,
    DESIGNATION_ASSISTANT_PROFESSOR,
    DESIGNATION_LECTURER,
    DESIGNATION_UNKNOWN
} Designation;

// Grades
typedef enum {
    GRADE_A,
    GRADE_B,
    GRADE_C,
    GRADE_D,
    GRADE_F,
    GRADE_INCOMPLETE
} Grade;

// Remarks
typedef enum {
    REMARK_EXCELLENT,
    REMARK_GOOD,
    REMARK_AVERAGE,
    REMARK_POOR,
    REMARK_NONE
} Remarks;

void facultyMenu(Faculty *prof);
void gradeMenu(GradeRecord records[], int *count);

void initFaculty(Faculty *f, int facultyID, const char *name, const char *email, 
                 const char *department, const char *designation, 
                 const char *contactNumber);

bool updateContactInfo(Faculty *f, const char *newEmail, const char *newContactNumber);

bool addCourseTaught(Faculty *f, int courseID);
bool removeCourseTaught(Faculty *f, int courseID);
bool teachesCourse(const Faculty *f, int courseID);

bool addResearchInterest(Faculty *f, const char *topic);
bool removeResearchInterest(Faculty *f, const char *topic);

void updateOfficeHours(Faculty *f, const char *newOfficeHours);

void printFaculty(const Faculty *f);


void initGradeRecord(GradeRecord *gr, int studentID, int courseID, float marks, 
                     const char *grade, const char *remarks);

void printGradeRecord(const GradeRecord *gr);

void displayGradeRecordsByStudent(const GradeRecord records[], int count, int studentID);
void displayGradeRecordsByCourse(const GradeRecord records[], int count, int courseID);

float calculateAverageMarks(const GradeRecord records[], int count, int studentID);

char calculateFinalGrade(float marks);

bool updateGrade(GradeRecord *gr, float newMarks, const char *newGrade, const char *newRemarks);

bool isPassingGrade(const GradeRecord *gr);

#endif