#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EMP 100

/* prints payslip for the requested employee */
void printSalary(int empId[], char employeeName[][32], int basic[], int pf[], int insurance[], float net[], int index) {
    printf("\n\033[1;32m=============================================\033[0m\n");
    printf("              \033[1;32mSALARY SLIP TABLE\033[0m              \n");
    printf("\033[1;32m=============================================\033[0m\n");
    printf("| %-15s | %-20s |\n", "Field", "Value");
    printf("=============================================\033[0m\n");
    printf("| %-15s | %-20d |\n", "Employee ID", empId[index]);
    printf("| %-15s | %-20s |\n", "Name", employeeName[index]);
    printf("| %-15s | %-20d |\n", "Basic Salary", basic[index]);
    printf("| %-15s | %-20d |\n", "Provident Fund", pf[index]);
    printf("| %-15s | %-20d |\n", "Insurance", insurance[index]);
    printf("| %-15s | %-20.2f |\n", "Net Salary", net[index]);
    printf("=============================================\n\n");
}

/* display all employee records in table form */
void displayAll(int empId[], char employeeName[][32], int basic[], int pf[], int insurance[], float net[], int num) {
    printf("\n====================================================================================================================\n");
    printf("| %-10s | %-20s | %-12s | %-12s | %-12s | %-12s |\n",
           "Emp. ID", "Employee Name", "Basic", "PF", "Insurance", "Net Salary");
    printf("====================================================================================================================\n");

    for (int i = 0; i < num; i++) {
        printf("| %-10d | %-20s | %-12d | %-12d | %-12d | %-12.2f |\n",
               empId[i], employeeName[i], basic[i], pf[i], insurance[i], net[i]);
    }

    printf("====================================================================================================================\n");
}

//login function
int login() {
    char username[20], password[20];
    int attempts = 3;

    while (attempts > 0) {
        printf("\n\033[1;31m===== ADMIN LOGIN =====\033[0m\n");
        printf("Username: ");
        scanf("%s", username);
        printf("Password: ");
        scanf("%s", password);

        if (strcmp(username, "Admin") == 0 && strcmp(password, "12345") == 0) {
            printf("\nLogin successful! Welcome, %s.\n", username);
            return 1;
        } else {
            attempts--;
            printf("Invalid credentials! Attempts left: %d\n", attempts);
        }
    }

    printf("\n\033[1;31mToo many failed attempts. Exiting program.\033[0m\n");
    return 0;
}

/* delete an employee record by ID */
void deleteEmployee(int empId[], char employeeName[][32], int basic[], int pf[], int insurance[], float net[], int *num) {
    int empID, found = 0;

    printf("\nEnter Employee ID to delete: ");
    scanf("%d", &empID);

    for (int i = 0; i < *num; i++) {
        if (empId[i] == empID) {
            found = 1;

            // Shift all elements up by one to remove this record
            for (int j = i; j < *num - 1; j++) {
                empId[j] = empId[j + 1];
                strcpy(employeeName[j], employeeName[j + 1]);
                basic[j] = basic[j + 1];
                pf[j] = pf[j + 1];
                insurance[j] = insurance[j + 1];
                net[j] = net[j + 1];
            }

            (*num)--; // reduce the total count
            printf("\nEmployee ID %d deleted successfully!\n", empID);
            break;
        }
    }

    if (!found) {
        printf("No Record Found for Employee ID %d!\n", empID);
    }
}

int main() {
    int empId[MAX_EMP], basic[MAX_EMP], pf[MAX_EMP], insurance[MAX_EMP];
    float net[MAX_EMP];
    char employeeName[MAX_EMP][32];
    int num = 0, i, ch, choice, empID, updateChoice, found;

    if (!login()) return 0;

    printf("\n==== PAYROLL PROCESSING SYSTEM ====\n");
    printf("\nEnter the number of employees: ");
    scanf("%d", &num);

    for (i = 0; i < num; i++) {
        printf("\nEmployee ID: ");
        scanf("%d", &empId[i]);
        getchar();
        printf("Employee Name: ");
        fgets(employeeName[i], 32, stdin);
        employeeName[i][strcspn(employeeName[i], "\n")] = '\0';
        printf("Basic Salary: ");
        scanf("%d", &basic[i]);
        printf("Provident Fund: ");
        scanf("%d", &pf[i]);
        printf("Insurance: ");
        scanf("%d", &insurance[i]);
        net[i] = basic[i] - (pf[i] + insurance[i]);
    }

    while (1) {
        printf("\n==== PAYROLL PROCESSING SYSTEM ====\n");
        printf("1) SHOW ALL RECORDS\n");
        printf("2) ADD NEW EMPLOYEE RECORD\n");
        printf("3) PRINT THE SALARY SLIP\n");
        printf("4) UPDATE EMPLOYEE RECORD\n");
        printf("5) DELETE EMPLOYEE RECORD\n");
        printf("6) EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayAll(empId, employeeName, basic, pf, insurance, net, num);
                break;

            case 2:
                if (num >= MAX_EMP) {
                    printf("Cannot add more employees! Maximum reached.\n");
                    break;
                }
                i = num++;
                printf("\nEmployee ID: ");
                scanf("%d", &empId[i]);
                getchar();
                printf("Employee Name: ");
                fgets(employeeName[i], 32, stdin);
                employeeName[i][strcspn(employeeName[i], "\n")] = '\0';
                printf("Basic Salary: ");
                scanf("%d", &basic[i]);
                printf("Provident Fund: ");
                scanf("%d", &pf[i]);
                printf("Insurance: ");
                scanf("%d", &insurance[i]);
                net[i] = basic[i] - (pf[i] + insurance[i]);
                printf("\nNew employee record added successfully!\n");
                break;

            case 3:
                printf("\nEnter Employee ID to get payslip: ");
                scanf("%d", &empID);
                found = 0;
                for (i = 0; i < num; i++) {
                    if (empId[i] == empID) {
                        printSalary(empId, employeeName, basic, pf, insurance, net, i);
                        found = 1;
                        break;
                    }
                }
                if (!found) printf("No Record Found for Employee ID %d!\n", empID);
                break;

            case 4:
                printf("\nEnter Employee ID to update: ");
                scanf("%d", &empID);
                found = 0;
                for (i = 0; i < num; i++) {
                    if (empId[i] == empID) {
                        found = 1;
                        printf("\nWHAT DO YOU WANT TO UPDATE?\n");
                        printf("1) NAME\n");
                        printf("2) BASIC SALARY\n");
                        printf("3) PROVIDENT FUND\n");
                        printf("4) INSURANCE\n");
                        printf("5) UPDATE ALL\n");
                        printf("Enter your choice: ");
                        scanf("%d", &updateChoice);

                        switch (updateChoice) {
                            case 1:
                                getchar();
                                printf("New Name: ");
                                fgets(employeeName[i], 32, stdin);
                                employeeName[i][strcspn(employeeName[i], "\n")] = '\0';
                                break;
                            case 2:
                                printf("New Basic Salary: ");
                                scanf("%d", &basic[i]);
                                break;
                            case 3:
                                printf("New Provident Fund: ");
                                scanf("%d", &pf[i]);
                                break;
                            case 4:
                                printf("New Insurance: ");
                                scanf("%d", &insurance[i]);
                                break;
                            case 5:
                                getchar();
                                printf("New Name: ");
                                fgets(employeeName[i], 32, stdin);
                                employeeName[i][strcspn(employeeName[i], "\n")] = '\0';
                                printf("New Basic Salary: ");
                                scanf("%d", &basic[i]);
                                printf("New Provident Fund: ");
                                scanf("%d", &pf[i]);
                                printf("New Insurance: ");
                                scanf("%d", &insurance[i]);
                                break;
                            default:
                                printf("Invalid choice!\n");
                        }

                        net[i] = basic[i] - (pf[i] + insurance[i]);
                        printf("\nEmployee record updated successfully!\n");
                        break;
                    }
                }
                if (!found) printf("No Record Found for Employee ID %d!\n", empID);
                break;

            case 5:
                deleteEmployee(empId, employeeName, basic, pf, insurance, net, &num);
                break;

            case 6:
                 printf("\nExiting Payroll System... Goodbye!\n");
                return 0;


            default:
                printf("Invalid choice! Try again.\n");
        }

        printf("\nDo you want to continue? (1 = Yes, 0 = No): ");
        scanf("%d", &ch);
        if (!ch) break;
    }

    printf("\nExiting Payroll System... Goodbye!\n");
    return 0;
}