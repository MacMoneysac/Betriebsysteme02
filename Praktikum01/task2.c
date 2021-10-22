
// Linux – Prozesserzeugung und Prozessumgebungen

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
    int pid;
    pid = fork();
    pid = fork();

    char *new_name = "errorAAAAAAAAAAAA";

    strcpy(argv[0], new_name);

    // Hier Ausgabe von argv[]
    for (int i = 0; i < argc; i++)
    {
        printf("[%i] %s\n", i, argv[i]);
    }

    while (1)
    {
        sleep(20);
        break;
    }
}

// ./task2 das ist das haus von Nikolaus
// htop F4 filter: task2 oder error404

// Unterschied Braak and Return
// https://stackoverflow.com/questions/3463551/what-is-the-difference-between-exit-and-return
//
// https://stackoverflow.com/questions/461449/return-statement-vs-exit-in-main