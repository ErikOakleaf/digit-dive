CFLAGS = -I/usr/include/SDL3
LDFLAGS = $(shell pkg-config --libs sdl3)

defualt: compile

compile: 
	gcc $(CFLAGS) -o main src/main.c $(LDFLAGS)

clean:
	rm -f main
