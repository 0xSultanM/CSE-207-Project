#include "Attendence.h"

// Create a new attendance record
AttendanceRecord markAttendance(uint16_t studentId, uint16_t courseId, const char* date, AttendanceStatus status) {
    AttendanceRecord rec;
    rec.studentId = studentId;
    rec.courseId = courseId;
    strncpy(rec.date, date, Date_Len - 1);
    rec.date[Date_Len - 1] = '\0';
    rec.status = status;
    return rec;
}

// Create new node
Node_a* createNode(AttendanceRecord record) {
    Node_a* newNode = (Node_a*)malloc(sizeof(Node_a));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->record = record;
    newNode->next = NULL;
    return newNode;
}

// attendence menu

int attendanceMenu(Node_a** head) {
    int choice;
    uint16_t studentId, courseId;
    char date[Date_Len];
    int status;

    while (1) {
        printf("\n\t\t\t==== Attendance Management ====\n");
        printf("\t\t1. Add Attendance Record\n");
        printf("\t\t2. Update Attendance Status\n");
        printf("\t\t3. Display All Records\n");
        printf("\t\t4. Find Record by Student ID\n");
        printf("\t\t5. Count Present Students\n");
        printf("\t\t0. Back to Main Menu\n\n");

        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                system("cls");
                printf("\t\tEnter Student ID: ");
                scanf("%hu", &studentId);
                printf("\t\tEnter Course ID: ");
                scanf("%hu", &courseId);
                printf("\t\tEnter Date (YYYY-MM-DD): ");
                scanf("%s", date);
                printf("\t\tEnter Status (0=Absent, 1=Present): ");
                scanf("%d", &status);
                insertRecord(head, markAttendance(studentId, courseId, date, (status == 1 ? Present : Absent)));
                break;

            case 2:
                system("cls");
                printf("\t\tEnter Student ID: ");
                scanf("%hu", &studentId);
                printf("\t\tEnter New Status (0=Absent, 1=Present): ");
                scanf("%d", &status);
                if (updateAttendanceStatus(*head, studentId, (status == 1 ? Present : Absent)))
                    printf("\t\tAttendance updated successfully.\n");
                else
                    printf("\t\tStudent ID not found.\n");
                break;

            case 3:
                system("cls");
                printAllRecords(*head);
                break;

            case 4:
                system("cls");
                printf("\t\tEnter Student ID: ");
                scanf("%hu", &studentId);
                {
                    AttendanceRecord* rec = findRecordByStudentId(*head, studentId);
                    if (rec) printAttendanceRecord(rec);
                    else printf("\t\tRecord not found.\n");
                }
                break;

            case 5:
                system("cls");
                printf("\t\tTotal Present Students: %d\n", countPresent(*head));
                break;

            case 0:
                system("cls");
                return 0;

            default:
                system("cls");
                printf("\t\tInvalid choice!\n");
        }
    }
}

// Insert record into linked list
void insertRecord(Node_a** head, AttendanceRecord record) {
    Node_a* newNode = createNode(record);
    newNode->next = *head;
    *head = newNode;
}

// Print single record
void printAttendanceRecord(const AttendanceRecord* record) {
    printf("Student ID: %hu | Course ID: %hu | Date: %s | Status: %s\n",
           record->studentId,
           record->courseId,
           record->date,
           (record->status == Present ? "Present" : "Absent"));
}

// Print all records
void printAllRecords(Node_a* head) {
    Node_a* temp = head;
    if (!temp) {
        printf("No attendance records found.\n");
        return;
    }
    while (temp) {
        printAttendanceRecord(&temp->record);
        temp = temp->next;
    }
}

// Free linked list
void freelist(Node_a* head) {
    Node_a* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Find record by studentId
AttendanceRecord* findRecordByStudentId(Node_a* head, uint16_t studentId) {
    Node_a* temp = head;
    while (temp) {
        if (temp->record.studentId == studentId) {
            return &temp->record;
        }
        temp = temp->next;
    }
    return NULL;
}

// Count number of present students
int countPresent(Node_a* head) {
    int count = 0;
    Node_a* temp = head;
    while (temp) {
        if (temp->record.status == Present) count++;
        temp = temp->next;
    }
    return count;
}

// Update attendance status
int updateAttendanceStatus(Node_a* head, uint16_t studentId, AttendanceStatus newstatus) {
    Node_a* temp = head;
    while (temp) {
        if (temp->record.studentId == studentId) {
            temp->record.status = newstatus;
            return 1; // success
        }
        temp = temp->next;
    }
    return 0; // not found
}