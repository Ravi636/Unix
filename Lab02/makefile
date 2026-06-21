
who2: who2.c
	cc -o who2 who2.c

whoami: whoami.c
	cc -o whoami whoami.c
run: who2
	./who2

clean:
	rm *.o
	rm run

debug: who2 
	gdb sim
