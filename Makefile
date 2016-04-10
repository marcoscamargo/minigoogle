all: minigoogle main
	gcc -g -o main minigoogle.o main.o -Wall

minigoogle:
	gcc -g -c minigoogle.c

main:
	gcc -g -c main.c

clean:
	rm main *.o 