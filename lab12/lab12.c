#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

int main() {
    char command[1024];
    FILE *fp;
    char result[1024];

    while(1) {
        printf("Enter command: ");
        fflush(stdout); // Ensure 'Enter command' is displayed before fgets.
        if (!fgets(command, sizeof(command), stdin)) {
            perror("fgets failed");
            exit(EXIT_FAILURE);
        }

        // Trim the newline character from the command
        size_t length = strlen(command);
        if(length > 0 && command[length-1] == '\n') {
            command[length-1] = '\0';
        }

        // Check if the command is "quit" after trimming
        if (strcmp(command, "quit") == 0) {
            printf("Exiting program...bye!\n");
            break;
        }

        // Open the command for reading.
        fp = popen(command, "r");
        if (fp == NULL) {
            perror("Failed to run command");
            exit(EXIT_FAILURE);
        }

        // Read the output a line at a time - output it.
        while (fgets(result, sizeof(result), fp) != NULL) {
            printf("%s", result);
        }

        // Close the command stream
        pclose(fp);
    }

    return 0;
}
