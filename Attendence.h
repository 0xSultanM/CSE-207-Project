#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define Date_Len 12

typedef enum {
    Absent = 0,
    Present = 1
} AttendanceStatus;

typedef struct {
    uint16_t studentId;
    uint16_t courseId;
    char date[Date_Len];
    AttendanceStatus status;
} AttendanceRecord;

typedef struct Node_a {
    AttendanceRecord record;
    struct Node_a* next;
} Node_a;

AttendanceRecord markAttendance(uint16_t studentId, uint16_t courseId, const char* date, AttendanceStatus status);
Node_a* createNode(AttendanceRecord record);

int attendanceMenu(Node_a** head);
void insertRecord(Node_a** head, AttendanceRecord record);
void printAttendanceRecord(const AttendanceRecord* record);
void printAllRecords(Node_a* head);
void freelist(Node_a* head);
AttendanceRecord* findRecordByStudentId(Node_a* head, uint16_t studentId);
int countPresent(Node_a* head);
int updateAttendanceStatus(Node_a* head, uint16_t studentId, AttendanceStatus newstatus);

#endif