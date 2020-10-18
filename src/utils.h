#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#define ENCODE_SIZE 3 // o un multiplo de 3
#define DECODE_SIZE 4 // o un multiplo de 4
#define EXIT_FAILURE 1
#define SUCCESS 0

int encodeFileToBase64(FILE* fdin,FILE* fdout);
int decodeFileFromBase64(FILE* fdin,FILE* fdout);
char* encodeBase64(const char *data,size_t lenInput,size_t* lenOutput);
char* decodeBase64(const char *data,size_t lenInput,size_t* lenOutput);
#endif
