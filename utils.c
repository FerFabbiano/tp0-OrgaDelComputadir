#include <stdint.h>
#include <string.h>
#include "utils.h"

#define MASK_SEXTET 0x3F
#define MASK_OCTET 0xFF
#define SHIFT_SEXTET 6
#define BYTE_NULO 0
#define CARACTER_IGUAL '='

static int modTable[] = {0,2,1}; // cant de veces que tiene que iterar
static const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *decodingTable = NULL;

static void __buildDecodingTable() {
    decodingTable = malloc(sizeof(char) * 256);
	if (!decodingTable)	return;
	
    for (int i = 0; i < 64; i++)
        decodingTable[(unsigned char) base64chars[i]] = i;
}

static size_t __len_base64_encode_output(size_t input_len) {
    size_t ouput_len = input_len;
    ouput_len += 3 - (input_len % 3);
    ouput_len /=3;
    ouput_len *= 4;
    return ouput_len;
}

static size_t __len_base64_decode_output(size_t lenInput) {
    return lenInput / 4 * 3;
}


char* encodeBase64(const char *data, 
					size_t lenInput/*,
					ssize_t *lenOutput*/) {
    ssize_t lenOutput = __len_base64_encode_output(lenInput);

	if(data == NULL || lenInput <= 0) return NULL;
    
    char* output = malloc(sizeof(char) * lenOutput);
	if(!output) return NULL;

    memset(output,0,(lenOutput));
    
    size_t i,j;

    for (i = 0,j=0; i < lenInput; j+=4) {
        uint32_t octet0 = (unsigned char) data[i++];
        uint32_t octet1 = i < lenInput ? (unsigned char) data[i++] : BYTE_NULO;
        uint32_t octet2 = i < lenInput ? (unsigned char) data[i++] : BYTE_NULO;

        uint32_t bits = (octet0 << 0x10) + (octet1 << 0x08) + octet2;

        uint32_t sextetA = (bits >> SHIFT_SEXTET * 3) & MASK_SEXTET;
        uint32_t sextetB = (bits >> SHIFT_SEXTET * 2) & MASK_SEXTET;
        uint32_t sextetC = (bits >> SHIFT_SEXTET) & MASK_SEXTET;
        uint32_t sextetD = (bits) & MASK_SEXTET;

        output[j] = base64chars[sextetA];
        output[j+1] = base64chars[sextetB];
        output[j+2] = base64chars[sextetC];
        output[j+3] = base64chars[sextetD];
    }

    for(int i=0; i < modTable[lenInput%3]; i++) 
        output[lenOutput - 1 -i] = CARACTER_IGUAL;

    return output;
}


char* decodeBase64(const char *data,
                             size_t lenInput/*,
                             ssize_t *lenOutput*/) {
 
    if (decodingTable == NULL) __buildDecodingTable();
  
    ssize_t lenOutput = __len_base64_decode_output(lenInput);
    if (data[lenInput - 1] == CARACTER_IGUAL) (lenOutput)--;
    if (data[lenInput - 2] == CARACTER_IGUAL) (lenOutput)--;
 
    char *output = malloc(sizeof(char)* (lenOutput));
	if(!output) return NULL;

	memset(output,0,lenOutput);
 
    for (int i = 0, j = 0; i < lenInput;) {
        uint32_t sextet_a = data[i] == CARACTER_IGUAL ? BYTE_NULO & i++ : decodingTable[(int) data[i++]];
        uint32_t sextet_b = data[i] == CARACTER_IGUAL ? BYTE_NULO & i++ : decodingTable[(int) data[i++]];
        uint32_t sextet_c = data[i] == CARACTER_IGUAL ? BYTE_NULO & i++ : decodingTable[(int) data[i++]];
        uint32_t sextet_d = data[i] == CARACTER_IGUAL ? BYTE_NULO & i++ : decodingTable[(int) data[i++]];
 
        uint32_t triple = (sextet_a << 3 * SHIFT_SEXTET)
        + (sextet_b << 2 * SHIFT_SEXTET)
        + (sextet_c << SHIFT_SEXTET)
        + sextet_d;
 
        if (j < lenOutput) output[j++] = (triple >> 2 * 8) & MASK_OCTET;
        if (j < lenOutput) output[j++] = (triple >> 1 * 8) & MASK_OCTET;
        if (j < lenOutput) output[j++] = (triple >> 0 * 8) & MASK_OCTET;
    }

	free(decodingTable);
 
    return output;
}

