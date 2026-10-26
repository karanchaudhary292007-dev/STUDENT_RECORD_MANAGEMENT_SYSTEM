/*
 * ============================================================
 *  Project  : Student Record Management System
 *  Language : C (C99)
 *  Author   : Kunal Chaudhary (UID: 26BCA10241)
 *  Date     : 26 October 2026
 *  Compiler : GCC
 *
 *  A simple menu-driven program that stores student records
 *  in an array of structures. It supports adding, displaying,
 *  searching, updating and deleting records, and finding the
 *  topper of the class.
 * ============================================================
 */

#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define NUM_SUBJECTS 3

/* ---------- Structure that stores one student ---------- */
struct Student {
    int   roll;
    char  name[40];
    float marks[NUM_SUBJECTS];
    float total;
    float percentage;
    char  grade;
};

struct Student students[MAX_STUDENTS];
int count = 0;

/* ---------- Helper: decide grade from percentage ---------- */
char findGrade(float p) {
    if (p >= 90) return 'A';
    else if (p >= 75) return 'B';
    else if (p >= 60) return 'C';
    else if (p >= 40) return 'D';
    else return 'F';
}

/* ---------- Helper: find index of a roll number ---------- */
int findIndex(int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll)
            return i;
    }
    return -1;
}

/* ---------- Helper: calculate total, percentage, grade ---------- */
void calculateResult(struct Student *s) {
    s->total = 0;
    for (int i = 0; i < NUM_SUBJECTS; i++)
        s->total += s->marks[i];
    s->percentage = s->total / NUM_SUBJECTS;
    s->grade = findGrade(s->percentage);
}

/* ---------- Module 1: Add a student ---------- */
void addStudent(void) {
    if (count >= MAX_STUDENTS) {
        printf("Record list is full!\n");
        return;
    }

    struct Student s;
    printf("Enter roll number : ");
    scanf("%d", &s.roll);

    if (findIndex(s.roll) != -1) {
        printf("Roll number already exists!\n");
        return;
    }

    printf("Enter name        : ");
    scanf(" %39[^\n]", s.name);

    for (int i = 0; i < NUM_SUBJECTS; i++) {
        printf("Enter marks of subject %d : ", i + 1);
        scanf("%f", &s.marks[i]);
    }

    calculateResult(&s);
    students[count++] = s;
    printf("Student record added successfully.\n");
}

/* ---------- Module 2: Display all students ---------- */
void displayAll(void) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    printf("\n%-6s %-18s %-6s %-6s %-6s %-10s %-5s\n",
           "Roll", "Name", "M1", "M2", "M3", "Percent", "Grade");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-6d %-18s %-6.0f %-6.0f %-6.0f %-10.2f %-5c\n",
               students[i].roll, students[i].name,
               students[i].marks[0], students[i].marks[1],
               students[i].marks[2], students[i].percentage,
               students[i].grade);
    }
}

/* ---------- Module 3: Search a student ---------- */
void searchStudent(void) {
    int roll;
    printf("Enter roll number to search : ");
    scanf("%d", &roll);

    int i = findIndex(roll);
    if (i == -1) {
        printf("Student with roll number %d not found.\n", roll);
        return;
    }

    printf("\nRecord found:\n");
    printf("Roll       : %d\n", students[i].roll);
    printf("Name       : %s\n", students[i].name);
    printf("Total      : %.0f / %d\n", students[i].total, NUM_SUBJECTS * 100);
    printf("Percentage : %.2f%%\n", students[i].percentage);
    printf("Grade      : %c\n", students[i].grade);
}

/* ---------- Module 4: Update marks ---------- */
void updateStudent(void) {
    int roll;
    printf("Enter roll number to update : ");
    scanf("%d", &roll);

    int i = findIndex(roll);
    if (i == -1) {
        printf("Student with roll number %d not found.\n", roll);
        return;
    }

    for (int j = 0; j < NUM_SUBJECTS; j++) {
        printf("Enter new marks of subject %d : ", j + 1);
        scanf("%f", &students[i].marks[j]);
    }
    calculateResult(&students[i]);
    printf("Record updated successfully.\n");
}

/* ---------- Module 5: Delete a student ---------- */
void deleteStudent(void) {
    int roll;
    printf("Enter roll number to delete : ");
    scanf("%d", &roll);

    int i = findIndex(roll);
    if (i == -1) {
        printf("Student with roll number %d not found.\n", roll);
        return;
    }

    for (int j = i; j < count - 1; j++)
        students[j] = students[j + 1];
    count--;
    printf("Record deleted successfully.\n");
}

/* ---------- Module 6: Show the topper ---------- */
void showTopper(void) {
    if (count == 0) {
        printf("No records found.\n");
        return;
    }

    int top = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].percentage > students[top].percentage)
            top = i;
    }
    printf("\nTopper of the class: %s (Roll %d) with %.2f%%\n",
           students[top].name, students[top].roll, students[top].percentage);
}

/* ---------- Main menu ---------- */
int main(void) {
    int choice;

    printf("=====================================\n");
    printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("=====================================\n");

    do {
        printf("\n1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student Marks\n");
        printf("5. Delete Student\n");
        printf("6. Show Topper\n");
        printf("7. Exit\n");
        printf("Enter your choice : ");

        if (scanf("%d", &choice) != 1)
            break;

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: showTopper();    break;
            case 7: printf("\nThank you for using the system. Goodbye!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
