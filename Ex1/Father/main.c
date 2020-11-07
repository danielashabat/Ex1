///FILE COMMENTS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Father.h"

static unsigned int dimensions;
static unsigned int generations;

//command line: Father.exe, input.txt
int main(int argc, char* argv[]) {
	FILE* input_file = NULL, * output_file = NULL;

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
		return 1;
	}

	set_dimension_generations(input_file); //reading variables from input file



	fclose(input_file);
	fclose(output_file);
	return 0;
}

void set_dimension_generations(FILE* input_file)
{

	fscanf(input_file, "%u\n%u\n", &dimensions, &generations);
}

void father(FILE* input_file, FILE* output_file) {

	////printf("%u\n%d\n", dimensions, generations);
	//allocate_memory_to_forest_string(dimensions);
	read_forest_table(input_file, forest_table, dimensions);

	//printf("{%s}\n", forest_table);
	//while (i < generations) {
	//	forest_table = load_next_generation(forest_table, dimensions);
	//	printf("{%s}\n", forest_table);
	//	i++;
	//}


	//free(forest_table);
}