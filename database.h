#ifndef DATABASE_H
#define DATABASE_H
#include "database.h"
#include "lista_attivita.h"

char* creazione_database(char *database_file_name);
char*creazione_file_singolo(char* collegamento, int size);
void scrittura_database(Item it, char* nome_database, char* collegamento);
lista_attivita lettura_database(char* database_name, lista_attivita lista, int ind) ;
void scorrimento_lista(char* database_name, AttivitaDiStudio att);
void eliminta_dal_database(char* database_name, lista_attivita lista);
char **gen_ind_file(int n);
char* concatena(char **array, int n);
#endif //DATABASE_H
