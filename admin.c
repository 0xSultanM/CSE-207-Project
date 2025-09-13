#include<stdio.h>
#include<string.h>
#include<stdint.h>
#include <stdlib.h>
#include"admin.h"

/* | Following code is developed by
   |  Name: Mahmudur Rahaman Pial
   |  ID: 2024-1-60-177
*/

void modifyUsers(){

    while (1) {
        printf("\n\t\t\t~~> Menu For Modifying Users <~~\n");
        printf("\t\t1. login\n");
        printf("\t\t2. Add User\n");
        printf("\t\t3. Delete User\n");
        printf("\t\t4. AccessControlSet\n");
        printf("\t\t5. SystemMaintenance\n");
        printf("\t\t6. Return\n");
        printf("\t\t0. Exit\n");

        printf("Enter choice: ");
        scanf("%hd", &choice);

        switch ((MenuChoice)choice) {
            case c1: 
                system("cls");
                login(); 
                break;
            case c2: 
                system("cls");
                adduser(); 
                break;
            case c3: 
                system("cls");
                deleteuser(); 
                break;
            case c4: 
                system("cls");
                accessControlSet(); 
                break;
            case c5: 
                system("cls");
                systemMaintenance(); 
                break;
            case c6:
                system("cls");
                return;
            case c0: 
                system("cls");
                printf("\n\n\t\t\tHave a great day ahead...");
                printf("\n\n\n");
                exit(0);
            default:
                system("cls"); 
                printf("Invalid number\n"); 
                break;
        }
    }
}

static User *head = NULL;

void login() {
    printf("System login by admin\n..");
}

void adduser() {
    User *u = (User*) malloc(sizeof(User));
    if (u == NULL) {
        printf("Add User Failed!\n");
        return;
    }

    printf("Enter user ID: ");
    scanf("%d", &u->userID);
    printf("Enter name: ");
    scanf("%s", u->name);
    printf("Enter Role: ");
    scanf("%s", u->role);


    u->next = head;
    head = u;

    printf("User '%s' added successfully.\n", u->name);
}

void deleteuser() {
    int deleteID;
    printf("Enter the User ID to delete: ");
    scanf("%d", &deleteID);

    User *curr = head, *prev = NULL;
    while (curr != NULL) {
        if (curr->userID == deleteID) {
            if (prev == NULL) {
                head = curr->next;
             }
            else {
                prev->next = curr->next;
            }
            printf("User with ID '%d' deleted successfully.\n", deleteID);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("User ID '%d' not found!\n", deleteID);
}

void accessControlSet() {
    printf("accessControlSet access by admin.\n");
}

void systemMaintenance() {
    printf("systemMaintenance access by admin.\n");
}


/* | Following code is developed by
   |  Name: Tauhid Uzzaman
   |  ID: 2023-3-60-581
*/

void addNewmember(){
    Node*head=NULL;
    int type,id;
    char name[50];

    while (1) {
        printf("\t\t\t\nAdmin Menu \n");
        printf("\t\t1.Add Person\n");
        printf("\t\t2.Remove Person\n");
        printf("\t\t3.Display List\n");
        printf("\t\t4.Return\n");
        printf("\t\t0. Exit\n\n");
        printf("\t\t\tEnter choice: ");
        scanf("%hd",&choice);

        switch ((MenuChoice)choice) {
            case c1:
                system("cls");
                printf("Enter type(1=Student,2=Faculty,3=Staff):");
                scanf("%d",&type);
                printf("Enter ID:");
                scanf("%d",&id);
                printf("Enter Name:");
                scanf("%[^\n]",name);
                addPerson(&head,type,name,id);
                break;

            case c2:
                system("cls");
                printf("Enter ID to remove:");
                scanf("%d",&id);
                removePerson(&head,id);
                break;

            case c3:
                system("cls");
                displayList(head);
                break;

            case c4:
                system("cls");
                return;

            case c0: 
                system("cls");
                printf("\n\n\t\t\tHave a great day ahead...");
                printf("\n\n\n");
                exit(0);
            default:
                system("cls");
                printf("Invalid choice!\n");
        }
    }
}

void addPerson(Node**head,int type,char name[],int id)
{
    Node*newNode=(Node*)malloc(sizeof(Node));
    newNode->type=type;
    strcpy(newNode->name,name);
    newNode->id=id;
    newNode->next=*head;
    *head=newNode;
}

void removePerson(Node**head,int id) 
{
    Node*temp=*head,*prev=NULL;

    while (temp!=NULL && temp->id!=id) 
    {
        prev=temp;
        temp=temp->next;
    }
    if (temp==NULL)
    {
        printf("ID %d not found!\n",id);
        return;
    }
    if (prev==NULL) 
    {
        *head=temp->next;
    } 
    else 
    {
        prev->next=temp->next;
    }
    free(temp);
    printf("ID %d removed successfully!\n",id);
}
void displayList(Node*head) 
{
    Node*temp=head;
    while(temp!=NULL) 
    {
        char*role;
        switch(temp->type) 
        {
            case STUDENT:role="Student";break;
            case FACULTY:role="Faculty";break;
            case STAFF:role="Staff";break;
            default:role="Unknown";break;
        }
        printf("ID:%d;Name: %s;Role:%s\n",temp->id,temp->name,role);
        temp=temp->next;
    }
}


/* | Following code is developed by
   |  Name: Najhat Noorin Saima
   |  ID: 2024-1-60-255
*/

#define MAX_STUDENTS 500

Student students[MAX_STUDENTS];
int studentcount = 0;

void paymentAndinvoice(){
    while (1) {
        printf("\n\t\t\t~~> Menu For Payment and Invoice <~~\n");
        printf("\t\t1. Add Payment\n");
        printf("\t\t2. Deposit Payment\n");
        printf("\t\t3. Generate Invoice\n");
        printf("\t\t4. Display All Students\n");
        printf("\t\t5. Return\n");
        printf("\t\t0. Exit\n\n");

        printf("\t\t\tEnter your choice: ");
        scanf("%hd", &choice);

        switch ((MenuChoice)choice) {
            case c1: system("cls"); addStudent(); 
            break;
            case c2: system("cls"); recordPayment(); 
            break;
            case c3: system("cls"); generateInvoice(); 
            break;
            case c4: system("cls"); displayAllStudents(); 
            break;
            case c5: 
                system("cls");
                return;
            case c0: 
                system("cls");
                printf("\n\n\t\t\tHave a great day ahead...");
                printf("\n\n\n");
                exit(0);
            default: 
                system("cls");
                printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
                break;
        }
    }
}

void addStudent(){
    if (studentcount >= MAX_STUDENTS){
    printf("Cannot add more\n");
        return;
    }
    printf("Enter Student ID:  ");
    scanf("%d", &students[studentcount].id);

    printf("Enter Student Name: ");
    scanf("%[^\n]s", students[studentcount].name);

    printf("Enter Total Fees: ");
    scanf("%f", &students[studentcount].totalFees);

    students[studentcount].paidFees = 0;

    studentcount++;
    printf("Student added successfully!\n");

}

void recordPayment() {
    int id;
    float amount;

    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < studentcount; i++) {
        if (students[i].id == id) {
            printf("Enter Payment Amount: ");
            scanf("%f", &amount);

            students[i].paidFees += amount;
            printf("Payment recorded successfully!\n");
            return;
        }
    }

    printf("Student not found!\n");
}

void generateInvoice() {
    int id;
    printf("Enter Student ID: ");
    scanf("%d", &id);

    for (int i = 0; i < studentcount; i++) {
        if (students[i].id == id) {
            printf(" Invoice\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Total Fees: %.f\n", students[i].totalFees);
            printf("Paid Fees: %.f\n", students[i].paidFees);
            printf("Due Fees: %.f\n", students[i].totalFees - students[i].paidFees);
            printf("-----------------\n");
            return;
        }
    }

    printf("Student not found!\n");
}

void displayAllStudents() {
    if (studentcount == 0) {
        printf("No students available.\n");
        return;
    }

    printf(" All Students\n");
    for (int i = 0; i < studentcount; i++) {
        printf("ID: %d\n", students[i].id);
        printf("Name: %s\n", students[i].name);
        printf("Total Fees: %.f\n", students[i].totalFees);
        printf("Paid Fees: %.f\n", students[i].paidFees);
        printf("Due Fees: %.f\n", students[i].totalFees - students[i].paidFees);

    }

}

/* | Following code is developed by
   |  Name: Radwan Hossain Reshad
   |  ID: 2024-1-60-096
*/

void courseAndenroll(){

    // initialize system with capacity for courses and enrollments
    InitSystem(50, 100);

    // menu loop using for with condition
    for (choice = -1; choice != 0; ) {
        printf("\n\n\t\t\t--- ADMIN PANEL: COURSE & ENROLLMENT MANAGEMENT ---\n\n");
        printf("\t\t\t1. Add Course & Assign Faculty\n");
        printf("\t\t\t2. View Courses\n");
        printf("\t\t\t3. Enroll Student\n");
        printf("\t\t\t4. View Enrollments\n");
        printf("\t\t\t5. Delete Course\n");
        printf("\t\t\t6. Delete Enrollment\n");
        printf("\t\t\t7. Search Course\n");
        printf("\t\t\t8. Search Enrollment\n");
        printf("\t\t\t9. Return\n");
        printf("\t\t\t0. Exit\n\n");
        printf("\t\t\tEnter choice: ");
        scanf("%hd", &choice);

        switch ((MenuChoice)choice) {
            case c1: system("cls"); AddCourse(); break;
            case c2: system("cls"); ViewCourses(); break;
            case c3: system("cls"); EnrollStd(); break;
            case c4: system("cls"); ViewEnrollments(); break;
            case c5: system("cls"); DeleteCourse(); break;
            case c6: system("cls"); DeleteEnrollment(); break;
            case c7: system("cls"); SearchCourse(); break;
            case c8: system("cls"); SearchEnrollment(); break;
            case c9: system("cls"); system("cls"); return;
            case c0: system("cls"); printf("\n\n\t\t\tHave a great day ahead..."); printf("\n\n\n"); exit(0);
            default: system("cls"); printf("Invalid choice!\n");
        }
    }
}


/* GLOBAL VARIABLES */
Course *c = NULL;
Enrollment *e = NULL;
uint16_t Count1 = 0;
uint16_t Count2 = 0;
uint16_t maxC = 0;// initialize max course to zero
uint16_t maxE = 0;//initialize max enrollemnt to zero

/* -------INITIALIZE SYSTEM WITH DYNAMIC MEMORY ALLOCATION------- */

void InitSystem(uint16_t courseL, uint16_t enrollL) 
{
    maxC = courseL;
    maxE = enrollL;
    c = (Course*) malloc ( maxC * sizeof(Course)); //DATA TYPE IS COURSE..
    e = (Enrollment*) malloc ( maxE * sizeof(Enrollment)); // DATA  TYPE IS ENROLLMENT..
    if (!c||!e) 
    {
        printf("SO,SORRY TO SAY, MEMORY ALLOCATION HAS FAILED!\n");
        exit(1);
    }
}

/* TO FREE MEMORY */

void FreeSystem() 
{
    free(c);// FOR COURSE c;
    free(e);// FOR ENROLLEMNT e;
}

/* ADDING COURSE */

void AddCourse() 
{
    if (Count1 >= maxC) 
    {
        printf("SORRY NO SPACE FOR ADDING COURSE, PLEASE!\n");
        return;
    }

    Course *a = &c[Count1]; // pointer to array element

    printf("ENTER COURSE ID: ");
    scanf("%hd", &a->id);

    printf("ENTER COURSE NAME: ");
    scanf(" %[^\n]s", a->name);

    printf("ENTER FACULTY NAME: ");
    scanf(" %[^\n]s", a->faculty);
    printf("ENTER COURSE CAPACITY: ");
    scanf("%hd", &a->capacity_of_seat);

    a->enrolled = 0;
    Count1++;
    printf("YEAH,COURSE ADDED SUCCESSFULLY!\n");
}

/* TO VIEW COURSES */
void ViewCourses() 
{
    if (Count1 == 0) 
    {
        printf("SORRY NO COURSE AVAILABLE.\n");
        return;
    }

    printf("----- COURSE LIST -----\n");

    for (uint16_t i=0;i<Count1;i++) 
    {
        Course *b = &c[i];
        printf("ID: %d , Name: %s , Faculty: %s , Capacity: %d , Enrolled: %d\n",b->id, b->name, b->faculty, b->capacity_of_seat, b->enrolled);
    }
}

/* TO ENROLL STUDENT */

void EnrollStd() 
{
    if (Count2 >= maxE) 
    {
        printf("NO SPACE FOR ENROLLMENTS!!!\n");
        return;
    }

    uint16_t courseId;
    printf("ENTER COURSE ID TO ENROLL: ");
    scanf("%hd", &courseId);

    /*-----TO FINDING COURSE----- */
    Course *w = NULL;
    for (uint16_t i=0;i<Count1; i++) 
    {
        if (c[i].id == courseId) {
            w = &c[i];
            break;
        }
    }
    if (!w) 
    {
        printf("SORRY COURSE NOT FOUND!!!\n");
        return;
    }
    if (w->enrolled >= w->capacity_of_seat) {
        printf("COURSE IS FULL!!!!\n");
        return;
    }

    Enrollment *r = &e[Count2];

    printf("ENTER STUDENT ID : ");
    scanf("%hd", &r->stdId);
    printf("Enter student name: ");
    scanf(" %[^\n]s", r->stdName);

    r->courseId = courseId;
    Count2++;
    w->enrolled++;

    printf("STUDENT ENROLLED SUCCESSFULLY!\n");
}//radwan hossain reshad

/* | Following code is developed by
   |  Name: Tahsin Saraf Maisha
   |  ID: 2024-1-60-139
*/

/* TO VIEW ENROLLMENTS */
void ViewEnrollments() 
{
    if (Count2 == 0) {
        printf("SORRY NO ENROLLMENTS.\n");
        return;
    }
    printf("-----LIST OF ENROLLMENTS -----\n");
    for (uint16_t i=0;i<Count2;i++) 
    {
        Enrollment *t = &e[i];
        printf("STUDENT ID: %d ,NAME: %s , COURSE ID: %d\n",t->stdId, t->stdName, t->courseId);
    }
}

/* TO DELETE COURSE */
void DeleteCourse() 
{
    uint16_t id;
    printf("ENTER COURSE ID TO DELETE: ");
    scanf("%hd", &id);

    for (uint16_t i=0;i<Count1;i++) 
    {
        if (c[i].id==id) 
        {
            /*Here it will shifting the info right to left*/
            for (uint16_t j=i;j<Count1 - 1;j++) 
            {
                c[j]=c[j+1];// inputing next value into prev place
            }
            Count1--;
            printf("CONGRATULATION!!COURSE DELETED SUCCESSFULLY!\n");
            return;
        }
    }
    printf("COURSE NOT FOUND, SORRY!\n");
}

/* TO DELETE ENROLLMENT */
void DeleteEnrollment() 
{
    uint16_t std_id;//unsigned integer
    printf("ENTER STUDENT ID TO DELETE ENROLLMENT: ");
    scanf("%hd", &std_id);

    for (uint16_t i=0;i<Count2;i++) 
    {
        if (e[i].stdId == std_id) 
        {
            /*REDUCING COURSE ENROLLED COUNT*/
            for (uint16_t j=0;j<Count2;j++)
            {
                if (c[j].id == e[i].courseId) 
                {
                    c[j].enrolled--;
                    break;
                }
            }
            /*SHIFTING LEFT*/
            for (uint16_t k=i;k<Count2 -1;k++) 
            {
                e[k] = e[k+1];
            }
            Count2--;
            printf("HURRAY!!ENROLLMENT DELETED SUCCESSFULLY!\n");
            return;
        }
    }
    printf("ENROLLMENT NOT FOUND!!!\n");
}

/* SEARCHING COURSE */
void SearchCourse() 
{
    uint16_t id;
    printf("ENTER COURSE ID TO SEARCH: ");
    scanf("%hd", &id);//assigning the value of courseid

    for (uint16_t i=0;i<Count1;i++) 
    {
        if (c[i].id == id) 
        {
            Course *p = &c[i];// declaring a pointer to point array element
            printf("YEAH, YOUR HAS BEEN FOUND \n ID: %d ,NAME: %s ,FACULTY: %s ,CAPACITY_OF_SEAT: %d ,ENROLLED: %d\n",p->id, p->name, p->faculty, p->capacity_of_seat, p->enrolled);
            return;
        }
    }
    printf("SO SORRY YOUR COURSE HAS NOT BEEN FOUND!\n");
}

/* SEARCHING ENROLLMENT */
void SearchEnrollment() 
{
    uint16_t std_id;
    printf("ENTER STUDENT ID TO SEARCH: ");
    scanf("%hd", &std_id);//ASSIGNING THE ID OF A STUDENT TO CHECKING IN THE ENROLLMENT LIST

    for (uint16_t i=0;i<Count2;i++) 
    {
        if (e[i].stdId==std_id) 
        {
            Enrollment *o = &e[i];
            printf("ENROLLMENT HAS BEEN FOUND!!\n! STUDENT ID: %d ,NAME: %s ,COURSE ID: %d\n",o->stdId,o->stdName,o->courseId);
            return;
        }
    }
    printf("ENROLLMENT NOT FOUND!\n");
}//tahsin saraf maisha

/* | Following code is developed by
   |  Name: Sultan Mahmud
   |  ID: 2024-3-60-294
*/

// declaring the structure for exam schedule
exam examS;

//Menu Otpions for exam schedule
void examAndGrade(){

    while (1) {
        printf("\t\tAvailable Options:\n\n");
        printf("\t\t\t1. Exam Schedule\n");
        printf("\t\t\t2. Grade Report\n");
        printf("\t\t\t3. Return\n");
        printf("\t\t\t0. Exit\n\n");

        printf("\t\tSelect your proferable option: ");
        scanf("%hd",&choice);

        switch ((MenuChoice)choice) {
            case c1: system("cls"); examSchedule(); 
            break;
            case c2: system("cls"); gradeReport(); 
            break;
            case c3: system("cls"); return;
            case c0: system("cls"); printf("\n\n\t\t\tHave a great day ahead..."); printf("\n\n\n");
            exit(0);
            default: 
            system("cls");
            printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
            break;
        }
    }

}

// Functions for Exam Schedule

// User input for exam schedule
FILE *examFile;

void examSchedule(){

    examFile = fopen("exam.txt","w");

    while(1){

        printf("\t\tOptions for Exam Schedule:\n\n");
        printf("\t\t\t1. Add a new Exam Schedule\n");
        printf("\t\t\t2. Edit existing Exam Schedule\n");
        printf("\t\t\t3. View Any Exam Schedule\n");
        printf("\t\t\t4. Delete Any Exam Schedule\n");
        printf("\t\t\t5. Exam Schedule Status\n");
        printf("\t\t\t6. Return\n");
        printf("\t\t\t0. Exit\n\n");
        printf("\t\tNow select your preferable option: ");
        scanf("%hd",&choice);
    
        switch ((MenuChoice)choice){
            case c1:
                system("cls"); 
                addExamSchedule();
                break;
            case c2:
                system("cls"); 
                editExamSchedule();
                break;
            case c3:
                system("cls"); 
                viewExamSchedule();
                break;
            case c4:
                system("cls"); 
                deleteExamSchedule();
                break;
            case c5:
                system("cls"); 
                isPublishedES();
                break;;
            case c6:
                system("cls");
                return;
            case c0: 
                system("cls");
                printf("\n\n\t\t\tHave a great day ahead...");
                printf("\n\n\n");
                exit(0);
            default: 
                system("cls");
                printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
                break;
        }
    }
    
}


// Add new exam schedule
void addExamSchedule(){

    examFile = fopen("exam.txt","a+");

    printf("\n\n\t\tSchedule the upcoming exams");
    printf("\n\n\t\tWrite the course code to add: ");
    scanf("%s",examS.courseCode);
    fprintf(examFile, examS.courseCode);
    fprintf(examFile," | ");
    printf("\t\tType the Date ( Format: DD/MM/YEAR ): ");
    scanf("%s",examS.date);
    fprintf(examFile, examS.date);
    fprintf(examFile," | ");
    printf("\t\tType the Time ( Format: 10:00 AM ): ");
    scanf("%s",examS.time);
    fprintf(examFile, examS.time);
    fprintf(examFile,"\n");
    fclose(examFile);
    system("cls");
    printf("\n\n\t\tExam for %s has been scheduled successfully!!\n\n",examS.courseCode);

    memset(&examS,0,sizeof(struct examSchedule));

}

// Edit or Modify the Exam Schedule
void editExamSchedule(){  

    if((examFile = fopen("exam.txt","a+")) == NULL){
        printf("\n\n\t\tNo exam is scheduled to be modified!");
    } else {
        printf("\n\t\tEdit or Modify the scheduled exams");
        char c[12];
        printf("\n\n\t\t\tWrite the course code to edit: ");
        scanf("%s",c);
        
        if(strcmp(c, examS.courseCode) == 0){
            printf("\n\n\t\tType the New Date ( Format: DD/MM/YEAR ): ");
            scanf("%s",examS.date);
            printf("\t\tType the New Time ( Format: 10:00 AM ): ");
            scanf("%s",examS.time);

            system("cls");
            printf("\n\n\t\tExam time has been edited for %s sucessfully\n\n",examS.courseCode);
        } else {
            system("cls");
            printf("\n\n\t\tThere isn't any scheduled exam for %s course\n\n",examS.courseCode);
        }
    }
    
    fclose(examFile);
    
}

// View Any Schdeduled Exams
void viewExamSchedule(){

    memset(&examS,0,sizeof(struct examSchedule));

    if((examFile = fopen("exam.txt","a+")) != NULL){
        fread(&examS,sizeof(struct examSchedule),1,examFile);
        printf("\n\n\t\t Course Code\t|\tExam Date\t|\tExam Time\n\n");
        printf("\t\t%s %s %s\n",examS.courseCode, examS.date,examS.time);
    } else {
        printf("\n\n\t\tNo exam is scheduled for now!");
    }

    fclose(examFile);

}

// Delete any scheduled Exams
void deleteExamSchedule(){

}

// Check Exam Schedule is published or not
void isPublishedES(){

}

// declaring the structure for grade
struct gradeDetails grades;

// functions for grade
// User input for grade
void gradeReport(){
    
    while(1){
        printf("\t\tOptions Grade Report:\n\n");
        printf("\t\t\t1. View Grade Report\n");
        printf("\t\t\t2. Edit Grade Report\n");
        printf("\t\t\t3. Pubish Grade Report\n");
        printf("\t\t\t4. Grade Report Status\n");
        printf("\t\t\t5. Return\n");
        printf("\t\t\t0. Exit");
        printf("\t\tNow select your preferable option: ");
        scanf("%hd",&choice);
    
        switch ((MenuChoice)choice){
            case 1:
                system("cls");
                viewGrade();
                break;
            case 2:
                system("cls");
                editGrade();
                break;
            case 3:
                system("cls");
                publishGrade();
                break;
            case 4:
                system("cls");
                isPublishGrade();
                break;
            case 0:
                system("cls");
                return;
            default: 
                system("cls");
                printf("\n\n\t\t\tNot a valid choice. Kindly select again!\n\n");
                break;

        }
    }
}

// View Grade of any course
void viewGrade(){

}

// Edit grade of any course
void editGrade(){

}

// Publish Grade Report for all student
void publishGrade(){

}

// Check Grade Report is published or not
void isPublishGrade(){

}