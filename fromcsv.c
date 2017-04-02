//
// Created by hhp on 17.03.2017.
//

#include <json-c/json.h>
#include <libxml/tree.h>
#include <string.h>
#include "message.h"

#define FIELDSIZE 20
#define BUFFSIZE 200

/* csvgetline: read and parse line, return field count */
/* sample input: "LU",86.25,"11/4/1998","2:19PM",+4.0625 */
char buf[BUFFSIZE];        /* input line buffer */
char *field[FIELDSIZE];    /* fields */

int csvgetline(FILE *fin)
{
    int nfield;
    char *p, *q;
    /* spacer */
    if (fgets(buf, sizeof(buf), fin) == NULL)
        return -1;
    nfield = 0;
    for (q = buf; (p = strtok(q, ",\n\r")) != NULL; q = NULL)
        field[nfield++] = p;
    return nfield;
}

void csv_to_xml(const char *filename, const char *out_name, int true)
{
    FILE *fp;
    fp = fopen(filename, "r");
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");      /* document pointer */
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "root"); /* node pointers */

    xmlDocSetRootElement(doc, root_node);


    int nf, prevnf = 0;
    /* spacer */
    prevnf = csvgetline(fp);
    if (prevnf == 0) errMsg("csv format error")
    char *tag[prevnf];

    for (int k = 0; k < prevnf; ++k) {
        tag[k] = (char *) malloc(strlen(field[k]) * sizeof(char));
        strcpy(tag[k], field[k]);
    }


    if (true) {
        while ((nf = csvgetline(fp)) != -1) {
            if (prevnf != nf) {
                errMsg("csv format error")
            }

            xmlNodePtr node = xmlNewChild(root_node, NULL, BAD_CAST "element", NULL);
            for (int i = 0; i < nf; i++) {
                //printf("field[%d] = `%s'\n", i, field[i]);
                xmlNewProp(node, BAD_CAST tag[i], BAD_CAST field[i]);
            }
        }
    } else {
        while ((nf = csvgetline(fp)) != -1) {
            if (prevnf != nf) {
                errMsg("csv format error")
            }
            for (int i = 0; i < nf; i++) {
                //printf("field[%d] = `%s'\n", i, field[i]);
                xmlNewChild(root_node, NULL, BAD_CAST tag[i], BAD_CAST field[i]);
            }
        }
    }
    fclose(fp);
    xmlSaveFormatFileEnc(out_name, doc, "UTF-8", 1);
    xmlFreeDoc(doc);
    xmlCleanupParser();

}

void csv_to_json(const char *filename, const char *out_name)
{
    FILE *fp;
    fp = fopen(filename, "r");


    int nf, prevnf = 0;
    /* spacer */
    prevnf = csvgetline(fp);
    if (prevnf == 0) errMsg("csv format error")
    char *tag[prevnf];

    for (int k = 0; k < prevnf; ++k) {
        tag[k] = (char *) malloc(strlen(field[k]) * sizeof(char));
        strcpy(tag[k], field[k]);
    }

    json_object *root = json_object_new_object();
    json_object *jobje = json_object_new_object();
    json_object *jarray = json_object_new_array();

    while ((nf = csvgetline(fp)) != -1) {
        if (prevnf != nf) {
            errMsg("csv format error")
        }
        for (int i = 0; i < nf; i++) {
            //printf("field[%d] = `%s'\n", i, field[i]);
            //xmlNewChild(root_node, NULL, BAD_CAST tag[i], BAD_CAST field[i]);
            json_object *jstring1 = json_object_new_string(field[i]);
            json_object_object_add(jobje, tag[i], jstring1);
            json_object_array_add(jarray, jobje);
        }
    }

    fclose(fp);
    fp = fopen(out_name, "w");

    json_object_object_add(root, (const char *) "root", jarray);
    json_object_to_file_ext(out_name, root, JSON_C_TO_STRING_PRETTY);
    fclose(fp);

}