#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
    FILE *fp;
    char buf[100], namepro[100];
    int pid;

    if (argc == 2) {
        if (pid = atoi(argv[1])) {  // Convert argv[1] to integer (PID)
            sprintf(buf, "/proc/%d/cmdline", pid);  // Formulate the path to process command line
            if (fp = fopen(buf, "r")) {  // Open the file for reading
                fgets(namepro, 100, fp);  // Read the command line from the file
                puts(namepro);  // Print the command line (process name)
            } else {
                printf("don't have %d\n", pid);  // Print error message if file cannot be opened
            }
        }
    } else {
        puts("error syntax");  // Print error if command-line arguments are not exactly 2
    }
}
