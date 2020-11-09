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
int read_forest_table(FILE * input_file, unsigned int dim);

/**
 * print_next_generation accepts a variables of type pointer to file and unsigned int.
 * the function loading the next generation of the forest table (according the excercise's rules) and prints the new table to output.txt file .
 * the function prints in the following format: "%s -$d" when the first string is the new forest table and the second int is the number of the 'Fire Trees' in the table   
 * the function create a new process for calculating the number of the 'Fire Trees' in the table 
 * Parameters:
 * ----------
 * output_file - the file to be printed to.
 * dim - the dimension of the forest table(symmetric table)
 */
void print_next_generation(unsigned int dimensions, FILE * output_file);

/**
 * this function free the memory that was allocated to the forest table.
 * forest table is a global variable thus there is no inputs.
 */
void free_forest_table();

#endif
#pragma once
