//
// Created by hhp on 9.03.2017.
//
#include <libxml/tree.h>
#include <string.h>
#include <json-c/json.h>
#include "fromxml.h"
#include "message.h"

#define FIELDSIZE 20
#define BUFFSIZE 200
static xmlNode *root_element = NULL;

char *field[FIELDSIZE];    /* fields */

void xml_csv_pattern_controller(xmlNode *a_node)
{
    xmlNode *cur_node = NULL;
    int flag = 1;
    int pcount = 1;
    int fcount = 0; /*field counter*/
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {

            if (cur_node->parent != root_element || cur_node->properties) {
                errMsg(XMLSTRUCTURE)
            }
            //printf("*cont: %s: %s \n", cur_node->name, cur_node->children->content);

            if (flag) {
                for (int i = 0; i < FIELDSIZE; i++) {
                    if (field[i] == NULL) {
                        field[i] = (char *) malloc(strlen((char *) cur_node->name) * sizeof(char));
                        strcpy(field[i], (char *) cur_node->name);
                        fcount++;
                        //printf("field: %s\n", field[i]);
                        break;
                    } else if (strcmp(field[i], (char *) cur_node->name) == 0) {
                        if (i == 0) {
                            flag = 0;
                            break;
                        } else {errMsg(XMLSTRUCTURE)}
                    }
                }
            } else {
                //printf("%s\n\n\n%s*\n",cur_node->name,field[pcount]);
                if (field[pcount] == NULL) { pcount = 0; }
                if (strcmp((char *) cur_node->name, field[pcount])) {
                    printf("%s : %s\n", field[pcount], cur_node->name);
                    errMsg(XMLSTRUCTURE)
                }
                pcount++;
            }
            if (pcount > FIELDSIZE) {errMsg(XMLSTRUCTURE)}
        }
        xml_csv_pattern_controller(cur_node->children);
    }
}

void xml_csv_writer(xmlNode *a_node, const char *out_name)
{
    FILE *fp;
    fp = fopen(out_name, "w+");
    xmlNode *cur_node = NULL;

    int fieldsize;
    for (fieldsize = 0; field[fieldsize] != NULL; fieldsize++) {
        fprintf(fp, "%s,", field[fieldsize]);
    }
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);

    int count = 0;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            //printf("%s,", cur_node->children->content);
            fprintf(fp, "%s,", cur_node->children->content);
            count++;
            if (count == fieldsize) {
                count = 0;
                fseek(fp, -1, SEEK_END);
                fputc('\n', fp);
            }
        }
        xml_csv_pattern_controller(cur_node->children);
    }
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);
}

void xml_to_csv(const char *filename, const char *out_name)
{
    //log_info("xml_to_csv");

    xmlDoc *doc = NULL;
    const char *Filename = filename;
    doc = xmlReadFile(Filename, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", Filename);
        exit(EXIT_FAILURE);
    } else {
        /* Get the root element node*/
        root_element = xmlDocGetRootElement(doc);

        xml_csv_pattern_controller(root_element->children);
        xml_csv_writer(root_element->children, out_name);

        /*free the document*/
        xmlFreeDoc(doc);
    }
    /*Free the global variables that may have been allocated by the parser.*/
    xmlCleanupParser();

}

void xml_json_parser(xmlNode *a_node, const char *out_name)
{
    xmlNode *temp = NULL;
    xmlNode *cur_node = NULL;
    json_object *root = json_object_new_object();
    json_object *jarray = json_object_new_array();

    for (cur_node = a_node->children; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            json_object *jobje = json_object_new_object();
            temp = cur_node->children;
            while (temp != NULL) {
                if (temp->children != NULL) {
                    json_object *jstring1 = json_object_new_string((const char *) temp->children->content);
                    json_object_object_add(jobje, (const char *) temp->name, jstring1);
                }
                temp = temp->next;
            }
            json_object_array_add(jarray, jobje);
        }
    }
    json_object_object_add(root, (const char *) a_node->children->next->name, jarray);
    //printf("%s\n",a_node->children->next->name);
    FILE *fp = fopen(out_name, "w+");
    //fputs(json_object_to_json_string(root), fp);
    json_object_to_file_ext(out_name, root, JSON_C_TO_STRING_PRETTY);

    fclose(fp);
}

void xml_to_json(const char *filename, const char *out_name)
{
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    doc = xmlReadFile(filename, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", filename);
    } else {
        /*Get the root element node*/
        root_element = xmlDocGetRootElement(doc);

        xml_json_parser(root_element, out_name);
        /* free the document*/
        xmlFreeDoc(doc);
    }
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}