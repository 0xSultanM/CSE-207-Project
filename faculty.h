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
    char designation;
} faculty;

<<<<<<< HEAD
void add_faculty();
void remove_faculty();
void assign_course();
void remove_couser();
void add_preadvising();
void remove_preadvising();

void nothing();

=======
>>>>>>> 8fab97234588dbd0700f28c136df789a3f525e89
#endif