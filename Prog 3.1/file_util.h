#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#ifdef _MSC_VER 
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_CHAR 30
#define MAXBUFF 200
typedef struct tokn{
	const char *str;  	
	int len;		//Length of the token
	int num;		//Enumeration of the token
}token;				//Reference
FILE *input,*output,*listing,*tmp,*back_up;
int tokNum;
int getInFile(int arg_count,  char * argv[],FILE **input); 					//Reads input and opens input file if exists
int getOutFile(int arg_count,  char * argv[], FILE **output, FILE **listing, FILE **tmp); 	//Gets input and checks if output file exists
void copy_backup(char *outFile);  								//Copies current contents of output to backup file
void clear_lineBuff(char * lineBuff);								//Nullifies line buffer between each line of input
void printToken(FILE *input, FILE *output,token tok[],int count, char *lineBuff);		//Prints the token to the appropriate files
void ParseTokens(token tok[],int tokperline[]);
void closeFiles(FILE *input, FILE *output, FILE *listing, FILE *tmp);   			//Close all opened files
void scanner (FILE *input, FILE *output, FILE *listing);					//Reads line from input and process line, continues until input eof
int Tokenize( char *lineBuff,  token tok[]);							//Breaks line into tokens calls functions to identify token type	
void ident_token(int count, token tok[]);							//Identifies token type and sets enumeration value of that token
int checkReserved(token tmp);									//Check if token is a reserved word or variable
int checkInt(token tmp);									//Check if token is an integer
int checkSymbol(token tmp);									//Checks if token is a reserved symbol
int BEGIN(FILE *listing, token tok[],int i, int tokperline[]);
int STMTLIST(FILE *listing,token tok[], int i, int tokperline[]);
int STMT(FILE *listing, token tok[], int i, int tokperline[]);
int ID(FILE *listing, token tok[], int i, int tokeperline[]);
int WRITE(FILE *listing, token tok[], int i, int tokperline[]);
int READ(FILE *listing, token tok[], int i, int tokperline[]);
int IF(FILE *listing, token tok[], int i, int tokperline[]);
int WHILE(FILE *listing, token tok[], int i, int tokperline[]);
int IDLIST(FILE *listing, token tok[], int i, int tokperline[]);
int EXPRESSION(FILE *listing, token tok[], int i, int tokperline[]);
int SEMI(FILE *listing, token tok[], int i, int tokperline[]);
int CONDITION(FILE *listing, token tok[], int i, int tokperline[]);
int NOTCOND(FILE *listing, token tok[], int i, int tokperline[]);
int RELATECOND(FILE *listing, token tok[], int i ,int tokperline[]);
void END(FILE * listing, token tok[], int i, int tokperline[]);
void printListing(int tokperline[]);



#endif
