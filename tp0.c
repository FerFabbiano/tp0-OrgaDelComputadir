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

#define HELP_MESSAGE "help\n"
#define INVALID_MESSAGE "Opción inválida\n"

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
    //if (!fd) return EXIT_FAILURE;

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
  char inputFileName[256];
  char outputFileName[256];

  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"version", no_argument,0, 'V'},
      {"help", no_argument, 0, 0},
      {"input", required_argument, 0, 0},
      {"output", required_argument, 0, 0},
      {"decode", required_argument, 0, 0}
    };

    c = getopt_long(argc, argv, "Vhi:o:d:", long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
      case V_OPTION:
        printf("version\n");
        break;

      case H_OPTION:
        printf(HELP_MESSAGE);
        break;

      case I_OPTION:
        memcpy(inputFileName,optarg,strlen(optarg));
        //printf("option i with value '%s'\n", optarg);
        break;

      case O_OPTION:
        memcpy(outputFileName,optarg,strlen(optarg));
        //printf("option o with value '%s'\n", optarg);
        break;

      case D_OPTION:
        func = decodeBase64;
        //modifyFileBase(optarg, decodeBase64);
        printf("option i with value '%s'\n", optarg);
        break;

      default:
        printf(INVALID_MESSAGE);
      }
  }

  modifyFileBase(inputFileName,outputFileName,func);

  exit(EXIT_SUCCESS);
}
