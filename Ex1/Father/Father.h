#ifndef	FATHER_H
#define FATHER_H

#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55
#define ALLOCATION_ERROR(NAME) if (NAME == NULL) {\
	printf("allocation failed\n");\
	exit(1);}


void read_forest_table(FILE * input_file, unsigned int dim);
void print_next_generation(unsigned int dimensions, FILE * output_file);
void free_forest_table();

#endif
#pragma once
