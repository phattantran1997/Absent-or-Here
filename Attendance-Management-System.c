#include <stdio.h>
#include <string.h>
#include <time.h>

struct Student {
    char fullName[150]; // Store full name including first, middle, and last name
    int rollNo;
    char attendanceStatus;
};

void enterTeacherAndSubject(char teacherName[], char subject[]) {
    printf("Enter the teacher's name: ");
    scanf(" %[^\n]", teacherName);

    printf("Enter the subject: ");
    scanf(" %[^\n]", subject);
}

void enterStudentInfo(struct Student students[], int numStudents) {
    for (int i = 0; i < numStudents; i++) {
        printf("Enter full name of student %d : ", i + 1);
        scanf(" %[^\n]", students[i].fullName);

        // Display the student's name and ask for their roll number
        printf("Enter roll number for %s: ", students[i].fullName);
        scanf("%d", &students[i].rollNo);
    }
}

int main() {
    int numStudents;
    char teacherName[50];
    char subject[50];
    int continueAttendance = 1; // Initialize to 1 to start the program

    while (continueAttendance) {
        // Step 1: Enter teacher name and subject
        enterTeacherAndSubject(teacherName, subject);

        // Step 2: Enter the number of students in class
        printf("Enter the number of students in the class: ");
        scanf("%d", &numStudents);

        struct Student students[numStudents];

        // Step 3: Enter student names and roll numbers
        enterStudentInfo(students, numStudents);

        // Get current date and time
        time_t currentTime;
        struct tm *localTime;

        time(&currentTime);
        localTime = localtime(&currentTime);

        // Step 4: Create attendance data text file for the subject
        char filename[50];
        snprintf(filename, sizeof(filename), "%s_attendance.txt", subject);

        FILE *file = fopen(filename, "w"); // Create a new file (overwrite if it exists)
        if (file == NULL) {
            printf("Error opening/creating file.\n");
            return 1;
        }

        // Write the subject header and other details
        fprintf(file, "Teacher Name: %s\n", teacherName);
        fprintf(file, "Subject: %s\n", subject);
        fprintf(file, "Attendance Date: %02d/%02d/%d\n\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);

        // Loop through students and take attendance one by one
        for (int i = 0; i < numStudents; i++) {
            // Display student name and roll number
            printf("%s [%d] is ", students[i].fullName, students[i].rollNo);

            printf("present (P) or absent (A) for %s? ", subject);
            scanf(" %c", &students[i].attendanceStatus);

            // Display student name and roll number along with attendance status in the file
            fprintf(file, "Student: %s [%d], Attendance: %s\n",
                    students[i].fullName, students[i].rollNo,
                    (students[i].attendanceStatus == 'P' || students[i].attendanceStatus == 'p') ? "Present" : "Absent");
        }

        fclose(file);
        printf("\nAttendance data for %s has been recorded in %s.\n", subject, filename);

        // Ask if the user wants to continue
        printf("Do you want to continue (1 for Yes, 0 for No)? ");
        scanf("%d", &continueAttendance);
    }

    return 0;
}