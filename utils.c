#include "utils.h"

#define EXIT_FAILURE 1
#define SUCCESS 0
#define BUFFER_SIZE 100

static int mod_table[] = {0,2,1};
static const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int leerArchivo(char *fileName){
	char *line = NULL;
	FILE *fd = fopen(fileName, "rw");

	if (!fd) return EXIT_FAILURE;
	ssize_t nread = 0;
	size_t len = 0;
	
	while ((nread = getline(&line, &len, fd)) != -1){
		char* output = encodeBase64(line,nread);
		printf("output:%s\n",output);
		free(output);
		free(line);
	}
	
	fclose(fd);

	return SUCCESS;
}


static size_t __len_base64_output(size_t input_len) {
	size_t ouput_len = input_len;
	ouput_len += 3 - (input_len % 3);
	ouput_len /=3;
	ouput_len *= 4;
	return ouput_len;
}


char* encodeBase64(char *data,size_t len_input) {
	size_t len_output = __len_base64_output(len_input);
	
	char* output = malloc(sizeof(char) * len_output + 1);
	memset(output,0,len_output +1);
	
	size_t i,j;

	for (i = 0,j=0; i < len_input; i,j+=4) {
		uint32_t car0 = (unsigned char) data[i++];
		uint32_t car1 = i < len_input ? (unsigned char) data[i++] : 0;
		uint32_t car2 = i < len_input ? (unsigned char) data[i++] : 0;

		uint32_t bits = (car0 << 0x10) + (car1 << 0x08) + car2;

		uint32_t result = (bits >> 18) & 63;
		uint32_t result2 = (bits >> 12) & 63;
		uint32_t result3 = (bits >> 6) & 63;
		uint32_t result4 = (bits) & 63;

		output[j] = base64chars[result];
		output[j+1] = base64chars[result2];
		output[j+2] = base64chars[result3];
		output[j+3] = base64chars[result4];
	}

	for(int i=0; i < mod_table[len_input%3]; i++) 
		output[len_output - 1 -i] = '=';
	return output;
}


