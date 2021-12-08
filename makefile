all: main.o

main.o: main.c
	gcc -o main main.c
run:
	./main
