#define  _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include "utils.h"

#define V_OPTION 'V'
#define H_OPTION 'h'
#define O_OPTION 'o'
#define I_OPTION 'i'
#define D_OPTION 'd'

#define MAX_LONGITUD 256

#define HELP_MESSAGE "Options:\n-V, --version\tPrint version and quit.\n-h, --help\t\
Print this information.\n-o, --output\tPath to output file.\n-i, \
--input\tPath to input file.\n-d, --decode\tDecode a base64-encoded\
file.\n"

#define INVALID_MESSAGE "Invalid option , use -h or --help to list valid commands\n"

typedef char* (*callback)(const char *,size_t,size_t*);

static int __write(FILE* file, char* data, size_t lenData) {
  if(!file || !data) return EXIT_FAILURE;
  fwrite(data,sizeof(char),lenData,file);
  return SUCCESS;
}

void imprimir_salida(const char* mensaje) {
  fprintf(stdout,"%s\n",mensaje);
}

int modifyFileBase(const char* inputFileName,
                  const char* outputFileName, 
                  callback f) {
  char *line = NULL;
  char *output = NULL;

  FILE* inputFile = stdin;
  if (inputFileName) {
    inputFile = fopen(inputFileName,"r");
  }

  FILE* outputFile = stdout;
  if (outputFileName) {
    outputFile = fopen(outputFileName,"w");
  }
  
  ssize_t nread = 0;
  size_t len = 0;
  size_t lenDataEncode = 0;

  while ((nread = getline(&line, &len, inputFile)) != -1) {
    output = f(line, nread,&lenDataEncode);
    __write(outputFile,output,lenDataEncode);
    if(output) free(output);
  }
  
  free(line);
  if(inputFileName) fclose(inputFile);
  if(outputFileName) fclose(outputFile);
  
  return SUCCESS;
}

int main(int argc, char **argv){
  int c;
  callback func = encodeBase64;
  const char* inputFileptr = NULL;
  const char* outputFileptr = NULL;

  char inputFileName[MAX_LONGITUD];
  char outputFileName[MAX_LONGITUD];
  memset(inputFileName,0,MAX_LONGITUD);
  memset(outputFileName,0,MAX_LONGITUD);

  while (true) {
    int option_index = 0;

    static struct option long_options[] = {
      {"version", no_argument,0, 'V'},
      {"help", no_argument, 0, 'h'},
      {"input", required_argument, 0, 'i'},
      {"output", required_argument, 0, 'o'},
      {"decode", no_argument, 0, 'd'}
    };

    c = getopt_long(argc, argv, "Vhdi:o:", long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
      case V_OPTION:
        imprimir_salida("Version: 1.0.0\n");
        break;
      case H_OPTION:
        imprimir_salida(HELP_MESSAGE);
        break;

      case I_OPTION:
        memcpy(inputFileName,optarg,strlen(optarg));
        inputFileptr = inputFileName;
        break;

      case O_OPTION:
        memcpy(outputFileName,optarg,strlen(optarg));
        outputFileptr = outputFileName;
        break;

      case D_OPTION:
        func = decodeBase64;
        break;

      default:
        imprimir_salida(INVALID_MESSAGE);
    }
  }

  modifyFileBase(inputFileptr,outputFileptr,func);

  exit(EXIT_SUCCESS);
}
