#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define EMPLOYEE_DETAILS_FILE "text_files/emp_details.txt"
#define EMPLOYEE_ATTENDANCE_FILE "text_files/login.txt"



void employee_login(); 


int validate_employee(int userId, char password[20]);