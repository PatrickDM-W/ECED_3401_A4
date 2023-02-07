/****************************************
Oct 10th, 2022
Patrick Wain

MorseDecoder.c
Main program containing entry point
****************************************/

#define DEBUG
#include "MorseDecoder.h"

FILE* infile;

int main(int argc, char* argv[])
{
	MORSE* root = build_compare_tree();
	char encoded[MAX_MORSE_LEN];
	char decoded;

	/*
	- open file in argv[1], reads and checks sentences
	- at EOF, stop reading and close
	- if only one argument (.exe name), stop executing
	*/

	/* check number of arguments */
	if (argc == 1)
	{
		printf("Missing file name\n");
		getchar();
		return -1;
	}

	for (int i = 1; i < argc; ++i)
	{
		/* argc >= 1, attempt to open file */
		if (fopen_s(&infile, argv[i], "r") != 0)
		{
			printf("Error opening file >%s< - possibly missing\n", argv[1]);
			getchar();
			return -1;
		}

		/* file(s) open now */
		while (fscanf_s(infile, "%s", encoded, MAX_MORSE_LEN) > 0)
		{
			/* read file for morse string */
			decoded = decode_char(root, encoded)->morse_char;
			printf("%c", decoded);

			decoded = fgetc(infile);
			if (decoded == '\t')
				printf(" ");
		}

		printf("\n");
		fclose(infile);
	}

	printf("\nWaiting to quit...");
	getchar();

	return 0;
}