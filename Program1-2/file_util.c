#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_util.h"


char* getInFile(char* filename) {
	char temp[MAX_CHAR] = "";
	// If filename has not been provided from command prompt
	if(filename[0] == '\0'){
		printf("Please enter an input file name. ");
		printf("Enter nothing to quit.\n");
		strcpy(temp,"");
		gets(temp);
		if(temp[0] == '\0'){
			go = 0;
			return "";
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
		strcpy(temp,"");
		gets(temp);
		if(temp[0] == '\0'){
			go = 0;
			return "";
		}
		strcpy(filename, temp);
	}
	// Make a persistent copy for use in getOutFile() if needed
	strcpy(inputFilename, filename);	
	fclose(inFile);
	return(filename);
}

char* getOutFile(char* filename, char* defaultName) {
	char temp[MAX_CHAR] = "";

	// If filename has not been provided from command prompt
	if(filename[0] == '\0'){
		printf("Please enter an output file name.\n");
		printf("If nothing is entered, the input filename will be ");
		printf("used with the .OUT extention.\n");
		temp[0] = '\0';
		gets(temp);
		if(temp[0] == '\0'){
			//strip extention from default
			if(strchr(defaultName, '.')){
				i = 0;
				while(defaultName[i] != '.'){
					temp[i] = defaultName[i];
					i++;
				}
				temp[i] = '\0';
			}
		}
		strcpy(filename, temp);
	}

	// Check for file extention
	if(!(strchr(filename, '.'))){
		strcat(filename, OUTEXT);
	}
	// Check if file does not exists - open it
	while((outFile = fopen(filename, "r")) && overwrite == 0){
		printf("File already exists.\n");
		printf("Enter 1 to enter a new file name.\n");
		printf("Enter 2 to overwrite %s\n", filename);
		printf("Enter nothing to quit.\n");
		strcpy(choice,"");
		gets(choice);
		if(choice[0] == '1'){
			printf("Please enter an output file name.\n");
			printf("If nothing is entered, the input filename will be ");
			printf("used with the .OUT extention.\n");
			temp[0] = '\0';
			gets(temp);
			if(temp[0] == '\0'){
				//strip extention from default
				if(strchr(defaultName, '.')){
					i = 0;
					while(defaultName[i] != '.'){
						temp[i] = defaultName[i];
						i++;
					}
					temp[i] = '\0';
				}
			}
		} else if (strcmp(choice,"2")){
			overwrite = 1;
		} else if (strcmp(choice,"")){
			go = 0;
			return "";
		}
		strcpy(filename, temp);
		fclose(outFile);
	}
	fclose(outFile);
	strcpy(outputFilename, filename);
	return(filename);
}

void copyFile(char* in, char* out){
	char c;
	inFile = fopen(in, "r");
	outFile = fopen(out, "w");
	//printf("hello from copyFile()");
	while((c = fgetc(inFile)) != EOF){
		fputc(c, outFile);
	}
	fclose(inFile);
	fclose(outFile);
}

void backupFile(char* file){
	char c;
	char back[MAX_CHAR] = "";
	i = 0;
	//strip extention from default
	if(strchr(file, '.')){
		while(file[i] != '.'){
			back[i] = file[i];
			i++;
		}
		back[i] = '\0';
	} else {
		strcpy(back, file);
	}
	strcat(back, BACKEXT);
	copyFile(file, back);
}