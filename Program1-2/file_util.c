#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"


void getInFile(char* filename) {
	char temp[MAX_CHAR] = "";
	// If filename has not been provided from command prompt
	if(filename[0] == '\0'){
		printf("Please enter an input file name. ");
		printf("Enter nothing to quit.\n");
		gets(temp);
		if(temp[0] == '\0'){
			go = 0;
			return;
		}strcpy(filename, temp);
	} 
	// Check for file extention
	if(strchr(filename, '.')){
		strcpy(inExtention, (strchr(filename, '.')));
	} else {
		strcat(filename, INEXT);
	}
	// Check if file exists - open it
	while(!(inFile = fopen(filename, "r"))){
		printf("File not found. Enter another file name. ");
		printf("Enter nothing to quit.\n");
		gets(temp);
		if(temp[0] == '\0'){
			go = 0;
			return;
		}
		strcpy(filename, temp);
	}
	// Make a persistent copy for use in getOutFile() if needed
	strcpy(inputFilename, filename);	
	fclose(inFile);
}

void getOutFile(char* filename) {
	char temp[MAX_CHAR] = "";
	int validChoice = -1; // Loop controller - user input
	// If filename has not been provided from command prompt
	if(filename[0] == '\0'){
		printf("Please enter an output file name.\n");
		printf("If nothing is entered, the input filename will be ");
		printf("used with the .OUT extention.\n");
		gets(temp);
		if(strcmp(temp,"")){
			memcpy(temp, inputFilename,
				(strchr(inputFilename, '.') - inputFilename));
			strcat(temp, OUTEXT);
		}strcpy(filename, temp);
	}

	// Check for file extention
	if(strchr(filename, '.')){
		strcpy(inExtention, (strchr(filename, '.')));
	} else {
		strcat(filename, OUTEXT);
	}
	// Check if file does not exists - open it
	while((outFile = fopen(filename, "r")) || overwrite == 1){
		printf("File already exists.\n");
		while(!validChoice){
			printf("Enter 1 to enter a new file name.\n");
			printf("Enter 2 to overwrite %s\n", filename);
			printf("Enter nothing to quit.\n");
			gets(choice);
			if(strcmp(choice,"1")){
				validChoice = 1;
				gets(temp);
				strcpy(filename, temp);
			} else if (strcmp(choice,"2")){
				validChoice = 1;
				overwrite = 1;
			} else if (choice[0] == '\0'){
				go = 0;
				return;
			}
		}
		

		strcpy(filename, temp);
	}
	fclose(outFile);
	strcpy(outputFilename, filename);
}

void copyFile(FILE *inFile, FILE *outFile){
	char c;
	inFile = fopen(inputFilename, "r");
	outFile = fopen(outputFilename, "w");
	printf("hello from copyFile()");
	while((c = fgetc(inFile)) != EOF){
		fputc(c, outFile);
	}
}