#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_CHAR 30
#define MAXBUFF 200

FILE *input,*output,*listing,*tmp;
typedef struct tokn{
	const char *str;  	//the actual token
	int len;			//the length of the token
	int num;			//the enumeration of the token
}token;					// typedef to token for easier reference

int getInFile(int arg_count,  char * argv[], FILE ** input); 			//reads user input checks if  input file exists and opens it
int getOutFile(int arg_count,  char * argv[], FILE **output, FILE **listing, FILE **tmp); //gets user input  checks if output file exists, or opens a file input.OUT
void copy_backup(char *outFile);  										// copies current contents of output to backup file
void clear_lineBuff(char * lineBuff);									//nullifies line buffer between each line of input
void print_token(FILE *input, FILE *output, FILE *listing,token tok[]); //prints the token to appropriate files
void closeFiles(FILE *input, FILE *output, FILE *listing, FILE *tmp);   //closes all opened files
void scanner (FILE *input, FILE *output, FILE *listing);				//reads line from input and calls functions to process line, continues until input eof
int Tokenize( char *lineBuff,  token tok[]);							//breaks line into tokens calls functions to identify token type	
void ident_token(int count, token tok[]);								//identifies token type and sets enumeration value of that token
int checkReserved(token tmp);											//determines if token is a reserved word or variable
int checkInt(token tmp);												//determines if token is an int
int checkSymbol(token tmp);												// determines if token is a reserved symbol

#endif
