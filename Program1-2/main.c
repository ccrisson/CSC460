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

int go = 1;
int overwrite = 0;

int main(int argc, char** args) {
	char argIn[MAX_CHAR];
	char argOut[MAX_CHAR];
	char inputFile[MAX_CHAR];
	char outputFile[MAX_CHAR];
	
	// Handle input file
	if(go){
		if (argc > 1){
			strcpy(argIn, args[1]);
		} 
		strcpy(inputFile,getInFile(argIn));
		printf("%s\n",inputFile);
	}
	// Handle output file
	if(go){
		if (argc > 2){
			strcpy(argOut, args[2]);
		}
		strcpy(outputFile,getOutFile(argOut, inputFile));
	}
	// Handle backup 
	if(overwrite == 1 && go){
		backupFile(outputFile);
	}
	// File copy
	if(go){
		copyFile(inputFile, outputFile);
	}
	
	//fclose(inFile);
	//fclose(outFile);
}
