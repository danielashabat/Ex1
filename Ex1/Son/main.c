/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 Authors: Anat Sinai 312578149 and Daniela Shabat 316415645
 This project was written for Tel Aviv unviersity course for learning about creating processes
 Project name: 'Exercise 1'
 decsription: this module runs the son's main of the project
*/
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
int calculate_number_of_burned_trees(char* forest_table);
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

int main(int argc, char* argv[]) {
	
	int num_of_burned_trees = 0;
	//checking that we got enough argument  
	if (argc < 2) {
		printf("ERROR:not enough arguments!");
		return 1;
	}
	else if (argc > 2) {
		printf("ERROR:too many arguments!");
		return 1;
	}
	else {
		//getting foredt table string from the father program  
		char* forest_string = argv[1];
		num_of_burned_trees = calculate_number_of_burned_trees(forest_string);
	}
	return num_of_burned_trees;
}

// find how much burend trees we have in the forest
//every burn free mark as 'F' so we count all 'F' in the forest string
int calculate_number_of_burned_trees(char* forest_table) {
	int number_of_burned_tree = 0;
	for (int i = 0; i < strlen(forest_table); i++) {
		if (forest_table[i] == 'F') {
			number_of_burned_tree++;
		}
	}
	return number_of_burned_tree;
}