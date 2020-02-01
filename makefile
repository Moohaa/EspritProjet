make: main.c
	gcc -g *.c *.h -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf -Wall -o main
