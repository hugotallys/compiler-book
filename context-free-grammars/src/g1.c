#include <stdio.h>
#include <string.h>

#define MAXSIZE 100

typedef long unsigned int luint;

int main(int argc, char const *argv[]) {
    char input[MAXSIZE];

    printf("Grammar G1 recognizer. Type a word.\n");
    scanf("%s", input);

    int accept = 1;
    luint p = 0;
    luint currentState = 0;

    while (p < strlen(input) && accept) {
        switch (currentState) {
            case 0:
                if (input[p] == 'b')
                    currentState = 1;
                else
                    accept = 0;
                break;
            case 1:
                if (input[p] == 'a')
                    currentState = 2;
                else
                    accept = 0;
                break;
            case 2:
                if (input[p] == 'a')
                    currentState = 3;
                else
                    accept = 0;
                break;
            case 3:
                if (input[p] == 'a')
                    currentState = 2;
                else
                    accept = 0;
                break;
            default:
                break;
        }
        p++;
    }

    if (currentState == 2 && accept) {
        printf("Accepted!\n");
    } else {
        printf("Not accepted!\n");
    }
    
    return 0;
}