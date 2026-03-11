#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float grade;
} Student;


void add_students(Student **students, int *count);
void display_students(Student *students, int count);
void sort_students(Student *students, int count);
void calculate_average(Student *students, int count);
void find_top_student(Student *students, int count);
void grade_distribution(Student *students, int count);


int main() {

    printf("Student ID: 54321\n");
    printf("Analysis Function: Grade Distribution\n\n");


    Student dataset[10] = {
        {1, "Alice", 85},
        {2, "Bob", 92},
        {3, "Charlie", 78},
        {4, "Diana", 88},
        {5, "Ethan", 95},
        {6, "Fiona", 67},
        {7, "George", 73},
        {8, "Hannah", 81},
        {9, "Isaac", 90},
        {10, "Julia", 76}
    };


    int student_count = 10;

    Student *students = malloc(student_count * sizeof(Student));

    if (students == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }


    for (int i = 0; i < student_count; i++) {
        students[i] = dataset[i];
    }


    int choice;

    void (*operations[])(Student*, int) = {
        display_students,
        sort_students,
        calculate_average,
        find_top_student,
        grade_distribution
    };


    while (1) {

        printf("\n===== Student Record System =====\n");
        printf("1. Add Students\n");
        printf("2. Display Students\n");
        printf("3. Sort Students by Grade\n");
        printf("4. Calculate Average Grade\n");
        printf("5. Find Top Student\n");
        printf("6. Grade Distribution Analysis\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);


        if (choice == 1) {

            add_students(&students, &student_count);

        }

        else if (choice >= 2 && choice <= 6) {

            operations[choice - 2](students, student_count);

        }

        else if (choice == 7) {

            free(students);
            printf(" Exiting program.\n");
            break;

        }

        else {

            printf("Invalid choice.\n");

        }

    }

    return 0;
}




void add_students(Student **students, int *count) {

    int n;

    printf("How many students do you want to add? ");
    scanf("%d", &n);

    *students = realloc(*students, (*count + n) * sizeof(Student));

    if (*students == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    Student *ptr = *students + *count;

    for (int i = 0; i < n; i++) {

        printf("\nStudent %d\n", *count + i + 1);

        printf("Enter ID: ");
        scanf("%d", &ptr->id);

        printf("Enter Name: ");
        scanf("%s", ptr->name);

        printf("Enter Grade: ");
        scanf("%f", &ptr->grade);

        ptr++;
    }

    *count += n;
}



void display_students(Student *students, int count) {

    printf("\nID\tName\tGrade\n");

    Student *ptr = students;

    for (int i = 0; i < count; i++) {

        printf("%d\t%s\t%.2f\n", ptr->id, ptr->name, ptr->grade);
        ptr++;

    }

}



void sort_students(Student *students, int count) {

    for (int i = 0; i < count - 1; i++) {

        for (int j = 0; j < count - i - 1; j++) {

            if (students[j].grade < students[j + 1].grade) {

                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;

            }

        }

    }

    printf("Students sorted by grade (highest first).\n");

}




void calculate_average(Student *students, int count) {

    float sum = 0;

    Student *ptr = students;

    for (int i = 0; i < count; i++) {

        sum += ptr->grade;
        ptr++;

    }

    printf("Average Grade: %.2f\n", sum / count);

}



void find_top_student(Student *students, int count) {

    Student *top = students;
    Student *ptr = students + 1;

    for (int i = 1; i < count; i++) {

        if (ptr->grade > top->grade) {
            top = ptr;
        }

        ptr++;
    }

    printf("Top Student: %s (ID %d) with Grade %.2f\n",
           top->name, top->id, top->grade);

}




void grade_distribution(Student *students, int count) {

    int A=0, B=0, C=0, D=0, F=0;

    Student *ptr = students;

    for (int i = 0; i < count; i++) {

        if (ptr->grade >= 90)
            A++;
        else if (ptr->grade >= 80)
            B++;
        else if (ptr->grade >= 70)
            C++;
        else if (ptr->grade >= 60)
            D++;
        else
            F++;

        ptr++;

    }

    printf("\nGrade Distribution\n");
    printf("A (90-100): %d\n", A);
    printf("B (80-89): %d\n", B);
    printf("C (70-79): %d\n", C);
    printf("D (60-69): %d\n", D);
    printf("F (<60): %d\n", F);

}