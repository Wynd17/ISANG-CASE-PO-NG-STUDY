#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_EMPLOYEES 5

typedef struct {
    char empNumber[11];  // 10 characters + null terminator
    char empName[16];    // 15 characters + null terminator
    char statusCode;     // R or C
    int hoursWorked;
    float basicRate;
    float basicPay;
    float overtimePay;
    float deductions;
    float netPay;
} Employee;

int main() {
    Employee emp[MAXIMUM_EMPLOYEES];
    FILE *fp;
    int i, numEmployees;

    // Ask user how many employees to input
   do {
    printf("How many employees do you want to enter (1 to %d)? ", MAXIMUM_EMPLOYEES);
    scanf("%d", &numEmployees);

    if (numEmployees < 1 || numEmployees > MAXIMUM_EMPLOYEES) {
        printf("\nunacceptable number. Please enter a value between 1 and %d.\n\n", MAXIMUM_EMPLOYEES);
    }
} while (numEmployees < 1 || numEmployees > MAXIMUM_EMPLOYEES);

    getchar(); // Clear newline from input buffer after scanf

    // Input employee data
    for (i = 0; i < numEmployees; i++) {
        printf("\nEnter Employee %d Details:\n", i + 1);

        printf("Employee Number (10 chars): ");
        scanf("%s", emp[i].empNumber);
        getchar(); // Consume leftover newline

        printf("Employee Name (15 chars max): ");
        fgets(emp[i].empName, sizeof(emp[i].empName), stdin);
        emp[i].empName[strcspn(emp[i].empName, "\n")] = '\0';  // Remove newline character

        printf("Status Code (R/C): ");
        scanf(" %c", &emp[i].statusCode);

        printf("Hours Worked in a month: ");
        scanf("%d", &emp[i].hoursWorked);

        printf("Basic Rate per month: ");
        scanf("%f", &emp[i].basicRate);

        printf("Deductions per month: ");
        scanf("%f", &emp[i].deductions);

        // Compute payroll
        emp[i].basicPay = 160 * emp[i].basicRate;

        if (emp[i].hoursWorked > 160) {
            int overtime = emp[i].hoursWorked - 160;
            emp[i].overtimePay = overtime * (emp[i].basicRate * 1.5);
        } else {
            emp[i].overtimePay = 0;
        }

        emp[i].netPay = emp[i].basicPay + emp[i].overtimePay - emp[i].deductions;

        getchar(); // Clear buffer before next fgets
    }

    // Write to file
    fp = fopen("employees.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fprintf(fp, "                               WYND CORPORATION\n");
    fprintf(fp, "                                QUEZON \n");
    fprintf(fp, "                                 City\n\n");
    fprintf(fp, "                                Payroll\n\n");

    fprintf(fp, "Employee     Employee         Status     Basic     Overtime   Deductions   Net\n");
    fprintf(fp, "Number       Name                       dda Salary       Pay                  Pay\n");
    fprintf(fp, "-------------------------------------------------------------------------------\n");

    for (i = 0; i < numEmployees; i++) {
        char statusStr[10];
        if (emp[i].statusCode == 'R' || emp[i].statusCode == 'r') {
            strcpy(statusStr, "Regular");
        } else if (emp[i].statusCode == 'C' || emp[i].statusCode == 'c') {
            strcpy(statusStr, "Casual");
        } else {
            strcpy(statusStr, "Unknown");
        }

        fprintf(fp, "%-12s %-16s %-8s %9.2f %10.2f %11.2f %9.2f\n",
                emp[i].empNumber,
                emp[i].empName,
                statusStr,
                emp[i].basicPay,
                emp[i].overtimePay,
                emp[i].deductions,
                emp[i].netPay);
    }

    fclose(fp);

    printf("\nPayroll written to employees.txt successfully.\n");

    return 0;
}
