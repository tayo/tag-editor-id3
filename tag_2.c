
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void check_tag(char*);
int getopt(int argc, char * const argv[], const char *optstring);

extern char *optarg;
extern int optind, optopt;
extern int opterr;

int seek_tag = 0;
int remove_extras = 0;

int main(int argc, char **argv) {
	int c = 0;
	char *filename = NULL;

	opterr = 0;
	while (-1 != (c = getopt(argc, argv, "f:e"))) {
		if (c == (int)'e')
			remove_extras = 1;
		else if (c == (int)'f') {
			/*check_tag(optarg);*/ 
			seek_tag = 1;
			if (NULL == (filename = malloc(strlen(optarg) + 1))) {
				fprintf(stderr, "unable to malloc space for filename\n");
				exit(EXIT_FAILURE);
			}
			strcpy(filename, optarg);
		}
		else if (c == (int)'?') {
			fprintf(stderr, "do not recognize flag %c...\n", c);
			exit(EXIT_FAILURE);
		}
	}

	if (optind < argc) {
		printf ("non-option arguments: ");
		while (optind < argc)
			printf ("%s ", argv[optind++]);
		printf ("\n");
	}

	printf("finished parsing command line...\n");

	if (seek_tag)
		check_tag(filename);

	free(filename);

	return 1;
}

void check_tag(char *filename) {
	FILE *file = NULL;
	char album[31];
	char year[5];
	char comment[31];
	int genre = 0;

	/* open a file handle to the file */
	if (NULL == (file = fopen(filename, "r+"))) {
		fprintf(stderr, "cannot open file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	/* seek to place where id3v1 tag should begin */
	if (0 != (fseek(file, -128, SEEK_END))) {
		fprintf(stderr, "cannot set file position in file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	/* EOF should not be possible, as I have just moved back 128 bytes - no check */
	if ((fgetc(file) == (int)'T') && (fgetc(file) == (int)'A') && (fgetc(file) == (int)'G')) {  
		/*printf("i found a tag!\n"); */
		if (!remove_extras)
			exit(2);
		else {
			if (0 != fseek(file, 60, SEEK_CUR)) {
				fprintf(stderr, "cannot set file position to remove extras...\n");
				exit(EXIT_FAILURE);
			}

			if ((NULL==fgets(album,31,file))||
				(NULL==fgets(year,5,file))||
				(NULL==fgets(comment,31,file))
				||(EOF==(genre=fgetc(file)))) {
				fprintf(stderr, "cannot read extra stuff...\n");
				exit(EXIT_FAILURE);
			}
			printf("album: %s\nyear: %s\ncomment: %s\ngenre: %d\n", album, year, comment, genre);
		}
	}
	else printf("no tag: %s\n", filename);


	if (EOF == (fclose(file))) {
		fprintf(stderr, "could not close file...\n");
		exit(EXIT_FAILURE);
	}
	exit(3);	/* did not find a tag */
}
