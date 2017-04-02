#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "fromxml.h"
#include "fromjson.h"
#include "fromcsv.h"
#include "message.h"

int main(int argc, char *argv[])
{
    if (argc < 5 || argc > 6) errMsg(USAGE);

    char *filename = NULL;
    char *out_name = NULL;
    char tmp = '\0';
    char *type = &tmp;
    int true = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i"))
            filename = argv[i + 1];

        else if (!strcmp(argv[i], "-o"))
            out_name = argv[i + 1];

        else if (!strcmp(argv[i], "-t"))
            type = argv[i + 1];

        else if (!strcmp(argv[i], "-true"))
            true = 1;
    }

    /* check */
    if (argc == 6 && true != 1) errMsg(USAGE)

    char *inExt = &tmp, *outExt = &tmp;

    if (filename) {
        if (access(filename, F_OK) == -1) {
            errMsg("Input file does not exist")
        }

        for (int i = 0; i < strlen(filename); i++) {
            if (filename[i] == '.') {
                inExt = filename + (i + 1);
                break;
            }
        }

        if (out_name) {
            for (int i = 0; i < strlen(out_name); i++) {
                if (out_name[i] == '.') {
                    outExt = out_name + (i + 1);
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

            xml_to_csv(filename, (out_name ?: "out.csv"));

        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {

            xml_to_json(filename, (out_name ?: "out.json"));

        }
    } else if (!strcmp(inExt, "csv")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {

            csv_to_xml(filename, (out_name ?: "out.xml"), true);

        } else if (!strcmp(outExt, "json") || !strcmp(type, "json")) {

            csv_to_json(filename, (out_name ?: "out.json"));

        }
    } else if (!strcmp(inExt, "json")) {
        if (!strcmp(outExt, "xml") || !strcmp(type, "xml")) {

            json_to_xml(filename, (out_name ?: "out.xml"), true);

        } else if (!strcmp(outExt, "csv") || !strcmp(type, "csv")) {

            json_to_csv(filename, (out_name ?: "out.csv"));

        }
    } else errMsg("Extension is invalid")


    printf("\nsusscess\n");
    return 0;

}
