#define  _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include "utils.h"

#define V_OPTION 'V'
#define H_OPTION 'h'
#define O_OPTION 'o'
#define I_OPTION 'i'
#define D_OPTION 'd'

#define BUFFER_NOMBRE_ARCHIVO 256

#define HELP_MESSAGE "Options:\n-V, --version   Print version and quit.\n-h, --help   \
                      Print this information.\n-o, --output   Path to output file.\n-i, \
                      --input   Path to input file.\n-d, --decode   Decode a base64-encoded \
                      file.\n"
#define INVALID_MESSAGE "Invalid option , use -h or --help to list valid commands\n"

typedef char* (*callback)(const char *, size_t);


static int __write(FILE* file, char* data, ssize_t lenData) {
	if(!file || !data) return EXIT_FAILURE;
	fwrite(data,sizeof(char),lenData,file);
	return SUCCESS;
}

int modifyFileBase(char* inputFileName,char* outputFileName, callback f) {
    char *line, *output = NULL;
    FILE *infd = fopen(inputFileName, "r");
    FILE *outfd = fopen(outputFileName, "w");

    ssize_t nread = 0;
    size_t len = 0;

    while ((nread = getline(&line, &len, infd)) != -1){
        output = f(line, nread);
        __write(outfd,output,strlen(output));
        free(output);
        free(line);
    }

    fclose(infd);
    fclose(outfd);
    return SUCCESS;
}

int main(int argc, char **argv){
  int c;
  callback func = encodeBase64;
  char inputFileName[BUFFER_NOMBRE_ARCHIVO];
  char outputFileName[BUFFER_NOMBRE_ARCHIVO];
  char finalizar = 1;
  while (1) {
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
        printf("Version: 1.0.0\n");
        break;

      case H_OPTION:
        printf(HELP_MESSAGE);
        break;

      case I_OPTION:
        memcpy(inputFileName,optarg,strlen(optarg));
	finalizar = 0;
        break;

      case O_OPTION:
        memcpy(outputFileName,optarg,strlen(optarg));
	finalizar = 0;
        break;

      case D_OPTION:
        func = decodeBase64;
        break;

      default:
        printf(INVALID_MESSAGE);
      }
  }
  if(!finalizar)
  	modifyFileBase(inputFileName,outputFileName,func);

  exit(EXIT_SUCCESS);
}
