#ifndef LISTA_ATTIVITA_H
#define LISTA_ATTIVITA_H

#include "attivita.h"

typedef struct Nodo {
    Attivita_di_studio attivita;
    struct Nodo* next;
} Nodo;

typedef struct {
    Nodo* head;
} Lista_attivita;

Lista_attivita crea_lista_attivita();
void aggiungi_attivita(Lista_attivita* la, Attivita_di_studio as);
void elimina_attivita(Lista_attivita* la, const char* descrizione);
void genera_report(Lista_attivita* la);

#endif