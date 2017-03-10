#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "xmlcsv.h"
#include "debug.h"

int main(int argc, char *argv[])
{

    if (argc < 5 || argc > 6) errMsg(USAGE)

    char *inputFile = NULL;
    char *outputFile = NULL;
    char *type = NULL;
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

    char *inExt, *outExt;

    if (inputFile) {
        if (access(inputFile, F_OK) == -1) {
            errMsg("Input file does not exist")
        }

        for (int i = 0; i < strlen(inputFile); i++) {
            if (inputFile[i] == '.') {
                inExt = inputFile + (i + 1);
                break;
            }
        }

        if (outputFile) {
            printf("strlen(outputFile): %d\n", strlen(outputFile));
            for (int i = 0; i < strlen(outputFile); i++) {
                if (outputFile[i] == '.') {
                    outExt = outputFile + (i + 1);
                    break;
                }
            }

        } else if (!type) {
            errMsg(USAGE)
        }

    } else {errMsg(USAGE)}

    if (!inExt && !(outExt || type)) {errMsg(USAGE)}

    if (!strcmp(inExt, "xml")) {
        if (!strcmp(outExt, "csv") || !strcmp(type, "csv")) {

            xml_to_csv(inputFile, (outputFile ?: "out.csv"));

        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {
            printf("json has been not implemented yet");
        }


    } else if (!strcmp(inExt, "csv")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {

            csv_to_xml(inputFile, (outputFile ?: "out.xml"), true);


        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {
            printf("json has been not implemented yet");
        }
    } else if (!strcmp(inExt, "json")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {
            printf("json has been not implemented yet");
        } else if (!strcmp(outExt, "csv") || !strcmp(type, "csv")) {
            printf("json has been not implemented yet");
        }
    } else errMsg("Extension is invalid")


    printf("\nsusscess\n");
    return 0;

}
