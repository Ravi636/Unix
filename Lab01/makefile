OBJS = more02.o
CFLAG = -Wall -g
CC = gcc
INCLUDE =
LIBS = -lm

#more02:${OBJ}
#	${CC} ${CFLAG} ${INCLUDE} -o $@ ${OBJS} ${LIBS}

#.cpp.o:
#	${CC} ${CFLAG} ${INCLUDE} -c $<

more02: more02.c
	cc -o more02 more02.c

run: more02
	./more02

clean:
	rm *.o
	rm run

debug: more02 
	gdb sim
