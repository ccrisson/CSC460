/*Program1
  main.c
  CSC-460 Language Translation
  Group 9
  Chris Crisson CRI4537@calu.edu
  Matthew Bedillion BED9714@calu.edu
  Mark Blatnik BLA9072@calu.edu
  Adlene Bellaoucha BEL7984@calu.edu
*/
#include <stdio.h>
#include <string.h>

int main(int argc, char** args) {
	// Declare variables
	char inFile[50];
	char outFile[50];
	char choice;
	FILE *inFilePtr;
	FILE *outFilePtr;
	// Get input and output file names
	// If not provided upon loading, Prompt for them
	if (argc < 2) {
		printf("Please enter an input file name ");
		scanf("%s", inFile);
		while((inFilePtr = fopen(inFile, "r")) == NULL){
			printf("File not found. Enter another file name ");
			scanf("%s", inFile);
		}
	} else {
		strcpy(inFile, args[1]);
		while((inFilePtr = fopen(inFile, "r")) == NULL){
			printf("File not found. Enter another file name ");
			scanf("%s", inFile);
		}
	}
	if (argc < 3) {
		printf("Please enter an output file name ");
		scanf("%s", outFile);
		outFilePtr = fopen(outFile, "r");
		printf("%s", outFilePtr);
		while(outFilePtr = fopen(outFile, "r")){
			printf("File found. {R}e-enter, {O}verwrite ");
			scanf("%c", choice);
			// Handle choice
		}
	} else {
		strcpy(outFile, args[2]);
		// insert while looop from above when complete
		// should probably be a function
	}

	printf("Input file: %s OutputFile %s", inFile, outFile);
}