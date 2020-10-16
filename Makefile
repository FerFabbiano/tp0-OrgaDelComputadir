CC = gcc
# nombre del ejecutable
TARGET = tp0
NAME = Makefile
# para obtener lista de archivos .c en el directorio.
FUENTES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
OBJS = $(patsubst %.cpp,%.o,$(FUENTES))

CC_FLAGS = -g -std=c99 -Wall -Werror -pedantic 
	
%.o: $(FUENTES)
	echo "Target $@ -> Compilando $<"
	$(CC) -c $(CC_FLAGS) $<


$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LDFLAGS) 

clean:
	$(RM) *.o $(TARGET) $(TARGET).zip

entrega:
	zip $(TARGET).zip $(FUENTES) $(HEADERS) $(NAME)

.PHONY: run
