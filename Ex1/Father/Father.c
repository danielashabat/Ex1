
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Father.h"

void father(FILE* input_file, FILE* output_file) {
	unsigned int dimensions;
	unsigned int generations;
	char **forest_table = { 0 };
	int i = 1;

	fscanf(input_file , "%u\n%u\n", &dimensions, &generations); //reading variables from input file
	//printf("%u\n%d\n", dimensions, generations);
	forest_table = allocate_memory_to_forest_table(dimensions);
	read_forest_table(input_file,forest_table,dimensions);

	printf("{%s} {%s}{%s}{%s}\n", forest_table[0], forest_table[1], forest_table[2], forest_table[3]);
	while (i < generations) {
		forest_table = load_next_generation(forest_table, dimensions);
		printf("{%s} {%s}{%s}{%s}\n", forest_table[0], forest_table[1], forest_table[2], forest_table[3]);
		i++;
	}
	

	free_forest_table(forest_table, dimensions);
}


char** load_next_generation(char ** forest_table, unsigned int dimensions) {

	char** new_forest_table = { 0 };
	new_forest_table = allocate_memory_to_forest_table(dimensions);
	for (int i = 0; i < dimensions; i++)//copy forest_table to new variable
		strcpy(new_forest_table[i], forest_table[i]);

	change_fire_to_ground(forest_table, new_forest_table,dimensions);
	change_ground_to_tree(forest_table,new_forest_table,  dimensions);
	spread_fire(forest_table, new_forest_table, dimensions);
	free_forest_table(forest_table, dimensions);
	return new_forest_table;
}
//fire tree changes to ground 
void change_fire_to_ground (char** forest_table, char** new_forest_table, unsigned int dimensions){
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			if (forest_table[i][j] == 'F') {
				new_forest_table[i][j] = 'G';
			}
		}
	}
}
//if ground is nearby at least two trees it's changes to a new tree (include diagonal neighbors)
void change_ground_to_tree(char** forest_table, char** new_forest_table, unsigned int dimensions) {
	int counter = 0;
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			if (forest_table[i][j] == 'G') {
				counter = 0;//search for near trees
				if(i > 0) //check from above
					if (forest_table[i-1][j] == 'T') counter++;
				if (i <(dimensions-1)) //check from below
					if (forest_table[i + 1][j] == 'T') counter++;
				if (j < (dimensions - 1)) //check from the right
					if (forest_table[i][j+1] == 'T') counter++;
				if (j >0) //check from the left
					if (forest_table[i][j - 1] == 'T') counter++;
				if (i > 0 && j>0) //check from upper-left diagonal
					if (forest_table[i - 1][j-1] == 'T') counter++;
				if (i <(dimensions - 1) && j > 0) //check from down-left diagonal
					if (forest_table[i + 1][j - 1] == 'T') counter++;
				if (i>0 && j < (dimensions - 1)) //check from upper-right diagonal
					if (forest_table[i - 1][j + 1] == 'T') counter++;
				if (i < (dimensions - 1) && j < (dimensions - 1)) //check from down-right diagonal
					if (forest_table[i+ 1][j + 1] == 'T') counter++;

				if (counter > 1)//if counter a least 2 the ground changes to tree
					new_forest_table[i][j] = 'T';
			}
		}
	}
}
//fire spreads to all the nearby trees (not include diagonal neighbors)
void spread_fire(char** forest_table, char** new_forest_table, unsigned int dimensions) {
	for (int i = 0; i < dimensions; i++) {
		for (int j = 0; j < dimensions; j++) {
			if (forest_table[i][j] == 'F') {
				//search for near trees
				if (i > 0) //check from above
					if (forest_table[i - 1][j] == 'T')
						new_forest_table[i - 1][j] = 'F';
				if (i < (dimensions - 1)) //check from below
					if (forest_table[i + 1][j] == 'T')
						new_forest_table[i + 1][j] = 'F';
				if (j < (dimensions - 1)) //check from the right
					if (forest_table[i][j + 1] == 'T')
						new_forest_table[i][j + 1] = 'F';
				if (j > 0) //check from the left
					if (forest_table[i][j - 1] == 'T')
						new_forest_table[i][j - 1] = 'F';
			}
		}
	}
}


//asssign new memory for table according the dimensions variable from user
char** allocate_memory_to_forest_table(unsigned int dimensions) {
	char** new_ptr = NULL;
	unsigned int rows = dimensions;
	unsigned int columns = (dimensions+1); //+1 for ending '\0' 
	unsigned int i = 0;
	new_ptr = (char**)malloc(rows*sizeof(char*));
	ALLOCATION_ERROR(new_ptr);
	for (i = 0; i < rows; i++)
		new_ptr[i] = NULL;

	for (i = 0; i < rows; i++) {
		new_ptr[i] = (char*)malloc(columns * sizeof(char));
		ALLOCATION_ERROR(new_ptr[i])
	}
	return new_ptr;
}

void free_forest_table(char** forest_table, unsigned int dimensions) {
	for (int i = 0; i < dimensions; i++) 
		free(forest_table[i]);
	free(forest_table);
}

//reading forest table from input file and assign it into 2D array
void read_forest_table(FILE* input_file,char **forest_table,unsigned int dimensions) {
	unsigned int i = 0;
	unsigned int j = 0;
	
	for (i = 0; i < dimensions; i++) {
		for (j = 0; j < dimensions; j++) {
			if (!feof(input_file)) {
				forest_table[i][j] = fgetc(input_file);
				fgetc(input_file);//filtering ',' or '\n'
			}
			else {
				printf("ERROR:table data not matched to dimensions!");
				exit(1);
			}
		}forest_table[i][j] = '\0';
	}

}