
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_tag(char*);
void remove_v2(char*);
int getopt(int argc, char * const argv[], const char *optstring);

extern char *optarg;
extern int optind, optopt;
extern int opterr;

/*
 * run the program with these tags:
 * 		-f <filename>
 * 		checks if this file has an mp3 tag
 *
 * 		-v <filename>
 * 		removes the tag from the file
 */
int main(int argc, char **argv) {
	int c = 0;

	opterr = 0;
	while (EOF != (c = getopt(argc, argv, "f:v:"))) {
		if (c == 'f')
			check_tag(optarg);
		else if (c == 'v')
			remove_v2(optarg);
		else if (c == '?') {
			fprintf(stderr, "do not recognize option...\n");
			exit(EXIT_SUCCESS);
		}
	}

	if (optind < argc) {
		printf ("non-option arguments: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		printf ("\n");
	}

	printf("finished parsing command line...\n");
	return 1;
}

/*
 * checks for an id3v2 tag and removes it if found
 */
void remove_v2(char *filename) {
	FILE *file = NULL;

	if (NULL == (file = fopen(filename, "r+"))) {
		fprintf(stderr, "cannot open file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	/* not checking for EOF here */
	if ((fgetc(file) == 'I') && (fgetc(file) == 'D') && (fgetc(file) == '3')) {
		if (0 != fseek(file, 0, SEEK_SET)) {
			fprintf(stderr, "cannot set file position...\n");
			exit(EXIT_FAILURE);
		}

		if (EOF == fputs("\0\0\0\0\0\0\0\0\0\0", file)) {
			fprintf(stderr, "could not overwrite id3v2 tag...\n");
			exit(EXIT_FAILURE);
		}

		if (EOF == (fclose(file))) {
			fprintf(stderr, "could not close file...\n");
			exit(EXIT_FAILURE);
		}
		exit(2);
	}
	else
		exit(3);
}
	
void check_tag(char *filename) {
	FILE *file = NULL;
	char album[31];
	char year[5];
	char comment[31];
	int genre = 0;

	if (NULL == (file = fopen(filename, "r+"))) {
		fprintf(stderr, "cannot open file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	if (0 != (fseek(file, -128, SEEK_END))) {
		fprintf(stderr, "cannot set file position in file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	/* EOF is not possible, as I have just moved back 128 bytes */
	if ((fgetc(file) == 'T') && (fgetc(file) == 'A') && (fgetc(file) == 'G'))  {
		exit(2);
		

	printf("found an id3v1 tag!\n");
		if (0 != fseek(file, 60, SEEK_CUR)) {
			fprintf(stderr, "cannot set file position to remove extras...\n");
			exit(EXIT_FAILURE);
		}

		if ((NULL==fgets(album,31,file))||
			(NULL==fgets(year,5,file))||
			(NULL==fgets(comment,31,file))||
			(EOF==(genre=(char)fgetc(file)))) {
			fprintf(stderr, "cannot read extra stuff...\n");
			exit(EXIT_FAILURE);
		}
		printf("album: %s\nyear: %s\ncomment: %s\n", album, year, comment);
	}


	if (EOF == (fclose(file))) {
		fprintf(stderr, "could not close file...\n");
		exit(EXIT_FAILURE);
	}
	exit(3);	/* did not find a tag */
}
