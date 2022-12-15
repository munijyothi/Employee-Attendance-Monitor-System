#include <stdio.h>
#include <string.h>
#include <time.h>
#include "admin.h"

int validate_employee(int userId, char password[20]);

void employee_login()
{
	
	int userId, d, m, y, li_hr, li_min, li_sec, lo_hr, lo_min, lo_sec;
	char password[20];
	int ch;
	
	FILE *ptr;
	FILE *fptr;
	ptr=fopen("text_files/L.txt","a");
	fptr=fopen("text_files/employee_details.txt","r");	
	time_t loginTime = time(NULL);
	
	
	printf("------------WELCOME EMPLOYEE ---------\n\n");
	
	printf("Employee login id\n");
	scanf("%d",&userId);

	printf("Employee pwd \n");
	scanf("%s",password);
	
	password[strlen(password)]='\n';
	
	
	if(validate_employee( userId, password))
	{
		printf("\nLogged in successfully...\n\n");
	
	
	printf("The login details are : %s \n",ctime(&loginTime));

	struct tm *pTime = NULL;
	pTime = localtime(&loginTime);

	
	fprintf(ptr,"%d,%d-%d-%d,%d:%d:%d,",userId,pTime->tm_mday,pTime->tm_mon+1,22,pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
	
	
	printf("Enter 1 for logout, any other digit for exit\n");
	scanf("%d",&ch);
	if(ch == 1)
	{
		time_t logoutTime = time(NULL);
		pTime = localtime(&logoutTime);

		
		fprintf(ptr,"%d:%d:%d\n",pTime->tm_hour,pTime->tm_min,pTime->tm_sec);
		printf("Logged out Succesfully");
	}
	else
	{
		fprintf(ptr,"0:0:0\n");
		
	}

	while(fptr != NULL)
	{
		fscanf(fptr,"%d,%d-%d-%d,%d:%d:%d,%d:%d:%d\n",&userId,&d,&m,&y,&li_hr,&li_min,&li_sec,&lo_hr,&lo_min,&lo_sec);
		break;
		
	}	
}
	else
		printf("login details are invalid");	
		
}


int validate_employee(int userId, char password[20])
{
	char *token;
	FILE* fptr;
	admin ad;
	int count=0;
	char line[100];
	fptr=fopen("./text_files/employee_details.txt","r");
	if(fptr==NULL)
		printf("File doesn't exist\n");
	
	while(fgets(line,sizeof(line),fptr)!=NULL)
	{
		token=strtok(line,",");
		
		if(count==0)
		{
			ad.userId=atoi(token);
			count++;
			printf("Id is : %d\n", ad.userId);
			token=strtok(NULL,",");
		}
		
		if(count==1)
		{
			strcpy(ad.password,token);
			token=strtok(NULL,",");
			count++;
		}

		if(userId==ad.userId)
			return 1;
		count=0;
	}
	return 0;
}

