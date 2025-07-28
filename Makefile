CFLAGS = -I/usr/include/SDL3 $(shell pkg-config --cflags sdl3-ttf)
LDFLAGS = $(shell pkg-config --libs sdl3) $(shell pkg-config --libs sdl3-ttf)

defualt: compile

compile: 
	gcc $(CFLAGS) -o main src/main.c $(LDFLAGS)

run: compile
	./main

clean:
	rm -f main
