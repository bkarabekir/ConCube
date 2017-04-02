//
// Created by hhp on 16.03.2017.
//

#include <stdio.h>
#include <libxml/tree.h>
#include <json-c/json.h>
#include "debug.h"

void j_xml_writer(json_object *jobj, xmlNodePtr parent, int true);

void json_parse(json_object *jobj, xmlNodePtr root_node, int true)
{
    enum json_type type;
    int arraylen;
    xmlNodePtr parent;
    json_object *tmp;
    json_object *jvalue;

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        json_object *arrObj;

        switch (type) {
            case json_type_array:

                arrObj = json_object_object_get(jobj, key);
                arraylen = json_object_array_length(arrObj);

                for (int i = 0; i < arraylen; i++) {
                    parent = xmlNewChild(root_node, NULL, BAD_CAST key, NULL);
                    jvalue = json_object_array_get_idx(arrObj, i);
                    tmp = json_tokener_parse(json_object_get_string(jvalue));
                    j_xml_writer(tmp, parent, true);
                }
                break;
        }
    }
}

void j_xml_writer(json_object *jobj, xmlNodePtr parent, int true)
{
    enum json_type type;
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_string:
                if (true) {
                    xmlNewProp(parent, BAD_CAST key, BAD_CAST json_object_get_string(val));
                    //printf("%p \n",xmlNewProp(parent, BAD_CAST key, BAD_CAST json_object_get_string(val)));
                } else {
                    xmlNewChild(parent, NULL, BAD_CAST key, BAD_CAST json_object_get_string(val));
                }
                break;
        }
    }
}

void json_to_xml(char *filename, char const *out_name, int true)
{
    json_object *read_obj = json_object_from_file(filename);

    xmlDocPtr doc = NULL;
    doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root_node = xmlNewNode(NULL, BAD_CAST "root");
    xmlDocSetRootElement(doc, root_node);

    json_object *jobj = json_tokener_parse(json_object_get_string(read_obj));

    json_parse(jobj, root_node, true);

    xmlSaveFormatFileEnc(out_name, doc, "UTF-8", 1);

    log_info("%s has been created.", out_name);
}

void j_csv_tagwriter(json_object *jobj, FILE *fp)
{
    enum json_type type;

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_string:
                fprintf(fp, "%s,", key);
                break;
        }
    }
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);
}

void j_csv_writer(json_object *jobj, FILE *fp)
{
    enum json_type type;

    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        switch (type) {
            case json_type_string:
                fprintf(fp, "%s,", json_object_get_string(val));
                break;
        }
    }
    fseek(fp, -1, SEEK_END);
    fputc('\n', fp);
}

void j_parse_csv(json_object *jobj, FILE *fp)
{
    enum json_type type;
    int arraylen;
    json_object *tmp;
    json_object *jvalue;
    int flag = 1;
    json_object_object_foreach(jobj, key, val) {
        type = json_object_get_type(val);
        json_object *arrObj;

        switch (type) {
            case json_type_array:

                arrObj = json_object_object_get(jobj, key);
                arraylen = json_object_array_length(arrObj);
                if (flag) {
                    flag = 0;
                    jvalue = json_object_array_get_idx(arrObj, 0);
                    tmp = json_tokener_parse(json_object_get_string(jvalue));
                    j_csv_tagwriter(tmp, fp);
                }
                for (int i = 0; i < arraylen; i++) {

                    jvalue = json_object_array_get_idx(arrObj, i);
                    tmp = json_tokener_parse(json_object_get_string(jvalue));
                    j_csv_writer(tmp, fp);
                }
                break;
        }
    }
}

void json_to_csv(char const *input_name, char const *out_name)
{
    FILE *fp;
    fp = fopen(out_name, "w");

    json_object *read_obj = json_object_from_file(input_name);
    json_object *jobj = json_tokener_parse(json_object_get_string(read_obj));

    j_parse_csv(jobj, fp);
}
