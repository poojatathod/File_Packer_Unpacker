#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>
#include<sys/stat.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

#define SUCCESS 1
#define ERR_ACCESS 2
#define ERR_INVALID 3
#define TRUE 1
#define FALSE 0
typedef int BOOL;
typedef struct
{
    char name[50];
    int size;
}FILEINFO;

BOOL FilePack(char *,char *);
BOOL FileUnpack(char *);
void DisplayHelp();
void DisplayError(BOOL);

