#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int system(const char *command);

int main(){

    const char *notification = "Hallo\n";

    // Open the command for reading
    FILE *input;
    char files[50];

    input = popen("/bin/ls /dev/pts", "r");
    if (input == NULL){
        printf("Failes to run command: ls\n");
    }

    // Read the output a line at a time
    while(fgets(files, sizeof(files), input) != NULL)
    {
        // files: 0, 1, 2, ptmx
        // printf("%s", files);

        // Remove last char "\n"
        files[strlen(files)-1] = '\0';

        char complete_path[60];
        strcpy(complete_path, "/dev/pts/");
        strcat(complete_path, files);

        // Open each file
        FILE *f = fopen(complete_path, "w"); 

        if (f == NULL)
        {
            printf("Cant open file %s!\n", complete_path);
            exit(1);
        }
        fprintf(f, notification);
        fclose(f);


    }

    fclose(input);



    // Write to device file
    // FILE *f = fopen("/dev/pts/0", "w");

    // if (f == NULL)
    // {
    //     printf("Error opening file!\n");
    //     exit(1);
    // }


    
    

    // system("echo 'Hallo.' > /dev/pts/0");

    return 0;

}

