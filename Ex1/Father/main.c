#include <stdio.h>

//command line: Fatther.exe, input.txt, output.txt
int main(int argc, char* argv[]) {
	FILE* input_file = NULL, * output_file = NULL;

	//check if there 2 arguments ****************

	//check if the files opened
	if ( NULL == (input_file = fopen(argv[1], "r")) ){
		printf("ERROR:can't open input file\n");
		return 1;
	}
	if (NULL == (output_file = fopen(argv[2], "w"))) {
		printf("ERROR:can't open output file\n");
		return 1;
	}

	fclose(input_file);
	fclose(output_file);
	return 0;
}