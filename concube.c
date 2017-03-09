#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include "converter.h"

#define USAGE "Usage: concube [-i <input filename>] [-o <output filename>] [-true] [-t <output format>]\n"
#define errMsg(msg) {fprintf(stderr, "%s",msg); exit(EXIT_FAILURE);}

int main(int argc, char *argv[]) {

    if (argc < 5 || argc > 6) errMsg(USAGE)

    char *inputFile = NULL;
    char *outputFile = NULL;
    char *type;
    int true = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i"))
            inputFile = argv[i + 1];

        else if (!strcmp(argv[i], "-o"))
            outputFile = argv[i + 1];

        else if (!strcmp(argv[i], "-t"))
            type = argv[i + 1];

        else if (!strcmp(argv[i], "-true"))
            true = 1;
    }

    /* check */
    if (argc == 6 && true != 1) errMsg(USAGE)

    char *inExt, *outExt, *outType, *fileName;

    if (inputFile) {
        if (access(inputFile, F_OK) == -1) {
            errMsg("Input file does not exist")
        }

        fileName = strtok(inputFile, ".");
        inExt = strtok(NULL, "\0");

        if (outputFile) {
            strtok(outputFile, ".");
            outExt = strtok(NULL, "\0");

        } else if (!type) {
            errMsg(USAGE)
        }

    } else {errMsg(USAGE)}

    if (!strcmp(inExt, "xml")) {
        if (!strcmp(outExt, "csv") || !strcmp(type, "csv")) {

            xmlToCsv(fileName);

        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {
            printf("json has been not implemented yet");
        }


    } else if(!strcmp(inExt, "csv")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {
            printf("outExt tpye xml");
        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {
            printf("json has been not implemented yet");
        }
    } else if(!strcmp(inExt, "json")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {
            printf("json has been not implemented yet");
        } else if (!strcmp(outExt, "csv") || !strcmp(type, "csv")) {
            printf("json has been not implemented yet");
        }
    } else errMsg("Extension is invalid")



    printf("\nsusscess\n");
    return 0;
}
