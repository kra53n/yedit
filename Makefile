SRC = main.c draw.c edit.c move.c
OBJ = ${SRC:.c=.o}

all: yedit run

yedit: ${OBJ}
	${CC} -std=c99 -o $@ ${OBJ} -lSDL2

run:
	./yedit

clean:
	rm -f yedit ${OBJ}

# debug: ${OBJ}
# 	${CC} -o debug.out ${OBJ} -lSDL2 -g
# 	gdb debug.out
# 	rm debug.out
