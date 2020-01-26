# Some useful variables
OBJS = graphics.o input.o main.o sprite.o game.o
CFLAGS = -Wall -g
LIBS = `sdl2-config --cflags --libs` -lSDL2_image
CC = g++

# 'all' is a phony target.
# Just typing 'make' will use the 'all' target.
# Let's point that at the dbz executable target.
all: dbz.out

# This is the dbz.out target. It will make the file 'dbz.out'
# using the provided command.
dbz.out: ${OBJS}
	${CC} ${CFLAGS} ${LIBS} ${OBJS} -o $@

# Special rule for making .o files out of .cpp files.
.cpp.o:
	${CC} ${CFLAGS} -c $<
	
# 'clean' is a phony target.
# Typing "make clean" will actually just run a command for us.
# Typically, 'clean' is set to remove the compiled outputs.
clean:
	rm *.out *.o

