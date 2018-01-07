CFLAGS=-Wall -g

all: ex5 ex6

ex5:
	cc -Wall -g ex5.c -o ex5

ex6:
	cc -Wall -g ex6.c -o ex6

clean:
	# delete any file without extension except for Makefile
	ls | grep -v "\." | grep -v Makefile | xargs rm