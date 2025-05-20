# Nome del file eseguibile finale
EXECUTABLE = programma.exe

# Compilatore
CC = gcc

# Opzioni di compilazione
CFLAGS = -Wall -Wextra

# File sorgenti
SRC = main.c data.c attivita.c lista_attivita.c

# File oggetto (trasforma i .c in .o)
OBJ = $(SRC:.c=.o)

# Regola principale
all: $(EXECUTABLE)

# Linking finale
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compilazione dei file .c in .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Pulizia dei file compilati (Windows-friendly)
clean:
	del /Q *.o $(EXECUTABLE) 2>nul || exit 0

.PHONY: all clean
