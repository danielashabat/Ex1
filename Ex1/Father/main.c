///FILE COMMENTS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Father.h"



//command line: Father.exe, input.txt
int main(int argc, char* argv[]) {
	FILE* input_file = NULL, * output_file = NULL;
	unsigned int dimensions;
	unsigned int generations;
	int i = 0;

	//check if there 2 arguments
	if (argc < 2) {
		printf("ERROR:not enough arguments!");
			return 1;
	}
	if (argc > 2) {
		printf("ERROR:too many arguments!");
		return 1;
	}

	//check if the files opened
	if ( NULL == (input_file = fopen(argv[1], "r")) ){
		printf("ERROR:can't open input file\n");
		return 1;
	}
	if (NULL == (output_file = fopen("output.txt", "w"))) {
		printf("ERROR:can't open output file\n");
		fclose(input_file);
		return 1;
	}
	fscanf(input_file, "%u\n%u\n", &dimensions, &generations);//reading variables from input file
	read_forest_table(input_file, dimensions);//reading forest table from input file and assign it in a global variable

	while (i < generations) {
		print_next_generation( dimensions, output_file);
		i++;
	}


	free_forest_table();
	fclose(input_file);
	fclose(output_file);
	return 0;
}


