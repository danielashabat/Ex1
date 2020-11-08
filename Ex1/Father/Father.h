/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 Authors: Anat Sinai and Daniela Shabat 316415645
 This project was written for Tel Aviv unviersity course for learning about creating processes
 Project name: 'Exercise 1'
 decsription:in this module written all the declaration and macros of the functions that belong to the father and can be used from the main.
*/
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/


#ifndef	FATHER_H
#define FATHER_H


#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55
#define ALLOCATION_ERROR(NAME) if (NAME == NULL) {\
	printf("allocation failed\n");\
	exit(1);}

/**
 * read_forest_table accepts a variables of type pointer to file and int.
 * the functions reads from the file a table in dimensions of the given int.
 * the table represent the inital status of the forest.
 * the function dynamically allocates memory for a new string that holds the same table in one string.  
 * Parameters:
 * ----------
 * input_file - the file to be read.
 * dim - the dimension of the table to be read (symmetric table)
 */
void read_forest_table(FILE * input_file, unsigned int dim);

void print_next_generation(unsigned int dimensions, FILE * output_file);

void free_forest_table();

#endif
#pragma once
