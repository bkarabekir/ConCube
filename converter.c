//
// Created by hhp on 9.03.2017.
//
#include <libxml/tree.h>

static void print_element_names(xmlNode *a_node);


void xmlToCsv(const char* fileName, const char* outName){
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;
    const char *Filename = "note.xml";
    doc = xmlReadFile(Filename, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", Filename);
    } else {
        /* Get the root element node*/
        root_element = xmlDocGetRootElement(doc);

        print_element_names(root_element);

        /*free the document*/
        xmlFreeDoc(doc);
    }
    /*Free the global variables that may have been allocated by the parser.*/
    xmlCleanupParser();

}

static void print_element_names(xmlNode *a_node) {
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("%s: %s \n", cur_node->name, cur_node->children->content);
            printf("cur_node: %p \ncur_node->children: %p \ncur_node->children->content %p \n\n\n-*-*-*-*-*-*-*-*-*-*-*-*-*\n",
                   cur_node, cur_node->children, cur_node->children->content);
            if (cur_node->children->content == NULL) {
                printf("asdf");
            }
        }
        print_element_names(cur_node->children);
    }
}