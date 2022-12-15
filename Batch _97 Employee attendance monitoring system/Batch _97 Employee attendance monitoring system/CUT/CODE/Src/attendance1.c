#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "attendance.h"
#include "admin.h"


void admin_Attendance_display(admin_atd_node* );

admin_atd_node* admin_Attendance_read_from_file();
admin_atd_node* admin_Attendance_create_node(admin_Attendance );
admin_atd_node* admin_Attendance_add_node(admin_atd_node* ,admin_atd_node* );



void calculate_time()			
{
	int admin_id;
	char admin_password[20];
	
	printf("Admin Login::\n");
	printf("Enter Admin ID: ");
	scanf("%d",&admin_id);
	printf("Enter password: ");
	scanf("%s",admin_password);
	admin_password[strlen(admin_password)]='\n';
	
	if(validate_admin(admin_id,admin_password))
	{
		admin_atd_node* head;
		head=NULL;
	
		head=admin_Attendance_read_from_file();
		admin_Attendance_display(head );
	}
	else 
	{
		printf("Invalid Login details\n");
	}

}

admin_atd_node* admin_Attendance_read_from_file()
{
	admin_Attendance lg;
	admin_atd_node* newnode,*head;
	head=NULL;
	 
      char line[200],date[20],temp_date[20],li_time[20],lo_time[20];
	char *token;
	int count,count1,count2,count3;
	FILE *fptr;
	int userId;
	fptr=fopen("text_files/L.txt","r");
	
	if(fptr==NULL)
		printf("File doesn't exist\n");
	
	while(fgets(line,100,fptr)!=NULL)
	{
	
		token=strtok(line,",");
		
		if(count==0)
		{
			lg.userId=atoi(token);
			count++;
			token=strtok(NULL,",");
		}
		
		if(count==1)
		{
			strcpy(date,token);
			token=strtok(NULL,",");
			count++;
			
			
		}
		if(count==2)
		{
			strcpy(li_time,token);
			token=strtok(NULL,",");
			count++;
		}
		
		if(count==3)
		{
			strcpy(lo_time,token);
			token=strtok(NULL,",");
			count++;
		}
		
		count=0;
		
		
		
		token=strtok(date,"-");
		
		lg.day=atoi(token);
		token=strtok(NULL,"-");
		
		lg.mon=atoi(token);
	
		
		token=strtok(NULL,"-");
		lg.year=atoi(token);
	
		
		
		token=strtok(li_time,":");
		lg.li_hr=atoi(token);
	
		token=strtok(NULL,":");
		
		lg.li_min=atoi(token);
		
		
		token=strtok(NULL,":");
		lg.li_sec=atoi(token);
	
		
		
		token=strtok(lo_time,":");
		lg.lo_hr=atoi(token);
	
		token=strtok(NULL,":");
		lg.lo_min=atoi(token);
		
	
		
		token=strtok(NULL,":");
		lg.lo_sec=atoi(token);
	
		newnode=admin_Attendance_create_node(lg);
		
		head=admin_Attendance_add_node(head,newnode);
		
		
	}
	
	
	fclose(fptr);
	return head;
}


 admin_atd_node* admin_Attendance_create_node(admin_Attendance Lg)
{
	admin_atd_node *newnode;
	newnode = (admin_atd_node*)malloc(sizeof(admin_atd_node)); 
	
	newnode->lg.userId=Lg.userId;
	newnode->lg.day=Lg.day;
	newnode->lg.mon=Lg.mon;
	newnode->lg.year=Lg.year;
	newnode->lg.li_hr=Lg.li_hr;
	newnode->lg.li_min=Lg.li_min;
	newnode->lg.li_sec=Lg.li_sec;
	newnode->lg.lo_hr=Lg.lo_hr;
	newnode->lg.lo_min=Lg.lo_min;
	newnode->lg.lo_sec=Lg.lo_sec;
	
	
	return newnode;
}


admin_atd_node* admin_Attendance_add_node(admin_atd_node *head,admin_atd_node *newnode)
{
    admin_atd_node *temp=head;
   
    if(head==NULL)
         head = newnode;
    else
    {
        while(temp->next!=NULL)
              temp = temp->next;
          
        temp->next = newnode; 
    }

   return head;
}



void admin_Attendance_display(admin_atd_node *head)
{
	
	int tot_hrs=0,tot_min=0,tot_sec=0;
	int temp_hrs,temp_min,temp_sec;
	int check=0;
	admin_atd_node *temp=head;
	int d,m,y;
	
	printf("Enter the date in the format of dd-mm-yy: ");
	scanf("%d-%d-%d",&d,&m,&y);
	
	while(temp!=NULL )
	{
		if( d==temp->lg.day && m==temp->lg.mon && y==temp->lg.year)
		{
			
			if(temp->lg.lo_hr!=0 && temp->lg.lo_min!=0 && temp->lg.lo_sec!=0)
			{
				printf("Employee with %d has logged in and logged out succesfully\n", temp->lg.userId);
				temp_hrs=temp->lg.lo_hr - temp->lg.li_hr;
				temp_min=abs(temp->lg.lo_min - temp->lg.li_min);
				temp_sec=abs(temp->lg.lo_sec - temp->lg.li_sec);	

				tot_hrs += temp_hrs;
				tot_min += temp_min;
				tot_sec += temp_sec;		
			}
			else
			{
				printf("The Employee has  logged in but not logged out for the day\n");
			}
		
		}
		
		temp=temp->next;	
	}
	
		

		tot_min = tot_min+(tot_sec/60);
		tot_sec = (tot_sec%60);
		tot_hrs = tot_hrs+(tot_min/60);
		tot_min = (tot_min%60);		
		
		printf("\nTotal working hours: %d:%d:%d\n",tot_hrs,tot_min,tot_sec);
	
}




