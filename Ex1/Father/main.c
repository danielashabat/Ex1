///FILE COMMENTS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


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
	father(input_file, output_file);

	fclose(input_file);
	fclose(output_file);
	return 0;
}