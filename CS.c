#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    Employee emp[5];
    FILE *fp;  // Write to text file with formatted layout
    int i;
    

    // Input 5 employees
    for (i = 0; i < 5; i++) {
        printf("Enter Employee %d Details:\n", i + 1);

        printf("Employee Number (10 chars): ");
        scanf("%s", emp[i].empNumber);

        printf("Employee Name (15 chars max): ");
        scanf(" %s[^\n]", emp[i].empName);  // allows spaces in name

        printf("Status Code (R/C): ");
        scanf(" %c", &emp[i].statusCode);

        printf("Hours Worked: ");
        scanf("%d", &emp[i].hoursWorked);

        printf("Basic Rate: ");
        scanf("%f", &emp[i].basicRate);

        printf("Deductions: ");
        scanf("%f", &emp[i].deductions);

        emp[i].basicPay = 160 * emp[i].basicRate;

        if (emp[i].hoursWorked > 160) {
            int overtime = emp[i].hoursWorked - 160;
            emp[i].overtimePay = overtime * (emp[i].basicRate * 1.5);
        } else {
            emp[i].overtimePay = 0;
        }

        emp[i].netPay = emp[i].basicPay + emp[i].overtimePay - emp[i].deductions;
    }
fp = fopen("employees.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    fprintf(fp, "                               WENDELL CORP\n");
    fprintf(fp, "                                QUEZON \n");
    fprintf(fp, "                                 City\n\n");
    fprintf(fp, "                                Payroll\n\n");

    fprintf(fp, "Employee     Employee         Status    Basic     Overtime  Deductions   Net\n");
    fprintf(fp, "Number       Name                       Salary       Pay                 Pay\n");
    fprintf(fp, "-------------------------------------------------------------------------------\n");

    for (i = 0; i < 5; i++) {
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

    printf("Payroll written to employees.txt successfully.\n");

    return 0;
}
