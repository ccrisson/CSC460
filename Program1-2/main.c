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
	char choice[MAX_CHAR];
	int validChoice;

	while(go){
		validChoice = -1;
		// Handle input file
		if(go){
			if (argc > 1){
				strcpy(argIn, args[1]);
			} 
			strcpy(inputFile,getInFile(argIn));
		}
		// Handle output file
		if(go){
			if (argc > 2){
				strcpy(argOut, args[2]);
			}
			strcpy(outputFile,getOutFile(argOut, inputFile));
		}
		// Handle backup 
		if((overwrite == 1) && go){
			backupFile(outputFile);
		}
		// File copy
		if(go){
			if(copyFile(inputFile, outputFile) == 1){
				createListingFile(outputFile);
				createTempFile();
			}
			//removeTempFile();
		}
		// Prompt to go again or quit
		if(go){
			while(validChoice != 1){
				printf("Enter 1 to Continue.\n");
				printf("Enter 2 to Quit\n");
				choice[0] = '\0';
				gets(choice);
				if(choice[0] == '1'){
					validChoice = 1;
					// Reset args to prevent infinite loop
					argIn[0] = '\0';
					argOut[0] = '\0';
					argc = 0;
				} else if(choice[0] == '2'){
					validChoice = 1;
					go = 0;
				}
			}
		}
	}
	return 0;
}
