#ifndef ADMIN_H
#define ADMIN_H

typedef enum {
    c0 = 0,
    c1,
    c2,
    c3,
    c4,
    c5,
    c6,
    c7,
    c8,
    c9,
    c10
    
} MenuChoice;

/* | Following code is developed by
   |  Name: Mahmudur Rahaman Pial
   |  ID: 2024-1-60-177
*/

#define NAME_LEN 20
#define ROLE_LEN 20


typedef struct User {
    int userID;
    char name[NAME_LEN];
    char role[ROLE_LEN];
    struct User *next;
} User;

void modifyUsers();
void login();
void adduser();
void deleteuser();
void accessControlSet();
void systemMaintenance();



/* | Following code is developed by
   |  Name: Tauhid Uzzaman
   |  ID: 2023-3-60-581
*/

#define STUDENT 1
#define FACULTY 2
#define STAFF   3


typedef struct Node {
    int type;              
    char name[50];
    int id;
    struct Node*next;
} Node;

void addNewmember();

void addPerson(Node**head,int type,char name[],int id);
void removePerson(Node**head,int id);
void displayList(Node*head);



/* | Following code is developed by
   |  Name: Najhat Noorin Saima
   |  ID: 2024-1-60-255
*/

typedef struct{

    int id;
    char name[50];
    float totalFees;
    float paidFees;
   }Student;

   void paymentAndinvoice();
   
   void addStudent();
   void recordPayment();
   void generateInvoice();
   void displayAllStudents();

/* | Following code is developed by
   |  Name: Radwan Hossain Reshad
   |  ID: 2024-1-60-096
*/

#define C 100  

/* ---STRUCT FOR COURSE--- */
typedef struct 
{
    uint16_t id;
    uint16_t capacity_of_seat;
    uint16_t enrolled;
    char name[C];
    char faculty[C];

} Course;

/* ---STRUCT FOR ENROLLMENT--- */

typedef struct 
{
    uint16_t stdId;
    uint16_t courseId;
    char stdName[C];

} Enrollment;

/* DECLARING GLOBAL POINTERS TO DYNAMIC ARRAYS */
extern Course *c;      
extern Enrollment *e;
extern uint16_t Count1;// FOR COUNTING COURSE     
extern uint16_t Count2;// FOR COUNTING COUNTING ENROLLMENT     
extern uint16_t maxC;//MAXIMUM COURSES      
extern uint16_t maxE;//MAXIMUM ENROLLMENT  

/* NEEDED FUNCTION ARE GIVEN BELOW*/

void courseAndenroll();

/*ASIGNING COURSELIMIT, ENROLLLIMIT*/
void InitSystem(uint16_t courseL, uint16_t enrollL);

/* TO FREE MEMORY*/
void FreeSystem();//radwan hossain reshad

/*ADDING COURSE*/
void AddCourse(); 

/*TO VIEW ALL COURSES*/
void ViewCourses();

/*TO ENROLL STUDENT*/
void EnrollStd();

/*TO SEE ALL ENROLLMENTS*/
void ViewEnrollments();


/* | Following code is developed by
   |  Name: Tahsin Saraf Maisha
   |  ID: 2024-1-60-139
*/

/*TO DELETE A COURSE IF IT FOUND*/
void DeleteCourse();

/*TO DELETE AN ENROLLMENT IF IT FOUND*/
void DeleteEnrollment();


/*TO SEARCH A COURSE IF IT FOUND*/
void SearchCourse();

/*TO SEARCH ENROLLMENT*/
void SearchEnrollment();

/* | Following code is developed by
   |  Name: Sultan Mahmud
   |  ID: 2024-3-60-294
*/

//  ~~~~ Exam and Grades ~~~~

void examAndGrade();

// Exam schedule
typedef struct examSchedule {
    char courseCode[12];
    char date[12];
    char time[10];
}exam;

void examSchedule();

void addExamSchedule();
void editExamSchedule();
void viewExamSchedule();
void deleteExamSchedule();
void isPublishedES();

// Grade Details
typedef struct gradeDetails{
    char studentID[16];
    char courseCode[12];
    char grade[4];
}grade;

void gradeReport();

void viewGrade();
void editGrade();
void publishGrade();
void isPublishGrade();

#endif