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

	// Get input and output file names
	// If not provided upon loading, Prompt for them
	switch (argc) {
		case 1:
			// No arguments passed from command line
			printf("Please enter an input file name ");
			scanf("%s", inFile);
		case 2:
			// Only one argument passes from command line
		    // OR fell from above (no break statement)
			printf("Please enter an output file name ");
			scanf("%s", outFile);
			break;
		default:
			strcpy(inFile, args[1]);
			strcpy(outFile, args[2]);
	}
	printf("Input file: %s OutputFile %s", inFile, outFile);
}