#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1
#define SUCCESS 0

char* encodeBase64(const char *data,size_t lenInput,size_t* lenOutput);
char* decodeBase64(const char *data,size_t lenInput,size_t* lenOutput);
#endif
