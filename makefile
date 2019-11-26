all: 
	gcc main.c tools.c -o test
	
debug: 
	gcc -g main.c tools.c 
	./a.out