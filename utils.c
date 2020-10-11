#include "utils.h"

#define EXIT_FAILURE 1
#define SUCCESS 0

static int modTable[] = {0,2,1}; // cant de veces que tiene que iterar
static const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *decodingTable = NULL;

int modifyFileBase(char *fileName, int opt){
    char *line, *output = NULL;
    FILE *fd = fopen(fileName, "rw");

    if (!fd) return EXIT_FAILURE;
    ssize_t nread = 0;
    size_t len = 0;
    
    while ((nread = getline(&line, &len, fd)) != -1){
        output = opt == OPT_ENCODE ? encodeBase64(line, nread) : decodeBase64(line, nread, &nread);
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

char* encodeBase64(char *data, size_t len_input) {
    size_t len_output = __len_base64_output(len_input);
    
    char* output = malloc(sizeof(char) * len_output + 1);
    memset(output,0,len_output +1);
    
    size_t i,j;

    for (i = 0,j=0; i < len_input; j+=4) {
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

    for(int i=0; i < modTable[len_input%3]; i++) 
        output[len_output - 1 -i] = '=';
    return output;
}

void buildDecodingTable() {
    decodingTable = malloc(256);
 
    for (int i = 0; i < 64; i++)
        decodingTable[(unsigned char) base64chars[i]] = i;
}

char *decodeBase64(const char *data,
                             size_t lenInput,
                             ssize_t *lenOutput) {
 
    if (decodingTable == NULL) buildDecodingTable();
  
    *lenOutput = lenInput / 4 * 3;
    if (data[lenInput - 1] == '=') (*lenOutput)--;
    if (data[lenInput - 2] == '=') (*lenOutput)--;
 
    char *output = malloc(*lenOutput);
 
    for (int i = 0, j = 0; i < lenInput;) {
 
        uint32_t sextet_a = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];
        uint32_t sextet_b = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];
        uint32_t sextet_c = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];
        uint32_t sextet_d = data[i] == '=' ? 0 & i++ : decodingTable[data[i++]];
 
        uint32_t triple = (sextet_a << 3 * 6)
        + (sextet_b << 2 * 6)
        + (sextet_c << 1 * 6)
        + (sextet_d << 0 * 6);
 
        if (j < *lenOutput) output[j++] = (triple >> 2 * 8) & 0xFF;
        if (j < *lenOutput) output[j++] = (triple >> 1 * 8) & 0xFF;
        if (j < *lenOutput) output[j++] = (triple >> 0 * 8) & 0xFF;
    }

    free(decodingTable);
 
    return output;
}

