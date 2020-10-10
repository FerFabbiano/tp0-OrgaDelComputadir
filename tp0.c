#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern size_t mystrlen(const char *);

#define EXIT_FAILURE 1
#define SUCCESS 0

/*
int leerArchivo(char *fileIn);

int main(int argc, char * const argv[]){  
  leerArchivo(argv[1]);
  return SUCCESS;
}

int leerArchivo(char *fileName){
  char *line = "NULL";
  size_t line_size = 0;

  FILE *fd = fopen(fileName, "rw");

  if (!fd) return EXIT_FAILURE;

  while (getline(&line, &line_size, fd) != -1){
    write(1, line, strlen(line));
    free(line);
  }

  fclose(fd);

  return SUCCESS;
}
*/

#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

#define V_OPTION 'V'
#define H_OPTION 'h'
#define O_OPTION 'o'
#define I_OPTION 'i'

#define HELP_MESSAGE "help\n"
#define INVALID_MESSAGE "Opción inválida\n"

int main(int argc, char **argv){
  int c;
  int version_flag = 0;
  while (1) {
    int option_index = 0;
    static struct option long_options[] = {
      {"version", no_argument,0, 'V'},
      {"help", no_argument, 0, 0},
      {"input", required_argument, 0, 0},
      {"output", required_argument, 0, 0},
    };

    c = getopt_long(argc, argv, "Vhi:o:", long_options, &option_index);
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
        printf("option i with value '%s'\n", optarg);
        break;

      case O_OPTION:
        printf("option o with value '%s'\n", optarg);
        break;

      default:
        printf(INVALID_MESSAGE);
      }
  }

  exit(EXIT_SUCCESS);
}
