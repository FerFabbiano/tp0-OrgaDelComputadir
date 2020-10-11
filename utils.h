#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define OPT_ENCODE 0
#define OPT_DECODE 1

char* encodeBase64(char *data, size_t len_input);
int modifyFileBase(char *fileName, int opt);
char *decodeBase64(const char *data, size_t lenInput, ssize_t *lenOutput);
void buildDecodingTable();

#endif
