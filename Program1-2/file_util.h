#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#define MAX_CHAR 50
#define INEXT ".IN"
#define OUTEXT ".OUT"
#define BACKEXT ".BAK"
#define LISTEXT ".LIS"
#define TEMPFILENAME "temporary.TEMP"

FILE *inFile;
FILE *outFile;
extern int go;
extern int overwrite;

int i;
char inputFilename[MAX_CHAR];
char outputFilename[MAX_CHAR];
char choice[MAX_CHAR];
char inExtention[MAX_CHAR];
char outExtention[MAX_CHAR];

char* getInFile(char* file);
char* getOutFile(char* file, char* defaultName);
void copyFile(char* in, char* out);
void backupFile(char* file);
void createListingFile(char* file);
void createTempFile();
void removeTempFile();

#endif