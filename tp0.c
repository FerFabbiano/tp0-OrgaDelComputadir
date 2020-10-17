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
//la longitud del buffer debe conincidir para q el 
//encode no agregue = al final
#define LEN_BUFFER 40

#define HELP_MESSAGE "Options:\n-V, --version\tPrint version and quit.\n-h, --help\t\
Print this information.\n-o, --output\tPath to output file.\n-i, \
--input\tPath to input file.\n-d, --decode\tDecode a base64-encoded\
file.\n"

#define INVALID_MESSAGE "Invalid option , use -h or --help to list valid commands\n"

enum operacion {DECODE,ENCODE,HELP,VERSION};

void imprimir_salida(const char* mensaje) {
  fprintf(stdout,"%s\n",mensaje);
}

void imprimir_error(const char* error) {
  fprintf(stderr,"%s\n",error);
}

int main(int argc, char **argv){
  int c;
  int operacion = ENCODE;
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
        operacion = VERSION;
        break;
      case H_OPTION:
        operacion = HELP;
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
        operacion = DECODE;
        break;

      default:
        imprimir_salida(INVALID_MESSAGE);
    }
  }
  
  if(operacion == ENCODE || operacion == DECODE) {
    FILE* outfd = stdout;
    FILE* infd = stdin;
    
    if (inputFileptr) {
      infd = fopen(inputFileName,"r");
      if (!infd) {
        imprimir_error("El archivo de input no existe\n");
        return EXIT_FAILURE;
      }
    }

    if (outputFileptr) {
      outfd = fopen(outputFileName,"w");
    }

    if(operacion) {
      encodeFileToBase64(infd,outfd);
    } else {
      decodeFileFromBase64(infd,outfd);
    }

    fclose(infd);
    fclose(outfd);
  } else if (operacion == HELP) {
    imprimir_salida(HELP_MESSAGE);
  } else if(operacion == VERSION) {
    imprimir_salida("Version: 1.0.0\n");
  } 

  return EXIT_SUCCESS;
}
