#include "packer.h"

BOOL FilePack(char * DirName,char * Filename)
{
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    char name[100]={'\0'};
    char buff[256]={'\0'};
    char *ptr=NULL;

int fd,fdread,retread,ret,fdnew,temp,icnt=0;
char key;
FILEINFO obj;

if((dir=opendir(DirName))==NULL)
{
    printf("Error : Unable to open specified directory\n");
    return ERR_ACCESS;
}

fd=creat(Filename,0666);
if(fd==-1)
{
    printf("Error : Unable to create file\n");
    return ERR_ACCESS;
}

key=strlen(Filename);

write(fd,"Marvellous21",strlen("Marvellous21"));
write(fd,&key,1);

printf("key written\n");
while((entry=readdir(dir))!=NULL)
{
    sprintf(name,"%s/%s",DirName,entry->d_name);
    stat(name,&filestat);
    if(S_ISREG(filestat.st_mode))
    {
        fdread=open(name,O_RDONLY);
        strcpy(obj.name,entry->d_name);
        obj.size=filestat.st_size;

        write(fd,&obj,sizeof(obj));
        while((retread=read(fdread,buff,sizeof(buff)))!=0)
        {
            temp=retread;
            while(temp!=0)
            {
                buff[temp]+=key;
                temp--;
            }
            write(fd,buff,retread);
        }
        close(fdread);
        icnt++;
    }
}
closedir(dir);
printf("%d File Successfully combined\n",icnt);
return SUCCESS;
}

BOOL FileUnpack(char *FileName)
{
    DIR *dir;
    struct dirent *entry;
    struct stat filestat;
    char name[100]={'\0'};
    char buff[256]={'\0'};
    char *ptr=NULL;

    int fd,fdread,retread,ret,fdnew,temp,icnt=0;
    char key;
    FILEINFO obj;

    fd=open(FileName,O_RDONLY);
    if(fd==-1)
    {
        printf("Error: Unable to open file\n");
        return ERR_ACCESS;
    }
    ret=read(fd,buff,strlen("Marvellous21"));
    if(ret<=0)
    {
        printf("Error : Unable to open file\n");
        return ERR_ACCESS;
    }
    if(strcmp(buff,"Marvellous21")!=0)
    {
        printf("Error:unable to open file\n");
        return ERR_INVALID;
    }
    read(fd,&key,1);
    while((ret=read(fd,&obj,sizeof(obj)))!=0)
    {
        fdnew=creat(obj.name,0666);

        ptr=(char *)malloc(obj.size*sizeof(char));
        read(fd,ptr,obj.size);

        temp=obj.size;
        while(temp!=0)
        {
            ptr[temp]-=key;
            temp--;
        }
        write(fdnew,ptr,obj.size);
        close(fdnew);
        free(ptr);
        icnt++;
    }
    close(fd);
    printf("%d File SuccessFully recreated\n",icnt);
    return SUCCESS;
}

void DisplayHelp()
{
    printf("\n------------File Packer Unpacker-----------------\n");
    printf("Developed by -Marvellous Infosystems\n");
    printf("----------------------------------------------------\n\n");
    printf("To Pack files\n");
    printf("Exe_name_ -p Directory_Name File_Name\n\n");
    printf("To Unpack files\n");
    printf("Exe_name -u Merge_File_Name\n\n");
}

void DisplayError(BOOL ret)
{
    switch(ret)
    {
        case ERR_INVALID:
            printf("Error:Invalid file for Unpacking");
            break;
        case ERR_ACCESS:
            printf("Error: Access denied");
            break;
    }
}


