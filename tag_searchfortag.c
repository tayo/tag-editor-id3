
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void check_tag(char*);
int getopt(int argc, char * const argv[], const char *optstring);

extern char *optarg;
extern int optind, optopt;
extern int opterr;

int main(int argc, char **argv) {
	int c = 0;

	opterr = 0;
	while (-1 != (c = getopt(argc, argv, "f:"))) {
		if ((c == (int)'f') || (c = (int)'F'))
			check_tag(optarg);
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
	return 1;
}

void check_tag(char *filename) {
	FILE *file = NULL;
	int cur = 0;
	int has_tag = 0;
	int byte_counter = 0;

	if (NULL == (file = fopen(filename, "r"))) {
		fprintf(stderr, "cannot open file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	while (EOF != (cur = fgetc(file))) {
		byte_counter++;
		if ((char)cur == 'T') {
			if ((EOF != (cur = fgetc(file))) && ((char)cur == 'A')) {
				if ((EOF != (cur = fgetc(file))) && ((char)cur == 'G')) {
					has_tag = 1;
					break;
				}
				else {
					if (EOF == ungetc(cur, file)) {
						fprintf(stderr, "could not unget a character...\n");
						exit(EXIT_FAILURE);
					}
					if (EOF == ungetc(cur, file)) {
						fprintf(stderr, "could not unget a character...\n");
						exit(EXIT_FAILURE);
					}
				}
			}
			else {
				if (EOF == ungetc(cur, file)) {
					fprintf(stderr, "could not unget a character...\n");
					exit(EXIT_FAILURE);
				}
			}
		}
	}


	if (has_tag) printf("found a tag at byte %d", byte_counter);

	while (EOF != (cur = fgetc(file)))
		byte_counter++;

	printf(" of %d bytes...\n", byte_counter);

	if (EOF == (fclose(file))) {
		fprintf(stderr, "could not close file...\n");
		exit(EXIT_FAILURE);
	}
}
