#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#define MASK_SEXTET 0x3F
#define MASK_OCTET 0xFF
#define SHIFT_SEXTET 6
#define BYTE_NULO 0
#define CARACTER_IGUAL '='

static int modTable[] = {0,2,1}; // cant de veces que tiene que iterar
static const unsigned char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//INICIO FUNCIONES PRIVADAS
static bool __b64_isvalidchar(char c) {
  bool valid = false;
	if (c >= '0' && c <= '9')
		valid = true;
	if (c >= 'A' && c <= 'Z')
		valid = true;
	if (c >= 'a' && c <= 'z')
		valid = true;
	if (c == '+' || c == '/' || c == '=')
	  valid = true;
	return valid;
}


size_t __len_base64_decode_output(const char *input,size_t lenInput) {
	if (!input) return 0;
	
  size_t len = 0;
	len = lenInput / 4 * 3;
	
	for (size_t i = 0; i < lenInput; i++) {
    if (input[i] == CARACTER_IGUAL) {
			len--;
		}
  }

	return len;
}

static size_t __len_base64_encode_output(size_t input_len) {
  size_t ouput_len = input_len;
  ouput_len += 3 - (input_len % 3);
  ouput_len /=3;
  ouput_len *= 4;
  return ouput_len;
}
//FIN FUNCIONES PRIVADAS

//INICIO FUNCIONES PUBLICAS
char* encodeBase64(const char *data,
	                size_t lenInput,
		              size_t *lenOutput) {
  if(data == NULL || lenInput <= 0) return NULL;  
  
  size_t maxlenOutput = __len_base64_encode_output(lenInput);
  char* output = (char*)calloc(sizeof(char), maxlenOutput);
  if(!output) return NULL;

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
  
    output[j] = base64_table[sextetA];
    output[j+1] = base64_table[sextetB];
    output[j+2] = base64_table[sextetC];
    output[j+3] = base64_table[sextetD];
  }

  for (int i=0; i < modTable[lenInput%3]; i++)
    output[maxlenOutput - 1 -i] = CARACTER_IGUAL;
  
  *lenOutput = strlen(output);
  return output;
}

char* decodeBase64(const char *data,
                             size_t lenInput,
                             size_t *lenOutput) {
  unsigned char* dataPtr = (unsigned char*)data;

  unsigned char dTable[256];
  memset(dTable, -1, 256);
	for (size_t i = 0; i < sizeof(base64_table) - 1; i++)
		dTable[base64_table[i]] = (unsigned char) i;

	if (!data) return NULL;
  
  size_t lenOutputAux = __len_base64_decode_output(data,lenInput);

  char *output = (char*)calloc(sizeof(char), lenOutputAux);
  if(!output) return NULL;

	uint32_t decode;
  
  size_t i;
	size_t j;
	for (i=0, j=0; i<lenInput; i+=4, j+=3) {
    if (!__b64_isvalidchar(data[i])) continue;
		decode = dTable[dataPtr[i]];
		decode = (decode << 6) | dTable[dataPtr[i+1]];
		decode = data[i+2] == CARACTER_IGUAL ? decode << 6 : (decode << 6) | dTable[dataPtr[i+2]];
		decode = data[i+3] == CARACTER_IGUAL ? decode << 6 : (decode << 6) | dTable[dataPtr[i+3]];

		if (j < lenOutputAux) output[j] = (decode >> 16) & MASK_OCTET;
    if (j < lenOutputAux) output[j+1] = (decode >> 8) & MASK_OCTET;
    if (j < lenOutputAux) output[j+2] = (decode) & MASK_OCTET;
	}
  *lenOutput = lenOutputAux;

	return output;
}

//FIN FUNCIONES PUBLICAS
