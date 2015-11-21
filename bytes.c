
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
	while (-1 != (c = getopt(argc, argv, "f:e"))) {
		if (c == (int)'f') {
			check_tag(optarg);
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
	return 1;
}

void check_tag(char *filename) {
	FILE *file = NULL;
	FILE *logfile = NULL;
	int c = 0;

	if (NULL == (file = fopen(filename, "r+"))) {
		fprintf(stderr, "cannot open file: %s\nexiting...\n", filename);
		exit(EXIT_FAILURE);
	}

	if (NULL == (logfile = fopen("logfile.txt", "w"))) {
		fprintf(stderr, "cannot open file: log file\nexiting...\n");
		exit(EXIT_FAILURE);
	}

	while (EOF != (c = fgetc(file))) {
		fprintf(logfile, "%c", (char)c);
	}

	if ((EOF == (fclose(file))) || (EOF == (fclose(logfile)))) {
		fprintf(stderr, "could not close a file...\n");
		exit(EXIT_FAILURE);
	}
}

