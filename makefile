all: fork.c
	gcc fork.c

clean:
	rm a.out

run: all
	./a.out
