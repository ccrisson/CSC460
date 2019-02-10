#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#define MAX_CHAR 50
#define INEXT ".IN"
#define OUTEXT ".OUT"

FILE *inFile;
FILE *outFile;
extern int go;
extern int overwrite;

char inputFilename[MAX_CHAR];
char outputFilename[MAX_CHAR];
char choice[MAX_CHAR];
char inExtention[MAX_CHAR];
char outExtention[MAX_CHAR];

void getInFile(char* file);
void getOutFile(char* file);
void copyFile(FILE *inFile, FILE *outFile);

#endif