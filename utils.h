#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char* encodeBase64(char *data,size_t len_input);
int leerArchivo(char *fileName);

#endif