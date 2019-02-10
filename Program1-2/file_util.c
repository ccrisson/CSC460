/*Program1
  file_util.c
  CSC-460 Language Translation
  Group 9
  Chris Crisson CRI4537@calu.edu
  Matthew Bedillion BED9714@calu.edu
  Mark Blatnik BLA9072@calu.edu
  Adlene Bellaoucha BEL7984@calu.edu
*/
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
		choice[0] = '\0';
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
		} else if (choice[0] == '2'){
			overwrite = 1;
			return filename;
		} else if (choice[0] == '\0'){
			go = 0;
			return "";
		}
		strcpy(filename, temp);
		// Check for file extention
		if(!(strchr(filename, '.'))){
			strcat(filename, OUTEXT);
			fclose(outFile);
		}
	}
	fclose(outFile);
	strcpy(outputFilename, filename);
	return(filename);
}

int copyFile(char* in, char* out){
	char c;
	if(strcmp(in,out)){
		inFile = fopen(in, "r");
		outFile = fopen(out, "w");
		while((c = fgetc(inFile)) != EOF){
			fputc(c, outFile);
		}
		fclose(inFile);
		fclose(outFile);
		return 1;
	} else {
		printf("File Copy Error. Both files have the same name.\n");
		return 0;
	}

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
	remove(file);
	return;
}

void createListingFile(char* file){
	char c;
	char list[MAX_CHAR] = "";
	i = 0;
	//strip extention from default
	if(strchr(file, '.')){
		while(file[i] != '.'){
			list[i] = file[i];
			i++;
		}
		list[i] = '\0';
	} else {
		strcpy(list, file);
	}
	strcat(list, LISTEXT);
	copyFile(file, list);
	return;
}

void createTempFile(){
	outFile = fopen(TEMPFILENAME, "w");
	fclose(outFile);
	return;
}

void removeTempFile(){
	if(remove(TEMPFILENAME) == 0){
		printf("Deleted %s successfully\n", TEMPFILENAME);
	}else {
		printf("Delete %s error\n", TEMPFILENAME);
	}
	return;
}