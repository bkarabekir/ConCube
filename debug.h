//
// Created by hhp on 9.03.2017.
//

#ifndef CONCUBE_DEBUG_H
#define CONCUBE_DEBUG_H

#endif //CONCUBE_DEBUG_H

#define USAGE "Usage: concube [-i <input filename>] [-o <output filename>] [-true] [-t <output format>]\n"
#define XMLSTRUCTURE "Invalid xml file. Structure have to be:\n<root>\n\t<tag1/>\n\t<tag2/>\n\t...\n\t...\n\t<tag1/>\n\t<tag2/>\n\t...\n\t...\n</root>"
#define errMsg(msg) {fprintf(stderr, "%s\t(%s: %d)\n",msg,__FILE__,__LINE__); exit(EXIT_FAILURE);}

#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
