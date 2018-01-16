CFLAGS=-Wall -g

all:  ex9

ex9:
	cc -Wall -g ex9.c -o ex9

clean:
	# delete any file without extension except for Makefile and .gitignore
	ls | grep -v "\." | grep -E -v 'Makefile|.gitignore' |  xargs rm