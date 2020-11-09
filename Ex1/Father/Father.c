
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
/*
 Authors: Anat Sinai 312578149 and Daniela Shabat 316415645
 This project was written for Tel Aviv unviersity course for learning about creating processes
 Project name: 'Exercise 1'
 decsription:in this module written all the implemantation of functions that belong to the father. 
*/
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <windows.h>
//#include <tchar.h>
#include "Father.h"
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

/* function declarations for static functions ( internal functions that */
/* are not visible outside this file ) */
static void change_fire_to_ground(char* new_forest_table, unsigned int dim);
static void change_ground_to_tree(char* new_forest_table, unsigned int dim);
static void spread_fire(char* new_forest_table, unsigned int dim);
static void find_trees_around(int i, char* forest_table, unsigned int d, int j, char* new_forest_table);
static char* allocate_memory_to_forest_table(unsigned int dimensions);
static void print_to_output_file(FILE* output_file);
static int CreateProcessSimpleMain();
static BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr);
/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
//declaration on static variables
static char* forest_table;

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/
void print_next_generation(unsigned int dimensions,FILE* output_file) {

	char* new_forest_table = { 0 };
	new_forest_table = allocate_memory_to_forest_table(dimensions);
	strcpy(new_forest_table, forest_table);//copy forest_table to new variable

	print_to_output_file(output_file);
	change_fire_to_ground(new_forest_table,dimensions);
	change_ground_to_tree(new_forest_table,  dimensions);
	spread_fire(new_forest_table, dimensions);
	free(forest_table);//free old forest table
	forest_table = new_forest_table;
}
//fire tree changes to ground 
static void change_fire_to_ground ( char* new_forest_table, unsigned int dim){
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (forest_table[i*dim+j] == 'F') {
				new_forest_table[i*dim+j] = 'G';
			}
		}
	}
}
//if ground is nearby at least two trees it's changes to a new tree (include diagonal neighbors)
static void change_ground_to_tree(char* new_forest_table, unsigned int dim) {
	int counter = 0;
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			if (forest_table[i*dim+j] == 'G') {
				counter = 0;//search for near trees
				if(i > 0) //check from above
					if (forest_table[dim*(i-1)+j] == 'T') counter++;
				if (i <(dim-1)) //check from below
					if (forest_table[(i + 1)*dim+j] == 'T') counter++;
				if (j < (dim - 1)) //check from the right
					if (forest_table[i*dim +j+1] == 'T') counter++;
				if (j >0) //check from the left
					if (forest_table[i*dim +j - 1] == 'T') counter++;
				if (i > 0 && j>0) //check from upper-left diagonal
					if (forest_table[dim*(i - 1)+(j-1)] == 'T') counter++;
				if (i <(dim - 1) && j > 0) //check from down-left diagonal
					if (forest_table[(i + 1)*dim+j - 1] == 'T') counter++;
				if (i>0 && j < (dim - 1)) //check from upper-right diagonal
					if (forest_table[(i - 1)*dim+j + 1] == 'T') counter++;
				if (i < (dim - 1) && j < (dim - 1)) //check from down-right diagonal
					if (forest_table[(i+ 1)*dim+j + 1] == 'T') counter++;

				if (counter > 1)//if counter a least 2 the ground changes to tree
					new_forest_table[i*dim +j] = 'T';
			}
		}
	}
}
//fire spreads to all the nearby trees (not include diagonal neighbors)
static void spread_fire(char* new_forest_table, unsigned int dim) {
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			int current_block_index = i * dim + j;
			if (forest_table[current_block_index]=='F'){
				find_trees_around(i, forest_table, dim, j, new_forest_table);
			}
		}
	}
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
//output:return pointer to char array represent the forest table data
static char* allocate_memory_to_forest_table(unsigned int dimensions) {
	char* new_ptr = NULL;
	new_ptr = (char*)malloc((dimensions* dimensions+1)*sizeof(char));//create 2D array, need +1 for ending '\0'
	if (new_ptr != NULL)
		return new_ptr;
	else 
	{
		printf("allocation failed\n");
		return EXIT_FAILURE;
	}
}
void free_forest_table() {
	free(forest_table);
}

//reading forest table from input file and assign it into char array
int read_forest_table(FILE* input_file,unsigned int dim ) {
	unsigned int i = 0;
	unsigned int j = 0;
	if ((forest_table = allocate_memory_to_forest_table(dim)) == EXIT_FAILURE)
		return EXIT_FAILURE;//allocation failed, return to main and end program
		for (i = 0; i < dim; i++) {
			for (j = 0; j < dim; j++) {
				if (!feof(input_file)) {
					forest_table[i * dim + j] = fgetc(input_file);
					fgetc(input_file);//filtering ',' or '\n'
				}
				else {
					printf("ERROR:table data not matched to dimensions!");
					return EXIT_FAILURE;////reading failed close all files and exit
				}
			}
		}
		forest_table[i * dim] = '\0'; //add in the end of the array
		return 0;
}

static void print_to_output_file(FILE* output_file) {
	fprintf(output_file,"%s - %d \n", forest_table, CreateProcessSimpleMain());
}


/***********Process functions**********************/

static int CreateProcessSimpleMain()

{
	TCHAR* project_name = L"Son.exe ";
	TCHAR command[0x100] = { 0 };
	wsprintf(command, TEXT("%s %hs"), project_name, forest_table);


	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;




	/*  Start the child process. */
	retVal = CreateProcessSimple(command, &procinfo);


	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return 1;
	}


	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */


	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10); /* Waiting a few milliseconds for the process to terminate,
					note the above command may also fail, so another WaitForSingleObject is required.
					We skip this for brevity */
	}

	GetExitCodeProcess(procinfo.hProcess, &exitcode);
	/* Note: process is still being tracked by OS until we release handles */
	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
	return exitcode;
}

/*oOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO*/

static BOOL CreateProcessSimple(LPTSTR CommandLine, PROCESS_INFORMATION* ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	return CreateProcess(
		NULL, /*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}