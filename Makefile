all:
	gcc -o game main.c `pkg-config --cflags --libs sdl2` -Wall -g