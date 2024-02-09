#include <stdio.h> 
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>

/* function declaration to list all files in given directory recursively */
void listFilesRecursively(char *basePath, int *count);

/* code provided in lab assignment, only adjustment is calling to 
listFilesRecursively at the end */
int main (int argc, char **argv) { 
    if (argc < 2) { 
        printf ("Usage: %s <dirname>\n", argv[0]); 
        exit(-1);
    } 

    int count = 1; 
    printf("Listing files and directories in: %s\n", argv[1]);
    listFilesRecursively(argv[1], &count); /* starting recursive traversal */

    return 0; 
} 

/* utilizing struct used in original code to list all files in directory recursively */
void listFilesRecursively(char *basePath, int *count) {
    struct dirent *dirent; 
    DIR *parentDir; 

    /* opening directory w/ error handling */
    parentDir = opendir (basePath); 
    if (parentDir == NULL) { 
        printf ("Error opening directory '%s'\n", basePath); 
        exit (-1);
    } 

    /* moved from main function in provided code*/
    while((dirent = readdir(parentDir)) != NULL){ 
      /* ignoring "." and ".." to avoid infinite loops */
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0) {
            printf ("[%d] %s\n", *count, dirent->d_name); 
            (*count)++; 

            char path[1024];
            snprintf(path, sizeof(path), "%s/%s", basePath, dirent->d_name);

            /* if current file = directory, call listFilesRecursively again */
            if (dirent->d_type == DT_DIR) {
                listFilesRecursively(path, count);
            }
        }
    } 
    closedir (parentDir); 
}