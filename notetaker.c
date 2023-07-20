#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

void usage(char *prog_name, char *filename)
{
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(0);
}

void fatal(char *);            // A function for fatal errors
void *ec_malloc(unsigned int); // An error-checked malloc() wrapper

int main(int argc, char *argv[])
{
    FILE *fd; // File descriptor
    int userid;
    char *buffer, *datafile;
    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);
    strcpy(datafile, "notetaker.txt");

    if (argc < 2)                 // If there aren't command-line arguments,
        usage(argv[0], datafile); // display usage message and exit.

    strcpy(buffer, argv[1]); // Copy into buffer.
    printf("[DEBUG] buffer @ %p: \'%s\'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: \'%s\'\n", datafile, datafile);

    // Opening the file
    fd = fopen(datafile, "a+");

    if (fd == NULL)
        fatal("in main() while opening file");

    printf("[DEBUG] file descriptor is %d\n", fd);

    if (fwrite("\n", sizeof(char), 1, fd) == -1)
    {
        fatal("in main() while adding new line to file");
    }

    if (fwrite(buffer, sizeof(buffer), 1, fd) == -1)
    {
        fatal("in main() while writing buffer to file");
    }

    if (fclose(fd) == -1)
        fatal("in main() while closing file");

    printf("Note has been saved.\n");

    free(buffer);
    free(datafile);
}