// Unix-crypt()
// TEST ParrotOS

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char password[] = "passwd";
    printf("%s\n", password);
    char *passwordcipher = crypt(password, "11");
    printf("%s\n", passwordcipher);
    return 0;
}