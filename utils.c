#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "utils.h"
#include <string.h>

#define EXIT_FAILURE 1
#define SUCCESS 0
#define BUFFER_SIZE 3

int leerArchivo(char *fileName){
  char line[BUFFER_SIZE];

  FILE *fd = fopen(fileName, "rw");

  if (!fd) return EXIT_FAILURE;

  while (!feof(fd)){
    fread(line, 1, BUFFER_SIZE, fd);
		encodeBase64(line);
		memset(line, 0, strlen(line));
  }

  fclose(fd);

  return SUCCESS;
}

int encodeBase64 (char *string) {
	const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	int resto = strlen(string) % 3;

	if (resto != 0){
		for (int i = 0; i < resto; i++){
			string[BUFFER_SIZE - 1 - i] = 0;
		}
	}

	printf("%s\n", string);

	uint32_t car0 = string[0];
	uint32_t car1 = string[1];
	uint32_t car2 = string[2];
	uint32_t bits = (car0 << 0x10) + (car1 << 0x08) + car2;
	uint32_t result = (bits >> 18) & 63;
	uint32_t result2 = (bits >> 12) & 63;
	uint32_t result3 = (bits >> 6) & 63;
	uint32_t result4 = (bits) & 63;

	char base64[5];
	base64[0] = base64chars[result];
	base64[1] = base64chars[result2];
	base64[2] = base64chars[result3];
	base64[3] = base64chars[result4];
	
	if (resto != 0){
		for (int i = 0; i < resto; i++){
			base64[3 - i] = '=';
		}
	}
	
	printf("%s", base64);
	
	return SUCCESS;
}
