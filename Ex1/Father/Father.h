#ifndef	FATHER_H
#define FATHER_H

#define ALLOCATION_ERROR(NAME) if (NAME == NULL) {\
	printf("allocation failed\n");\
	exit(1);\
}
void father(FILE * input_file, FILE * output_file);
char** load_next_generation(char** forest_table, unsigned int dimensions);
char** allocate_memory_to_forest_table(unsigned int dimensions);
void free_forest_table(char** forest_table, unsigned int dimensions);
void read_forest_table(FILE * input_file, char** forest_table, unsigned int dimensions);
void change_fire_to_ground(char** forest_table, char** new_forest_table, unsigned int dimensions);
void change_ground_to_tree(char** forest_table, char** new_forest_table, unsigned int dimensions);
void spread_fire(char** forest_table, char** new_forest_table, unsigned int dimensions);
#endif
#pragma once
