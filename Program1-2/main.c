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
#include <stdlib.h>
#include "file_util.h"

extern FILE *inFile;
extern FILE *outFile;
int go = 1;
int overwrite = 0;

int main(int argc, char** args) {
	char argIn[MAX_CHAR];
	char argOut[MAX_CHAR];
	
	// Handle input file
	if(go){
		if (argc > 1){
			strcpy(argIn, args[1]);
		} 
		getInFile(argIn);
	}
	// Handle output file
	if(go){
		if (argc > 2){
			strcpy(argOut, args[2]);
		}
		getOutFile(argOut);
	}
	// Handle backup 
	if(overwrite && go){
		printf("overwrite =%d\n",overwrite);
	}
	// File copy

	copyFile(inFile, outFile);
	
	
	fclose(inFile);
	fclose(outFile);
}
