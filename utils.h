#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1
#define SUCCESS 0
#define OPT_ENCODE 0
#define OPT_DECODE 1

//int modifyFileBase(char *fileName, int opt);
char* encodeBase64(const char *data, size_t lenInput/*,ssize_t *lenOutput*/);
char* decodeBase64(const char *data, size_t lenInput/*, ssize_t *lenOutput*/);

#endif
