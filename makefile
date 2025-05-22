all: main

main: main.o salao.o cozinha.o
	gcc -o main main.o salao.o cozinha.o

main.o: main.c salao.h cozinha.h
	gcc -c main.c

salao.o: salao.c salao.h
	gcc -c salao.c

cozinha.o: cozinha.c cozinha.h
	gcc -c cozinha.c

clean:
ifeq ($(OS),Windows_NT)
	del /Q *.o main.exe 2>nul || echo.
else
	rm -f *.o main
endif

.PHONY: all clean