all: lab2

lab2: lab2.c lab.c
		gcc lab2.c -c 
		gcc lab2.o lab.o -o lab2

lab.c:
		gcc ../libs/lab.c -c

clean:
		rm lab2
		rm *.o