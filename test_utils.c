#include "/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/utils.h"
#include "string.h"

#define MAX_LONGITUD 256

//Pruebas de la funcion encodeBase64

int test00PasoABase64UnaFrase() {
	size_t outputLen = 0;
	char* frase = "En un lugar de La Mancha de cuyo nombre no quiero acordarme";
	char* fraseEnBase64 = "RW4gdW4gbHVnYXIgZGUgTGEgTWFuY2hhIGRlIGN1eW8gbm9tYnJlIG5vIHF1aWVybyBhY29yZGFybWU=";
	char* resultado = encodeBase64(frase,strlen(frase),&outputLen);

	if (strcmp(fraseEnBase64,resultado) == 0) {
		printf("Paso una frase a base64 : OK\n");
		return SUCCESS;
	} else {
		printf("Paso una frase a base64 : ERROR\n");
		return EXIT_FAILURE;
	}
}

int test01PasoABase64UnaFraseVacia() {
	size_t outputLen = 0;
	char* frase = "";
	char* resultado = encodeBase64(frase,strlen(frase),&outputLen);

	if (strcmp(frase,resultado) == 0) {
		printf("Paso una frase vacia a base64 : OK\n");
		return SUCCESS;
	} else {
		printf("Paso una frase vacia a base64 : ERROR\n");
		return EXIT_FAILURE;
	}
}

int test02PasoABase64UnaFraseInvalida() {
	size_t outputLen = 0;
	char* frase = NULL;
	char* resultado = encodeBase64(frase,-1,&outputLen);

	if (!resultado) {
		printf("Paso una frase invalida a base64 : OK\n");
		return SUCCESS;
	} else {
		printf("Paso una frase invalida a base64 : ERROR\n");
		return EXIT_FAILURE;
	}
}
/*
int test03ComparoResultadosConFuncionDeOtraBiblioteca() {
	size_t outputLen = 0;
	char* frase = "En un lugar de La Mancha de cuyo nombre no quiero acordarme";
	char* resultado = encodeBase64(frase,strlen(frase),&outputLen);

	if (strcmp(a64l(),resultado) == 0) {
		printf("Paso una frase a base64 : OK\n");
		return SUCCESS;
	} else {
		printf("Paso una frase a base64 : ERROR\n");
		return EXIT_FAILURE;
	}
}
*/

//Pruebas de la funcion decodeBase64

int test00DecodificoUnaFraseEnBase64() {
	size_t outputLen = 0;
	char* frase = "En un lugar de La Mancha de cuyo nombre no quiero acordarme";
	char* fraseEnBase64 = "RW4gdW4gbHVnYXIgZGUgTGEgTWFuY2hhIGRlIGN1eW8gbm9tYnJlIG5vIHF1aWVybyBhY29yZGFybWU=";
	char* resultado = decodeBase64(fraseEnBase64,strlen(fraseEnBase64),&outputLen);


	if (strcmp(frase,resultado) == 0) {
		printf("Decodifico frase en base64 : OK\n");
		return SUCCESS;
	} else {
		printf("Decodifico frase en base64 : ERROR\n");
		return EXIT_FAILURE;
	}
}

int test01DecodificoUnaFraseVacia() {
	size_t outputLen = 0;
	char* frase = "";
	char* resultado = decodeBase64(frase,strlen(frase),&outputLen);

	if (strcmp(frase,resultado) == 0) {
		printf("Decodifico una frase vacia : OK\n");
		return SUCCESS;
	} else {
		printf("Decodifico una frase vacia : ERROR\n");
		return EXIT_FAILURE;
	}
}

int test02DecodificoUnaFraseInvalida() {
	size_t outputLen = 0;
	char* frase = NULL;
	char* resultado = decodeBase64(frase,-1,&outputLen);

	if (!resultado) {
		printf("Decodifico una frase invalida : OK\n");
		return SUCCESS;
	} else {
		printf("Decodifico una frase invalida : ERROR\n");
		return EXIT_FAILURE;
	}
}

//Pruebas de la funcion encodeFileToBase64

int test00CodificoUsandoDosArchivosValidos() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/entrada.txt", "r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/textoCodificado.txt","r+");

	int resultado = encodeFileToBase64(inputFile,outputFile);
	char* inputFileEnconding = "RW4gdW4gbHVnYXIgZGUgTGEgTWFuY2hhIGRlIGN1eW8gbm9tYnJlIG5vIHF1aWVybyBhY29yZGFybWUgaG9sYSBjb21vIGVzdGFzIHN0ZQppaWplcmlyZyBlbCBmaW4gZGVsIG11bmRvCg==";

	if (resultado == SUCCESS) {
		char outputFileContent [MAX_LONGITUD];
		memset(outputFileContent,0,MAX_LONGITUD);
		fseek(outputFile, 0, SEEK_SET);
		fread(outputFileContent,sizeof(char),MAX_LONGITUD,outputFile);

		if (strcmp(inputFileEnconding,outputFileContent) == 0) {
			printf("Codifico usando dos archivos validos : OK\n");
			fclose(inputFile);
			fclose(outputFile);
			return SUCCESS;	
		} else {
			printf("Codifico usando dos archivos validos : ERROR\n");
			fclose(inputFile);
			fclose(outputFile);
			return EXIT_FAILURE;
		}
		

	} else {
		printf("Codifico usando dos archivos validos : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}

int test01CodificoUsandoArchivoDeInputInexistente() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/noExiste.txt", "r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/textoCodificado.txt","r+");

	int resultado = encodeFileToBase64(inputFile,outputFile);

	if (resultado == EXIT_FAILURE) {
		printf("Codifico usando archivo de input inexistente : OK\n");
		fclose(outputFile);
		return SUCCESS;
	} else {
		printf("Codifico usando archivo de input inexistente : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}

int test02CodificoUsandoArchivoDeOutputInexistente() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/entrada.txt", "r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/noExiste.txt","r+");

	int resultado = encodeFileToBase64(inputFile,outputFile);

	if (resultado == EXIT_FAILURE) {
		printf("Codifico usando archivo de output inexistente : OK\n");
		fclose(inputFile);
		return SUCCESS;
	} else {
		printf("Codifico usando archivo de output inexistente : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}


//Pruebas de la funcion decodeFileToBase64

int test00DecodificoUsandoDosArchivosValidos() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/textoCodificado.txt","r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/entrada.txt", "r+");

	int resultado = decodeFileFromBase64(inputFile,outputFile);
	char* inputFileDecoding = "En un lugar de La Mancha de cuyo nombre no quiero acordarme hola como estas ste\niijerirg el fin del mundo\n";

	if (resultado == SUCCESS) {
		char outputFileContent [MAX_LONGITUD];
		memset(outputFileContent,0,MAX_LONGITUD);
		fseek(outputFile, 0, SEEK_SET);
		fread(outputFileContent,sizeof(char),MAX_LONGITUD,outputFile);

		if (strcmp(inputFileDecoding,outputFileContent) == 0) {
			printf("Codifico usando dos archivos validos : OK\n");
			fclose(inputFile);
			fclose(outputFile);
			return SUCCESS;	
		} else {
			printf("Codifico usando dos archivos validos : ERROR\n");
			fclose(inputFile);
			fclose(outputFile);
			return EXIT_FAILURE;
		}
		

	} else {
		printf("Codifico usando dos archivos validos : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}

int test01DecodificoUsandoArchivoDeInputInexistente() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/noExiste.txt","r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/entrada.txt", "r+");

	int resultado = decodeFileFromBase64(inputFile,outputFile);

	if (resultado == EXIT_FAILURE) {
		printf("Deodifico usando archivo de input inexistente : OK\n");
		fclose(outputFile);
		return SUCCESS;
	} else {
		printf("Decodifico usando archivo de input inexistente : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}

int test02DecodificoUsandoArchivoDeOutputInexistente() {
	FILE* inputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/textoCodificado.txt","r+");
	FILE* outputFile = fopen("/home/franco/Escritorio/OrgaDelComputador/tp0-OrgaDelComputador/noExiste.txt", "r+");

	int resultado = decodeFileFromBase64(inputFile,outputFile);

	if (resultado == EXIT_FAILURE) {
		printf("Decodifico usando archivo de output inexistente : OK\n");
		fclose(inputFile);
		return SUCCESS;
	} else {
		printf("Decodifico usando archivo de output inexistente : ERROR\n");
		fclose(inputFile);
		fclose(outputFile);
		return EXIT_FAILURE;
	}
}

//Pruebas de uso

int test00PasoABase64UnaFraseYLuegoLaDecodifico() {
	size_t outputLen = 0;
	char* frase = "En un lugar de La Mancha de cuyo nombre no quiero acordarme";

	char* encode = encodeBase64(frase,strlen(frase),&outputLen);
	char* resultado = decodeBase64(encode,strlen(encode),&outputLen);
	
	if (strcmp(frase,resultado) == 0) {
		printf("Paso una frase a base64 y luego la decodifico : OK\n");
		return SUCCESS;
	} else {
		printf("Paso una frase a base64 y luego la decodifico : ERROR\n");
		return EXIT_FAILURE;
	}
}

int tests() {
	int resultado = 0;
	printf("---Incio pruebas de la funcion encodeBase64---\n\n");
	resultado += test00PasoABase64UnaFrase();
	resultado += test01PasoABase64UnaFraseVacia();
	resultado += test02PasoABase64UnaFraseInvalida();

	printf("\n---Incio pruebas de la funcion decodeBase64---\n\n");
	resultado += test00DecodificoUnaFraseEnBase64();
	resultado += test01DecodificoUnaFraseVacia();
	resultado += test02DecodificoUnaFraseInvalida();

	printf("\n---Incio pruebas de la funcion encodeFileToBase64---\n\n");
	resultado += test00CodificoUsandoDosArchivosValidos();
	resultado += test01CodificoUsandoArchivoDeInputInexistente();
	resultado += test02CodificoUsandoArchivoDeOutputInexistente();

	printf("\n---Incio pruebas de la funcion decodeFileToBase64---\n\n");
	resultado += test00DecodificoUsandoDosArchivosValidos();
	resultado += test01DecodificoUsandoArchivoDeInputInexistente();
	resultado += test02DecodificoUsandoArchivoDeOutputInexistente();

	printf("\n---Incio pruebas de uso---\n\n");
	resultado += test00PasoABase64UnaFraseYLuegoLaDecodifico();

	if (resultado == SUCCESS) return SUCCESS;
	else return EXIT_FAILURE;
}

int main() {
	return tests();
}