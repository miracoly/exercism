#include "grade_school.h"
#include <string.h>
#include <stdlib.h>

static bool elem(const roster_t* roster, const char name[static 1]) {
    for (size_t i = 0; i < roster->count && i < MAX_STUDENTS; ++i) {
        if (!strcmp(roster->students[i].name, name))
            return true;
    }
    return false;
}

static int compare_student(const void* student_1, const void* student_2) {
    const student_t* s1 = student_1;
    const student_t* s2 = student_2;

    if (s1->grade - s2->grade) return s1->grade - s2->grade;
    return strcmp(s1->name, s2->name);
}

void init_roster(roster_t* roster) {
    roster->count = 0;
    memset(roster->students, 0, sizeof(roster->students));
}

bool add_student(roster_t* roster, const char name[static 1], uint8_t grade) {
    if (roster->count >= MAX_STUDENTS) return false;
    if (elem(roster, name)) return false;

    student_t student = {.grade = grade};
    strncpy(student.name, name, MAX_NAME_LENGTH - 1);
    student.name[MAX_NAME_LENGTH - 1] = '\0';

    roster->students[roster->count] = student;
    roster->count++;

    qsort(roster->students, roster->count, sizeof(student_t), compare_student);

    return true;
}

roster_t get_grade(const roster_t* roster, uint8_t desired_grade) {
    roster_t filtered = {0};
    init_roster(&filtered);

    for (size_t i = 0; i < roster->count; ++i) {
        if (roster->students[i].grade == desired_grade) {
            add_student(&filtered, roster->students[i].name, roster->students[i].grade);
        }
    }
    return filtered;
}

