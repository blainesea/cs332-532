#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
    int sourceFileDescriptor, destinationFileDescriptor;
    long int bytesRead;
    char buffer[BUFFSIZE];

    /* checking if correct num of args is provided from command line */
    if (argc != 3) {
        printf("Usage: %s <source_filename> <destination_filename>\n", argv[0]);
        exit(-1);
    }

    /* opening source file (file2) for reading */
    sourceFileDescriptor = open(argv[2], O_RDONLY);
    if (sourceFileDescriptor == -1) {
        printf("Error with file open\n");
        exit(-1);
    }

    /* openening the destination file (file1) for writing & appending to the end */
    destinationFileDescriptor = open(argv[1], O_CREAT | O_WRONLY | O_APPEND, 0700);
    if (destinationFileDescriptor == -1) {
        printf("Error with file open\n");
        close(sourceFileDescriptor); /* closing source file */
        exit(-1);
    }

    /* loop to read file and write to it */
    while ((bytesRead = read(sourceFileDescriptor, buffer, BUFFSIZE)) > 0) {
        if (write(destinationFileDescriptor, buffer, bytesRead) != bytesRead) {
            printf("Error writing to output file\n");
            exit(-1);
        }
    }
    /* error handling */
    if (bytesRead < 0) {
        printf("Error reading input file\n");
        exit(-1);
    }

    /* closing file descriptors */
    close(sourceFileDescriptor);
    close(destinationFileDescriptor);

    /* printing to console when program works succesfully */
    printf("Files concatenated successfully.\n");

    return 0;
}