all:eams

eams: client.o attendance1.o  admin_def.o emp_def.o

	gcc client.c attendance1.c attendance.h admin_def.c admin.h emp_def.c emp.h -o eams

client.o: client.c
	gcc -c client.c
attendance1.o: attendance1.c
	gcc -c attendance1.c
admin_def.o: admin_def.c
	gcc -c admin_def.c
emp_def.o: emp_def.c
	gcc -c emp_def.c
clean:
	rm *.o eams
