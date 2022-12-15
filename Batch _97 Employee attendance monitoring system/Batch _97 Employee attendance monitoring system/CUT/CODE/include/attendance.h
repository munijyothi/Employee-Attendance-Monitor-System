#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define EMPLOYEE_ATTENDANCE_FILE "text_files/login.txt"

#define CLIENT_ADMIN 1
#define CLIENT_EMPLOYEE 2
#define CLIENT_EXIT 0


typedef struct admin_Attendance
{
	int userId;
	int day;
	int mon;
	int year;
	int li_hr;
	int li_min;
	int li_sec;
	int lo_hr;
	int lo_min;
	int lo_sec;
}admin_Attendance;


 typedef struct admin_Attendance_LL
{
	admin_Attendance lg;
	struct admin_Attendance_LL *next;

}admin_atd_node;

void admin_Attendance_display(admin_atd_node* );

admin_atd_node* admin_Attendance_read_from_file();
admin_atd_node* admin_Attendance_create_node(admin_Attendance );
admin_atd_node*
admin_Attendance_add_node(admin_atd_node* ,admin_atd_node* );

int calculate_display_login(); 

void calculate_time();			