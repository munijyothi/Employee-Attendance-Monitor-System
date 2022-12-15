#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EMPLOYEE 1
#define ADD 1
#define UPDATE 2
#define DELETE 3
#define DISPLAY 4
#define LOGOUT 5
#define EXIT 0
#define ADMIN_LOGOUT 3
#define GO_BACK 6

typedef struct Admin
{
	int userId;
	char name[20];
	char password[20];
	
}admin;

	
typedef struct admin_employee{

	int userId;
	char password[20];
	char name[20];
	char lname[20];
}admin_employee;
	
typedef struct admin_Employee_LL{

	admin_employee emp;
	struct admin_Employee_LL *next;

}admin_d_node;

	

int validate_admin(int,char []);


int admin_validate_name(char[]);

void admin_menu();

void admin_employee_menu();


admin_d_node* add_employee();

void admin_employee_freeList(admin_d_node*);


admin_d_node* admin_employee_create_node(admin_employee);

admin_d_node* admin_employee_add_node(admin_d_node*,admin_d_node*);

FILE* admin_employee_write_to_file(FILE*, admin_d_node*);


admin_d_node* admin_employee_read_from_file();

void admin_employee_display(int,admin_d_node*);

admin_d_node* admin_employee_update(int,admin_d_node*);

admin_d_node* admin_employee_delete(int,admin_d_node*);


