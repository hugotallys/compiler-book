#include <stdio.h>

// function to open a txt file
void openFile(char *fileName)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error opening file");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }
    printf("\n");
    fclose(file);
}

int main(int argc, char const *argv[])
{
    char *filePath = "../test/program.txt";
    openFile(filePath);
    return 0;
}
