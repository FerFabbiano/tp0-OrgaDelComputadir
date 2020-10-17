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

static size_t __len_base64_decode_output(const char *input,size_t lenInput) {
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

static size_t __len_base64_encode_output(size_t inputLen) {
  size_t ouputLen;
	ouputLen =  inputLen;
	if (inputLen % 3 != 0)
		ouputLen += 3 - (inputLen % 3);
	ouputLen /= 3;
	ouputLen *= 4;

	return ouputLen;
}

static int __write(FILE* file, char* data, size_t lenData) {
  if(!file || !data) return EXIT_FAILURE;
  fwrite(data,sizeof(char),lenData,file);
  return SUCCESS;
}

static int __processFile(FILE* fdin,FILE* fdout,char* buffer,size_t lenBuffer,bool encode) {
  char* output = NULL;
  size_t len = 0;
  size_t nread = 0;
  while ((nread = fread(buffer,sizeof(char),lenBuffer,fdin)) > 0) {
    if(encode) {
      output = encodeBase64(buffer, nread,&len);
    } else {
      output = decodeBase64(buffer, nread,&len);
    }
    if(output){
      __write(fdout,output,len);
      free(output);
    }
    memset(buffer,0,lenBuffer);
  }

  if(nread == -1) return EXIT_FAILURE;
  
  return SUCCESS;
}

//FIN FUNCIONES PRIVADAS

//INICIO FUNCIONES PUBLICAS
char* encodeBase64(const char *data,
	                size_t lenInput,
		              size_t *lenOutput) {
  if(data == NULL || lenInput <= 0) return NULL;  
  
  size_t maxlenOutput = __len_base64_encode_output(lenInput);
  char* output = (char*)calloc(sizeof(char), maxlenOutput + 1);
  if(!output) return NULL;

  size_t i,j;

  for (i = 0,j=0; i < lenInput; j+=4) {
    uint32_t octet0 = (unsigned char) data[i++];
    uint32_t octet1 = i < lenInput ?  data[i++] : BYTE_NULO;
    uint32_t octet2 = i < lenInput ?  data[i++] : BYTE_NULO;
  
    uint32_t bits = (octet0 << 16) + (octet1 << 8) + octet2;
  
    uint32_t sextetA = (bits >> 18) & MASK_SEXTET;
    uint32_t sextetB = (bits >> 12) & MASK_SEXTET;
    uint32_t sextetC = (bits >> 6) & MASK_SEXTET;
    uint32_t sextetD = (bits) & MASK_SEXTET;
    
    output[j]   = base64_table[sextetA];
		output[j+1] = base64_table[sextetB];
    output[j+2] = base64_table[sextetC];
    output[j+3] = base64_table[sextetD];

  }

  for(int i=0; i < modTable[lenInput%3]; i++)
    output[maxlenOutput - 1 -i] = CARACTER_IGUAL;
  
  *lenOutput = strlen(output);
  return output;
}

char* decodeBase64(const char *data,
                             size_t lenInput,
                             size_t *lenOutput) {
	if (!data) return NULL;
  unsigned char* dataPtr = (unsigned char*)data;

  unsigned char dTable[256];
  memset(dTable, -1, 256);
	for (size_t i = 0; i < sizeof(base64_table) - 1; i++)
		dTable[base64_table[i]] = (unsigned char) i;  
  
  size_t lenOutputAux = __len_base64_decode_output(data,lenInput);

  char *output = (char*)calloc(sizeof(char), lenOutputAux + 1);
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

		output[j] = (decode >> 16) & MASK_OCTET;
    if (data[i+2] != '=')
			output[j+1] = (decode >> 8) & MASK_OCTET;
		if (data[i+3] != '=')
			output[j+2] = decode & MASK_OCTET;
	}
  *lenOutput = strlen(output);

	return output;
}

int encodeFileToBase64(FILE* fdin,FILE* fdout) {
  char buffer[ENCODE_SIZE];
  memset(buffer,0,ENCODE_SIZE);
  return __processFile(fdin,fdout,buffer,ENCODE_SIZE,true);
}

int decodeFileFromBase64(FILE* fdin,FILE* fdout) {
  char buffer[DECODE_SIZE];
  memset(buffer,0,DECODE_SIZE);
  return __processFile(fdin,fdout,buffer,DECODE_SIZE,false);
}

//FIN FUNCIONES PUBLICAS
