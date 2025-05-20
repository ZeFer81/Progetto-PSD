#include "lista_attivita.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Lista_attivita crea_lista_attivita() {
    Lista_attivita la;
    la.head = NULL;
    return la;
}

void aggiungi_attivita(Lista_attivita* la, Attivita_di_studio as) {
    Nodo* nuovo = (Nodo*)malloc(sizeof(Nodo));
    nuovo->attivita = as;
    nuovo->next = la->head;
    la->head = nuovo;
}

void elimina_attivita(Lista_attivita* la, const char* descrizione) {
    Nodo *curr = la->head, *prev = NULL;
    while (curr) {
        if (strcmp(curr->attivita.descrizione, descrizione) == 0) {
            if (prev) prev->next = curr->next;
            else la->head = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void genera_report(Lista_attivita* la) {
    Nodo* curr = la->head;
    printf("\n=== ATTIVITA' COMPLETATE ===\n");
    while (curr) {
        if (strcmp(curr->attivita.avanzamento, "completato") == 0)
            stampa_attivita(&curr->attivita);
        curr = curr->next;
    }
    curr = la->head;
    printf("\n=== ATTIVITA' IN CORSO ===\n");
    while (curr) {
        if (strcmp(curr->attivita.avanzamento, "in corso") == 0)
            stampa_attivita(&curr->attivita);
        curr = curr->next;
    }
    curr = la->head;
    printf("\n=== ATTIVITA' IN RITARDO ===\n");
    while (curr) {
        if (strcmp(curr->attivita.avanzamento, "in ritardo") == 0)
            stampa_attivita(&curr->attivita);
        curr = curr->next;
    }
}