all: compile run
compile:
	gcc -o uyg main.c
run:
	./uyg
