#ifndef FACULTY_H
#define FACULTY_H

enum designation{
    LECTURER = 0;
    ASSISTANT_PROFESSOR,
    ASSOCIATE_PROFESSOR,
    PROFESSOR,
}

typedef struct faculty{
    char *name;
    int *id;
    char *designation;
} faculty;

#endif