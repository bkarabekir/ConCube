//
// Created by hhp on 17.03.2017.
//

#ifndef CONCUBE_MESSAGE_H
#define CONCUBE_MESSAGE_H

#endif //CONCUBE_MESSAGE_H


#define USAGE "Usage: concube [-i <input filename>] [-o <output filename>] [-true] [-t <output format>]\n"
#define XMLSTRUCTURE "Invalid xml file. Structure have to be:\n<root>\n\t<tag1/>\n\t<tag2/>\n\t...\n\t...\n\t<tag1/>\n\t<tag2/>\n\t...\n\t...\n</root>"
#define errMsg(msg) {fprintf(stderr, "%s\t(%s: %d)\n",msg,__FILE__,__LINE__); exit(EXIT_FAILURE);}