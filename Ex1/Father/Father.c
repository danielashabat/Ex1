
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Father.h"

static void change_fire_to_ground(char* forest_table, char* new_forest_table, unsigned int d);
static int is_on_fire(char block_state);
static void find_trees_around(int i, char* forest_table, unsigned int d, int j, char* new_forest_table);

static char* forest_table;

void father(FILE* input_file, FILE* output_file) {
	unsigned int dimensions;
	unsigned int generations;
	//char *forest_table = { 0 };
	int i = 1;
	int num_of_burned_tree = 0;
	fscanf(input_file , "%u\n%u\n", &dimensions, &generations); //reading variables from input file
	//printf("%u\n%d\n", dimensions, generations);
	forest_table = allocate_memory_to_forest_string(dimensions);
	read_forest_table(input_file,forest_table,dimensions);
	num_of_burned_tree = CreateProcessSimpleMain(forest_table);
	printf("%s - %d \n", forest_table,num_of_burned_tree);
	while (i < generations) {
		forest_table = load_next_generation(forest_table, dimensions);
		num_of_burned_tree = CreateProcessSimpleMain(forest_table);
		printf("%s - %d\n", forest_table, num_of_burned_tree);
		i++;
	}
	

	free(forest_table);
}


static char* load_next_generation(char * forest_table, unsigned int dimensions) {

	char* new_forest_table = { 0 };
	new_forest_table = allocate_memory_to_forest_string(dimensions);
	
	strcpy(new_forest_table, forest_table);//copy forest_table to new variable

	change_fire_to_ground(forest_table, new_forest_table,dimensions);
	change_ground_to_tree(forest_table,new_forest_table,  dimensions);
	spread_fire(forest_table, new_forest_table, dimensions);
	free(forest_table);//free old forest table
	return new_forest_table;//
}
//fire tree changes to ground 
static void change_fire_to_ground (char* forest_table, char* new_forest_table, unsigned int d){
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			if (forest_table[i*d+j] == 'F') {
				new_forest_table[i*d+j] = 'G';
			}
		}
	}
}
//if ground is nearby at least two trees it's changes to a new tree (include diagonal neighbors)
static void change_ground_to_tree(char* forest_table, char* new_forest_table, unsigned int d) {
	int counter = 0;
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			if (forest_table[i*d+j] == 'G') {
				counter = 0;//search for near trees
				if(i > 0) //check from above
					if (forest_table[d*(i-1)+j] == 'T') counter++;
				if (i <(d-1)) //check from below
					if (forest_table[(i + 1)*d+j] == 'T') counter++;
				if (j < (d - 1)) //check from the right
					if (forest_table[i*d +j+1] == 'T') counter++;
				if (j >0) //check from the left
					if (forest_table[i*d +j - 1] == 'T') counter++;
				if (i > 0 && j>0) //check from upper-left diagonal
					if (forest_table[d*(i - 1)+(j-1)] == 'T') counter++;
				if (i <(d - 1) && j > 0) //check from down-left diagonal
					if (forest_table[(i + 1)*d+j - 1] == 'T') counter++;
				if (i>0 && j < (d - 1)) //check from upper-right diagonal
					if (forest_table[(i - 1)*d+j + 1] == 'T') counter++;
				if (i < (d - 1) && j < (d - 1)) //check from down-right diagonal
					if (forest_table[(i+ 1)*d+j + 1] == 'T') counter++;

				if (counter > 1)//if counter a least 2 the ground changes to tree
					new_forest_table[i*d +j] = 'T';
			}
		}
	}
}
//fire spreads to all the nearby trees (not include diagonal neighbors)
static void spread_fire(char* forest_table, char* new_forest_table, unsigned int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int current_block_index = i * dim + j;
			if (is_on_fire(forest_table[current_block_index])) {
				find_trees_around(i, forest_table, dim, j, new_forest_table);
			}
		}
	}
}

static int is_on_fire(char block_state)
{
	return (block_state == 'F');
}

static void find_trees_around(int i, char* forest_table, unsigned int d, int j, char* new_forest_table)
{
	//search for near trees
	if (i > 0) //check from above
		if (forest_table[(i - 1) * d + j] == 'T')
			new_forest_table[(i - 1) * d + j] = 'F';
	if (i < (d - 1)) //check from below
		if (forest_table[(i + 1) * d + j] == 'T')
			new_forest_table[(i + 1) * d + j] = 'F';
	if (j < (d - 1)) //check from the right
		if (forest_table[i * d + j + 1] == 'T')
			new_forest_table[i * d + j + 1] = 'F';
	if (j > 0) //check from the left
		if (forest_table[i * d + j - 1] == 'T')
			new_forest_table[i * d + j - 1] = 'F';
}


//asssign new memory for string according the dimensions variable from user   
//output:return pointer to 2D array represent the forest table data
 char* allocate_memory_to_forest_string(unsigned int dimensions) {
	char* new_ptr = NULL;

	new_ptr = (char*)malloc((dimensions* dimensions+1)*sizeof(char));//create 2D array, need +1 for ending '\0'
	ALLOCATION_ERROR(new_ptr);//check if the allocaton failed
	return new_ptr;
}


//reading forest table from input file and assign it into 2D array
static void read_forest_table(FILE* input_file,unsigned int d) {
	unsigned int i = 0;
	unsigned int j = 0;
	
	for (i = 0; i < d; i++) {
		for (j = 0; j < d; j++) {
			if (!feof(input_file)) {
				forest_table[i*d + j] = fgetc(input_file);
				fgetc(input_file);//filtering ',' or '\n'
			}
			else {
				printf("ERROR:table data not matched to dimensions!");
				exit(1);////***need to close files
			}
		}
	}
	forest_table[i*d] = '\0'; //add in the end of the array

}

