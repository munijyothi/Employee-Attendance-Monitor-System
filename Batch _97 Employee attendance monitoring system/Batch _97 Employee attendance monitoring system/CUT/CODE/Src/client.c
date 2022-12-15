#include "emp.h"
#include "attendance.h"
#include "admin.h"


int main()
{
	
	int ch;
	printf("Enter 1 for Modifying Employee details\nEnter 2 for Calculating Total working hours\nEnter 3 for Employee login\n ");
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:admin_menu();
	       		break;
		case 2:calculate_time();
		       break;
		case 3:employee_login();
			 break;
		default:printf("Invalid");
	}

	 return 0;
	
}