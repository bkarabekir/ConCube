#include <stdio.h>
#include <string.h>

#define error {printf("Usage: concube [-i <input filename>]\
 [-o <output filename>] [-true] [-t <output format>]\n"); return 1;}

int main(int argc, char* argv[]) {
    printf("%d\n", argc);
    if(argc < 5 || argc > 6)
        error

    char* inputFile = NULL;
    char* outputFile = NULL;
    char* type;
    int true = 0;

    for(int i=1; i < argc; i++ ) {
        if(!strcmp(argv[i], "-i"))
            inputFile = argv[i+1];

        else if(!strcmp(argv[i], "-o"))
            outputFile = argv[i+1];

        else if(!strcmp(argv[i], "-t"))
            type = argv[i+1];

        else if(!strcmp(argv[i], "-true"))
            true = 1;
    }

    if(((!inputFile && !(outputFile || type)) || (argc == 6 && true != 1)))
        error
    printf("susscess");
    return 0;
}
