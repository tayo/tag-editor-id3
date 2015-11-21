
tag: tag.c
	gcc -ansi -pedantic -Wall -O2 -o tag tag.c

bytes: bytes.c
	gcc -ansi -pedantic -Wall -O2 -o bytes bytes.c

debug: tag.c
	gcc -ansi -pedantic -Wall -o debug tag.c
