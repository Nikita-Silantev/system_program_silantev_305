#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

void print_student(struct Student *s) {
    printf("  Name: %s | Age: %d | Grade: %.1f\n", s->name, s->age, s->grade);
}

void bump_grade(struct Student *s) {
    s->grade += 0.5f;
    if (s->grade > 5.0f) s->grade = 5.0f;
}

void apply_to_student(struct Student *s, void (*fn)(struct Student *)) {
    fn(s);
}

void run_then_show(struct Student *s,
                   void (*action)(struct Student *),
                   void (*show)(void (*)(struct Student *), struct Student *)) {
    show(action, s);
}

void call_and_print(void (*fn)(struct Student *), struct Student *s) {
    fn(s);
    print_student(s);
}

void swap_pointers(int **a, int **b) {
    int *tmp = *a;
    *a = *b;
    *b = tmp;
}

void write_students(struct Student *arr, int count, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        printf("Error: cannot open %s\n", filename);
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %d %.1f\n", arr[i].name, arr[i].age, arr[i].grade);
    }
    fclose(f);
    printf("Saved to %s\n", filename);
}

void copy_file(const char *from, const char *to) {
    FILE *fin = fopen(from, "r");
    if (fin == NULL) {
        printf("Error: cannot open %s\n", from);
        return;
    }
    FILE *fout = fopen(to, "w");
    if (fout == NULL) {
        printf("Error: cannot open %s\n", to);
        fclose(fin);
        return;
    }
    fprintf(fout, "=== copy of %s ===\n", from);
    char line[200];
    while (fgets(line, sizeof(line), fin)) {
        fputs(line, fout);
    }
    fclose(fin);
    fclose(fout);
    printf("Copied %s -> %s\n", from, to);
}

int main(void) {
    printf("--- Pointers ---\n");
    int x = 10, y = 20;
    int *px = &x;
    int *py = &y;
    printf("x=%d  y=%d\n", x, y);
    printf("px points to address %p, value = %d\n", (void *)px, *px);
    *px = 99;
    printf("After *px=99: x=%d\n", x);

    int **ppx = &px;
    printf("ppx -> px -> x = %d\n", **ppx);

    printf("\nBefore swap: px->%d  py->%d\n", *px, *py);
    swap_pointers(&px, &py);
    printf("After swap:  px->%d  py->%d\n", *px, *py);

    printf("\n--- Structs ---\n");
    struct Student students[3];

    strcpy(students[0].name, "Alice");
    students[0].age = 20;
    students[0].grade = 3.5f;

    strcpy(students[1].name, "Bob");
    students[1].age = 22;
    students[1].grade = 4.0f;

    strcpy(students[2].name, "Carol");
    students[2].age = 19;
    students[2].grade = 4.8f;

    printf("All students:\n");
    for (int i = 0; i < 3; i++) {
        apply_to_student(&students[i], print_student);
    }

    printf("\n--- Function pointer chain ---\n");
    printf("Bump grade of Alice then print:\n");
    run_then_show(&students[0], bump_grade, call_and_print);

    printf("\nBump grade of Bob then print:\n");
    run_then_show(&students[1], bump_grade, call_and_print);

    printf("\n--- Files ---\n");
    write_students(students, 3, "students.txt");
    copy_file("students.txt", "students_copy.txt");

    printf("\nRead back from students_copy.txt:\n");
    FILE *f = fopen("students_copy.txt", "r");
    if (f != NULL) {
        char line[200];
        while (fgets(line, sizeof(line), f)) {
            printf("  %s", line);
        }
        fclose(f);
    }

    return 0;
}
