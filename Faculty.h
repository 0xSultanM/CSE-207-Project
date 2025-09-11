
#ifndef FACULTY_H
#define FACULTY_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @def RESEARCH_TOPIC_LEN
 * @brief Maximum length for a research topic string.
 */
#define RESEARCH_TOPIC_LEN 100

/**
 * @def REMARKS_LEN
 * @brief Maximum length for remarks in a grade record.
 */
#define REMARKS_LEN 200

/**
 * @def GRADE_LEN
 * @brief Maximum length for a grade string.
 */
#define GRADE_LEN 3

/**
 * @struct ResearchNode
 * @brief Represents a linked list node storing research interests.
 */
typedef struct ResearchNode {
    char *topic;                /**< Research topic string */
    struct ResearchNode *next;  /**< Pointer to the next research node */
} ResearchNode;

/**
 * @struct CourseNode
 * @brief Represents a linked list node storing courses taught by a faculty.
 */
typedef struct CourseNode {
    uint32_t courseID;          /**< Unique course identifier */
    struct CourseNode *next;    /**< Pointer to the next course node */
} CourseNode;

/**
 * @struct Faculty
 * @brief Represents a faculty member and their details.
 */
typedef struct {
    uint32_t facultyID;          /**< Unique faculty identifier */
    char *name;                  /**< Faculty member name */
    char *email;                 /**< Faculty email address */
    char *department;            /**< Faculty department */
    char *designation;           /**< Faculty designation (e.g., Professor) */
    CourseNode *coursesTaught;   /**< Linked list of courses taught */
    uint16_t coursesCount;       /**< Number of courses taught */
    char *officeHours;           /**< Office hours string */
    ResearchNode *researchInterests; /**< Linked list of research interests */
    uint16_t researchCount;      /**< Number of research interests */
    char *contactNumber;         /**< Faculty contact number */
} Faculty;

/**
 * @struct GradeRecord
 * @brief Represents a student's grade record for a specific course.
 */
typedef struct {
    uint32_t studentID;   /**< Unique student identifier */
    uint32_t courseID;    /**< Unique course identifier */
    float marks;          /**< Marks obtained */
    char *grade;          /**< Letter grade */
    char *remarks;        /**< Remarks about performance */
} GradeRecord;

Faculty *createFaculty(uint32_t facultyID, const char *name, const char *email,
                       const char *department, const char *designation,
                       const char *contactNumber);
void freeFaculty(Faculty *f); 
 /**
 * @brief Frees memory allocated for a Faculty object.
 * 
 * @param f Pointer to the Faculty object to be freed.
 * @param newEmail 
 * @param newContactNumber 
 
 */

bool updateContactInfo(Faculty *f, const char *newEmail, const char *newContactNumber);
bool addCourseTaught(Faculty *f, uint32_t courseID);
bool removeCourseTaught(Faculty *f, uint32_t courseID);
bool teachesCourse(const Faculty *f, uint32_t courseID);
bool addResearchInterest(Faculty *f, const char *topic);
bool removeResearchInterest(Faculty *f, const char *topic);
void updateOfficeHours(Faculty *f, const char *newOfficeHours);
void printFaculty(const Faculty *f);
GradeRecord *createGradeRecord(uint32_t studentID, uint32_t courseID, float marks,
                               const char *grade, const char *remarks);
void freeGradeRecord(GradeRecord *gr);
void printGradeRecord(const GradeRecord *gr);
void displayGradeRecordsByStudent(GradeRecord *records[], uint16_t count, uint32_t studentID);
void displayGradeRecordsByCourse(GradeRecord *records[], uint16_t count, uint32_t courseID);
float calculateAverageMarks(GradeRecord *records[], uint16_t count, uint32_t studentID);
char calculateFinalGrade(float marks);
bool updateGrade(GradeRecord *gr, float newMarks, const char *newGrade, const char *newRemarks);
bool isPassingGrade(const GradeRecord *gr);

// Added functions for faculty and grade menu
void facultyMenu(Faculty *prof);
void gradeMenu(GradeRecord records[], int *gradeCount);

#endif
