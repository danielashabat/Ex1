/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 Authors: Anat Sinai 312578149 and Daniela Shabat 316415645
 This project was written for Tel Aviv unviersity course for learning about creating processes 
 Project name: 'Exercise 1' 
 decsription: this module runs the father's main of the project
*/
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
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
			return EXIT_FAILURE;
	}
	if (argc > 2) {
		printf("ERROR:too many arguments!");
		return EXIT_FAILURE;
	}

	//check if the files opened
	if ( NULL == (input_file = fopen(argv[1], "r")) ){
		printf("ERROR:can't open input file\n");
		return EXIT_FAILURE;
	}
	if (NULL == (output_file = fopen("output.txt", "w"))) {
		printf("ERROR:can't open output file\n");
		fclose(input_file);
		return EXIT_FAILURE;
	}
	fscanf(input_file, "%u\n%u\n", &dimensions, &generations);//reading variables from input file
	if (read_forest_table(input_file, dimensions) == EXIT_FAILURE) //if the function failed exit program
	{
		free_forest_table();
		fclose(input_file);
		fclose(output_file);
		return EXIT_FAILURE;
	}

	while (i < generations) {
		print_next_generation( dimensions, output_file);
		i++;
	}


	free_forest_table();
	fclose(input_file);
	fclose(output_file);
	return 0;
}


