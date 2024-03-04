#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employee.dat"
#define MAX_NAME_LENGTH 50
struct Employee {
    int id;
    char name[MAX_NAME_LENGTH];
    float salary;
};
void addEmployee();
void displayEmployee(int id);
void updateEmployee(int id);
void deleteEmployee(int id);

int main() {
    int choice;
    do {
        printf("\nEmployee Database\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee\n");
        printf("3. Update Employee\n");
        printf("4. Delete Employee\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                addEmployee();
                break;
            case 2: {
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                displayEmployee(id);
                break;
            }
            case 3: {
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                updateEmployee(id);
                break;
            }
            case 4: {
                int id;
                printf("Enter employee ID: ");
                scanf("%d", &id);
                deleteEmployee(id);
                break;
            }
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);

    return 0;
}
void addEmployee() {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "ab");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    printf("Enter employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter employee name: ");
    scanf(" %[^\n]", emp.name);
    printf("Enter employee salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(struct Employee), 1, file);
    fclose(file);
}
void displayEmployee(int id) {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {
            printf("Employee ID: %d\n", emp.id);
            printf("Employee Name: %s\n", emp.name);
            printf("Employee Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee with ID %d not found.\n", id);

    fclose(file);
}
void updateEmployee(int id) {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "r+b");
    if (file == NULL) {
        printf("Error opening file for reading and writing.\n");
        return;
    }
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id == id) {
            printf("Enter new employee name: ");
            scanf(" %[^\n]", emp.name);
            printf("Enter new employee salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR);
            fwrite(&emp, sizeof(struct Employee), 1, file);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Employee with ID %d not found.\n", id);

    fclose(file);
}
void deleteEmployee(int id) {
    struct Employee emp;
    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    FILE *tempFile = fopen("temp.dat", "wb");
    if (tempFile == NULL) {
        printf("Error opening temporary file.\n");
        fclose(file);
        return;
    }
    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file) == 1) {
        if (emp.id != id) {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Employee with ID %d deleted successfully.\n", id);
    else
        printf("Employee with ID %d not found.\n", id);
}
