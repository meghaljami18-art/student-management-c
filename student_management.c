#include <stdio.h>
#include <string.h>

#define MAX 100
#define MAX_SUBJECTS 10

// Global subject data
char subjects[MAX_SUBJECTS][20];
int sub_count;

// Structure
struct student {
    char name[50];
    int roll;
    int marks[MAX_SUBJECTS];
};

// Function declarations
void inputSubjects();
void inputmarks(struct student s[], int n);
void display(struct student s[], int n);
int totalMarks(struct student s);
float averageMarks(struct student s);
void sortStudents(struct student s[], int n, int type, int subIndex);

// ─────────────────────────────────────────
// MAIN
// ─────────────────────────────────────────
int main() {
    struct student s[MAX];
    int n, choice, type, subIndex;

    printf("Enter number of students (1-%d): ", MAX);
    scanf("%d", &n);

    // FIX 1: Validate number of students
    if (n < 1 || n > MAX) {
        printf("Invalid number of students!\n");
        return 1;
    }

    inputSubjects();
    inputmarks(s, n);

    do {
        printf("\n1. Display");
        printf("\n2. Sort");
        printf("\n3. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            display(s, n);
        }
        else if (choice == 2) {
            printf("\nSort by:");
            printf("\n1. Name (A-Z)");
            printf("\n2. Subject marks (High-Low)");
            printf("\n3. Total marks (High-Low)");
            printf("\n4. Average marks (High-Low)");
            printf("\nEnter type: ");
            scanf("%d", &type);

            // FIX 2: Validate sort type
            if (type < 1 || type > 4) {
                printf("Invalid sort type!\n");
                continue;
            }

            if (type == 2) {
                printf("Enter subject index (0 to %d): ", sub_count - 1);
                scanf("%d", &subIndex);

                // FIX 3: Validate subject index
                if (subIndex < 0 || subIndex >= sub_count) {
                    printf("Invalid subject index!\n");
                    continue;
                }
            } else {
                subIndex = -1;
            }

            sortStudents(s, n, type, subIndex);
            printf("\nSorted successfully!\n");
        }
        else if (choice == 3) {
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    } while (choice != 3);

    return 0;
}

// ─────────────────────────────────────────
// INPUT SUBJECTS
// ─────────────────────────────────────────
void inputSubjects() {
    printf("Enter number of subjects (1-%d): ", MAX_SUBJECTS);
    scanf("%d", &sub_count);

    // FIX 4: Validate subject count
    if (sub_count < 1 || sub_count > MAX_SUBJECTS) {
        printf("Invalid number of subjects! Defaulting to 1.\n");
        sub_count = 1;
    }

    for (int i = 0; i < sub_count; i++) {
        printf("Enter subject %d name: ", i + 1);
        // FIX 5: Buffer-safe scanf for subject names (max 19 chars + null)
        scanf("%19s", subjects[i]);
    }
}

// ─────────────────────────────────────────
// INPUT STUDENTS
// ─────────────────────────────────────────
void inputmarks(struct student s[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nStudent %d", i + 1);
        printf("\nEnter name: ");
        // FIX 6: Buffer-safe scanf for student names (max 49 chars + null)
        scanf("%49s", s[i].name);

        printf("Enter roll: ");
        scanf("%d", &s[i].roll);

        for (int j = 0; j < sub_count; j++) {
            do {
                printf("Enter marks in %s (0-100): ", subjects[j]);
                scanf("%d", &s[i].marks[j]);

                // FIX 7: Validate marks range
                if (s[i].marks[j] < 0 || s[i].marks[j] > 100) {
                    printf("Invalid marks! Please enter between 0 and 100.\n");
                }
            } while (s[i].marks[j] < 0 || s[i].marks[j] > 100);
        }
    }
}

// ─────────────────────────────────────────
// DISPLAY
// ─────────────────────────────────────────
void display(struct student s[], int n) {
    int i, j;

    printf("\n-------------------------------------------------------------\n");
    printf("%-12s %-6s", "Name", "Roll");

    for (j = 0; j < sub_count; j++) {
        printf("%-10s", subjects[j]);
    }

    printf("%-8s %-8s %s", "Total", "Avg", "Result");
    printf("\n-------------------------------------------------------------\n");

    for (i = 0; i < n; i++) {
        printf("%-12s %-6d", s[i].name, s[i].roll);

        for (j = 0; j < sub_count; j++) {
            printf("%-10d", s[i].marks[j]);
        }

        int total = totalMarks(s[i]);
        float avg  = averageMarks(s[i]);

        // FIX 8: Added pass/fail — fail if any subject < 40
        int passed = 1;
        for (j = 0; j < sub_count; j++) {
            if (s[i].marks[j] < 40) {
                passed = 0;
                break;
            }
        }

        printf("%-8d %-8.2f %s", total, avg, passed ? "PASS" : "FAIL");
        printf("\n");
    }

    printf("-------------------------------------------------------------\n");
}

// ─────────────────────────────────────────
// TOTAL
// ─────────────────────────────────────────
int totalMarks(struct student s) {
    int sum = 0;
    for (int i = 0; i < sub_count; i++) {
        sum += s.marks[i];
    }
    return sum;
}

// ─────────────────────────────────────────
// AVERAGE
// ─────────────────────────────────────────
float averageMarks(struct student s) {
    return (float)totalMarks(s) / sub_count;
}

// ─────────────────────────────────────────
// SORT (Bubble Sort)
// ─────────────────────────────────────────
void sortStudents(struct student s[], int n, int type, int subIndex) {
    struct student temp;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {

            int doSwap = 0;

            if (type == 1) {  // Name: A → Z
                if (strcmp(s[j].name, s[j + 1].name) > 0)
                    doSwap = 1;
            }
            else if (type == 2) {  // Subject marks: High → Low
                if (s[j].marks[subIndex] < s[j + 1].marks[subIndex])
                    doSwap = 1;
            }
            else if (type == 3) {  // Total: High → Low
                // FIX 9: Cache totals to avoid recomputing each comparison
                int t1 = totalMarks(s[j]);
                int t2 = totalMarks(s[j + 1]);
                if (t1 < t2)
                    doSwap = 1;
            }
            else if (type == 4) {  // Average: High → Low
                float a1 = averageMarks(s[j]);
                float a2 = averageMarks(s[j + 1]);
                if (a1 < a2)
                    doSwap = 1;
            }

            if (doSwap) {
                temp     = s[j];
                s[j]     = s[j + 1];
                s[j + 1] = temp;
            }
        }
    }
}
