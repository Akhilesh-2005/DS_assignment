#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 50
#define MAX_ASSIGNMENTS 100
#define MAX_STUDENTS 100

// Structures
typedef struct {
    int id;
    char name[100];
} Course;

typedef struct {
    int id;
    char title[100];
    int courseId;
    int maxScore;
} Assignment;

typedef struct {
    int id;
    char name[100];
    float grade;
    char feedback[1000];
    int assignmentId;
} StudentGrade;

typedef struct {
    int id;
    char name[100];
    char email[100];
} Student;

// Function prototypes
void addCourse(Course courses[], int *numCourses);
void addAssignment(Assignment assignments[], int *numAssignments, Course courses[], int numCourses);
void addStudent(Student students[], int *numStudents);
void assignGrade(StudentGrade grades[], int *numGrades, Assignment assignments[], int numAssignments, Student students[], int numStudents);
void generateReport(StudentGrade grades[], int numGrades, Student students[], int numStudents, Assignment assignments[], int numAssignments);

int main() {
    Course courses[MAX_COURSES];
    Assignment assignments[MAX_ASSIGNMENTS];
    Student students[MAX_STUDENTS];
    StudentGrade grades[MAX_ASSIGNMENTS]; // Assuming one grade per assignment
    int numCourses = 0;
    int numAssignments = 0;
    int numStudents = 0;
    int numGrades = 0;

    int choice;
    do {
        printf("\nStudent Grade Tracker\n");
        printf("1. Add Course\n");
        printf("2. Add Assignment\n");
        printf("3. Add Student\n");
        printf("4. Assign Grade\n");
        printf("5. Generate Report\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                addCourse(courses, &numCourses);
                break;
            case 2:
                addAssignment(assignments, &numAssignments, courses, numCourses);
                break;
            case 3:
                addStudent(students, &numStudents);
                break;
            case 4:
                assignGrade(grades, &numGrades, assignments, numAssignments, students, numStudents);
                break;
            case 5:
                generateReport(grades, numGrades, students, numStudents, assignments, numAssignments);
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 6);

    return 0;
}

void addCourse(Course courses[], int *numCourses) {
    if (*numCourses >= MAX_COURSES) {
        printf("Cannot add more courses. Maximum limit reached.\n");
        return;
    }

    printf("Enter course name: ");
    scanf(" %[^\n]", courses[*numCourses].name);
    courses[*numCourses].id = *numCourses + 1;
    (*numCourses)++;
    printf("Course added successfully.\n");
}

void addAssignment(Assignment assignments[], int *numAssignments, Course courses[], int numCourses) {
    if (*numAssignments >= MAX_ASSIGNMENTS) {
        printf("Cannot add more assignments. Maximum limit reached.\n");
        return;
    }

    printf("Enter assignment title: ");
    scanf(" %[^\n]", assignments[*numAssignments].title);

    printf("Enter maximum score: ");
    scanf("%d", &assignments[*numAssignments].maxScore);

    printf("Enter course ID: ");
    int courseId;
    scanf("%d", &courseId);
    if (courseId < 1 || courseId > numCourses) {
        printf("Invalid course ID.\n");
        return;
    }
    assignments[*numAssignments].courseId = courseId;

    assignments[*numAssignments].id = *numAssignments + 1;
    (*numAssignments)++;
    printf("Assignment added successfully.\n");
}

void addStudent(Student students[], int *numStudents) {
    if (*numStudents >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    printf("Enter student name: ");
    scanf(" %[^\n]", students[*numStudents].name);

    printf("Enter student email: ");
    scanf(" %[^\n]", students[*numStudents].email);

    students[*numStudents].id = *numStudents + 1;
    (*numStudents)++;
    printf("Student added successfully.\n");
}

void assignGrade(StudentGrade grades[], int *numGrades, Assignment assignments[], int numAssignments, Student students[], int numStudents) {
    if (*numGrades >= numAssignments * numStudents) {
        printf("Cannot assign more grades. Maximum limit reached.\n");
        return;
    }

    printf("Enter student ID: ");
    int studentId;
    scanf("%d", &studentId);
    if (studentId < 1 || studentId > numStudents) {
        printf("Invalid student ID.\n");
        return;
    }

    printf("Enter assignment ID: ");
    int assignmentId;
    scanf("%d", &assignmentId);
    if (assignmentId < 1 || assignmentId > numAssignments) {
        printf("Invalid assignment ID.\n");
        return;
    }

    printf("Enter grade for assignment (out of %d): ", assignments[assignmentId - 1].maxScore);
    float grade;
    scanf("%f", &grade);
    if (grade < 0 || grade > assignments[assignmentId - 1].maxScore) {
        printf("Invalid grade. Grade must be between 0 and %d.\n", assignments[assignmentId - 1].maxScore);
        return;
    }

    printf("Enter feedback for assignment: ");
    scanf(" %[^\n]", grades[*numGrades].feedback);

    grades[*numGrades].id = *numGrades + 1;
    grades[*numGrades].assignmentId = assignmentId;
    grades[*numGrades].grade = grade;
    (*numGrades)++;
    printf("Grade assigned successfully.\n");
}

void generateReport(StudentGrade grades[], int numGrades, Student students[], int numStudents, Assignment assignments[], int numAssignments) {
    printf("\nGrade Report:\n");
    printf("Student ID\tStudent Name\tAssignment\tGrade\tFeedback\n");
    for (int i = 0; i < numGrades; i++) {
        printf("%d\t\t%s\t\t%s\t\t%.2f\t%s\n", students[grades[i].id - 1].id, students[grades[i].id - 1].name, assignments[grades[i].assignmentId - 1].title, grades[i].grade, grades[i].feedback);
    }
}
