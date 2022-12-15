#include <string.h>
#include "admin.h"

void calculate_emp(void);

void admin_menu()
{
	int admin_id,opt;
	char admin_password[20],ch;
	FILE *dptr;
	printf("\n--------------------WELCOME ADMIN--------------------\n\n");
	printf("Admin Login::\n");
	printf("Enter Admin ID: ");
	scanf("%d",&admin_id);
	printf("Enter password: ");
	scanf("%s",admin_password);
	admin_password[strlen(admin_password)]='\n';
	if(validate_admin(admin_id,admin_password))			
	{
		printf("\nLogged in successfully...\n\n");
		while(1)
		{
			printf("\n--------------ADMIN MENU--------------\n\n");
			printf("Choose an option...\n1) Employee\n2) LogOut\n0) Exit\nOption: ");
			scanf("%d",&opt);
			switch(opt)
			{
				case 1:
					admin_employee_menu();
					continue;
				case 3:
					printf("Logged out successfully..\n\n");
					printf("Do you want to login again..?\n");
					printf("Choose y/n : ");
					while(getchar()!='\n');
					ch=getchar();
					if(ch=='Y' || ch=='y')
					{
						admin_menu();
						break;
					}
					
					return;
				case 0:
					printf("\nThank you for using our services \nExited from Employee Attendance Monitor System..\n\n");
					exit(0);
				default:
					printf("Invalid Option!! Choose a valid option...\n");
					continue;
			}
		}
	}
	else
	{
		printf("\nIncorrect Admin ID/Password !!!\n");
		printf("Do you want to login again..?\n");
		printf("Choose y/n : ");
		while(getchar()!='\n');
		ch=getchar();
		if(ch=='Y' || ch=='y')
			admin_menu();
		else
		{
			printf("\nThank you for using our services \nExited from Employee Attendance Monitor System..\n\n");
			exit(0);
		}
	}
	
}


int admin_validate_name(char str[])
{
	int n,i,check;
	n=strlen(str);
	for(i=0;i<n;i++)
	{
		if((str[i]>='a' && str[i]<='z') || (str[i]>='A' && str[i]<='Z') || str[i]==' ')
			check=0;
		else
			return 0;
	}
	
	
	if(check==0)  //To check whether the name is valid
		return 1;
	else
		return 0;
}


int validate_admin(int admin_id, char admin_password[20])
{
	char *token;
	FILE* fptr;
	admin ad;
	int count=0;
	char line[100];
	fptr=fopen("./text_files/admin_details.txt","r");
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

		if(admin_id==ad.userId)
			return 1;
		count=0;
	}
	return 0;
}



void admin_employee_menu()
{
	int choice,id;
	char ch;
	admin_d_node *head;
	FILE *dptr;
	while(1)
	{
		printf("\nChoose an option...\n1) Add employee\n2) Update employee\n3) Delete employee\n4) Display employee\n5) Go Back\n0) Exit\nOption: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case ADD:
				head = add_employee();
				dptr = fopen("./text_files/employee_details.txt","a");	
				dptr=admin_employee_write_to_file(dptr,head);
				fclose(dptr);
				printf("\nemployee added successfully with !!!\n\n");
				continue;
			case UPDATE:
				head=admin_employee_read_from_file();
				printf("\nEnter the employee ID of the employee you want to update the details: ");
				scanf("%d",&id);
				head=admin_employee_update(id,head);
				dptr = fopen("./text_files/employee_details.txt","w");	
				dptr=admin_employee_write_to_file(dptr,head);
				fclose(dptr);
				printf("\nemployee details updated successfully !!\n");
				continue;
			case DELETE:
				head=admin_employee_read_from_file();
				printf("\nEnter the employee ID of the employee you want to delete the details: ");
				scanf("%d",&id);
				head=admin_employee_delete(id,head);
				dptr = fopen("./text_files/employee_details.txt","w");	
				dptr=admin_employee_write_to_file(dptr,head);
				fclose(dptr);
				continue;
			case DISPLAY:
				head=admin_employee_read_from_file();
				printf("\nEnter the employee ID of the employee you want to display the details: ");
				scanf("%d",&id);
				admin_employee_display(id,head);
				continue;
			case GO_BACK:
				printf("Do you want to login again..?\n");
				printf("Choose y/n : ");
				while(getchar()!='\n');
				ch=getchar();
				if(ch=='Y' || ch=='y')
				{
					admin_menu();
					break;
				}
				return;
			case EXIT:
				admin_employee_freeList(head);
				printf("\nThank you for using our services \nExited from Employee Attendance Monitor System..\n\n");
				exit(0);
			default:
				printf("Invalid Option!! Choose a valid option...\n");
				continue;
		}
	}
}


admin_d_node* admin_employee_create_node(admin_employee d)
{
	admin_d_node *newnode= (admin_d_node*)malloc(sizeof(admin_d_node));
	
	newnode->emp.userId=d.userId;
	strcpy(newnode->emp.password,d.password);
	strcpy(newnode->emp.name,d.name);
	strcpy(newnode->emp.lname,d.lname);
	
	return newnode;
}

admin_d_node* admin_employee_add_node(admin_d_node *head,admin_d_node *newnode)
{
    admin_d_node *temp=head;
    //check if LL is empty
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


FILE* admin_employee_write_to_file(FILE *dptr2, admin_d_node *head)
{
	admin_d_node *temp=head;
	
	while(temp!=NULL)
	{
		fprintf(dptr2,"%d,%s,%s,%s\n",temp->emp.userId, temp->emp.password,temp->emp.name,temp->emp.lname);
		temp=temp->next;
	}
	
	return dptr2;
	
}



admin_d_node* admin_employee_read_from_file()
{
	char *token;
	int cont=0;
	FILE* fptr;
	admin_employee emp;
	int count=0;
	admin_d_node *head,*newnode;
	head=NULL;
	newnode=NULL;
	char line[200];
	char *end[20];
	fptr=fopen("text_files/employee_details.txt","r");
	
	if(fptr==NULL)
		printf("File doesn't exist\n");
	
	while(fgets(line,200,fptr)!=NULL)
	{
	
		token=strtok(line,",");
		
		if(count==0)
		{
			emp.userId=atoi(token);
			count++;
			token=strtok(NULL,",");
		}
		
		if(count==1)
		{
			strcpy(emp.password,token);
			token=strtok(NULL,",");
			count++;
		}
		if(count==2)
		{
			strcpy(emp.name,token);
			token=strtok(NULL,",");
			count++;
		}
		
		if(count==3)
		{
			strcpy(emp.lname,token);
			token=strtok(NULL,",");
			count++;
		}

		count=0;
		cont++;
		newnode=admin_employee_create_node(emp);
		head=admin_employee_add_node(head,newnode);
	}
	fclose(fptr);
	return head;
}


admin_d_node* add_employee()
{
	int check=0,count=0;
	admin_employee emp;
	emp.userId=999;
	char line[200];
	char *token;
	FILE *fptr;
	admin_d_node *head,*newnode;
	head=NULL;
	newnode=NULL;
	fptr=fopen("./text_files/employee_details.txt","r");
	if(fptr==NULL)
		printf("File doesn't exist\n");
	
	while(fgets(line,sizeof(line),fptr)!=NULL)
	{
		token=strtok(line,",");
	
		if(count==0)
		{
			emp.userId=atoi(token);
			count++;
			token=strtok(NULL,",");
		}
		count=0;
	}
	emp.userId++;
	printf("\nEnter the details to add a employee:\n");
	    
	printf("\nPassword: ");
	scanf("%s",emp.password);
	
	printf("\nFirst name: ");
	while(1)
	{
		scanf("%s",emp.name);
		check=admin_validate_name(emp.name); //to validate name
		if(check==1)
			break;
		else
			printf("Enter valid name\n");
	}
	
	printf("\nLast name: ");
	while(1)
	{
		scanf("%s",emp.lname);
		check=admin_validate_name(emp.lname); //to validate name
		if(check==1)
			break;
		else
			printf("Enter valid name\n");
		
	
	}
	newnode=admin_employee_create_node(emp);
	head=admin_employee_add_node(head,newnode);
		printf("employee is added with %d Id",emp.userId);
	return head;
}




void admin_employee_freeList(admin_d_node* head)
{
   admin_d_node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
    free(head);
}




void admin_employee_display(int id,admin_d_node *head)
{
	int check=0;
	admin_d_node *temp=head;
	
	while(temp!=NULL && id!=temp->emp.userId)
	{
		temp=temp->next;
		
	}
	
	if(temp!=NULL)
	{
		printf("\nDetails of the employee are ::");
		printf("\nemployee ID : %d",temp->emp.userId);	
		printf("\nName: %s %s",temp->emp.name,temp->emp.lname);
		
	}
	else
		printf("\nNo employee exists with the ID you entered.\n");
}



admin_d_node* admin_employee_update(int id,admin_d_node* head)
{
	admin_d_node *temp=head;
	int check=0;
	char name[20],lname[20],password[20];
	while(temp!=NULL && id!=temp->emp.userId)
	{
		temp=temp->next;
			
	}
		
	if(temp!=NULL)
	{
		printf("employee Name: %s",temp->emp.name);
		printf("\nEnter new details of the employee :\n");
		printf("\nPassword: ");
		scanf("%s",password);
		
		printf("\nFirst name: ");
		while(1)
		{
			scanf("%s",name);
			check=admin_validate_name(name); 
			if(check==1)
				break;
			else
				printf("Enter valid name\n");
		}
		
		printf("\nLast name: ");
		while(1)
		{
			scanf("%s",lname);
			check=admin_validate_name(lname); 
			if(check==1)
				break;
			else
				printf("Enter valid name\n");
		}
		
		strcpy(temp->emp.password,password);
		strcpy(temp->emp.name,name);
		strcpy(temp->emp.lname,lname);
		
	}		
	else
		printf("\nNo employee exists with the ID you entered.\n");
		
	return head;
}


admin_d_node* admin_employee_delete(int id,admin_d_node *head)
{
	
		admin_d_node *temp=head;
		admin_d_node *temp2=NULL;
		
		if(temp->emp.userId==id)
		{
			head=head->next;
			free(temp);
			temp=NULL;
			printf("\nEmployee Deletion successfull\n");
			return head;
		}
		while(temp!=NULL && id!=temp->emp.userId)
		{
			temp2=temp;
			temp=temp->next;
			
		}
		
		if(temp!=NULL)
		{
			temp2->next=temp->next;
			free(temp);
			temp=NULL;
			printf("\nEmployee Deletion successfull !!\n");
			
		}
		else
			printf("\nNo Employee exists with the ID you entered.\n");
		
		return head;
	
}


