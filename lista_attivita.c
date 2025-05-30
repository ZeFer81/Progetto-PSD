/* lista_attivita.c */

#include "lista_attivita.h"
#include "list.h"
#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct lista_attivita {
    List intern;  // lista interna di AttivitaDiStudio
};

/* Crea una nuova lista di attività */
lista_attivita crea_lista_attivita(void) {
    lista_attivita L = malloc(sizeof *L);
    if (!L) {
        free(L);
        return NULL;
    }
    L->intern = newList();
    return L;
}

/* Libera la lista e tutte le attività in essa contenute */
void libera_lista(lista_attivita lista) {
    if (!lista) return;
    while (!isEmpty(lista->intern)) {
        AttivitaDiStudio a = removeHead(lista->intern);
        distruggi_attivita(a);
    }
    free(lista);
}

/* Aggiunge un’attività in coda */
lista_attivita aggiungi_attivita(lista_attivita lista, AttivitaDiStudio att) {
    if (lista && att)
        addListTail(lista->intern, att);
    return lista;
}

/* Rimuove la prima occorrenza di un’attività */
lista_attivita elimina_attivita(lista_attivita lista, AttivitaDiStudio att) {
    if (lista && att)
        removeListItem(lista->intern, att);
    return lista;
}

/* Restituisce il numero di attività presenti */
int lista_attivita_size(lista_attivita lista) {
    return lista ? sizeList(lista->intern) : 0;
}

/* Ottiene l’attività all’indice idx senza eliminare la lista originale */
AttivitaDiStudio lista_attivita_get(lista_attivita lista, int idx) {
    if (!lista) return NULL;
    List temp = cloneList(lista->intern);
    AttivitaDiStudio result = NULL;
    for (int i = 0; i <= idx && !isEmpty(temp); i++) {
        AttivitaDiStudio a = removeHead(temp);
        if (i == idx) result = a;
    }
    while (!isEmpty(temp))
        removeHead(temp); // svuota temp
    return result;
}

/* Modifica lo stato di avanzamento di una specifica attività */
void lista_attivita_set_avanzamento(lista_attivita lista, int idx, char* nuovo_stato) {
    AttivitaDiStudio a = lista_attivita_get(lista, idx);
    if (a)
        attivita_set_avanzamento(a, nuovo_stato);
}

/* Selezione interattiva di indice da tastiera */
static size_t scegli_indice(lista_attivita lista, const char* prompt) {
    size_t n = lista_attivita_size(lista);
    if (n == 0) {
        printf("Lista vuota\n");
        return (size_t)-1;
    }
    printf("%s (0..%zu): ", prompt, n - 1);
    size_t idx;
    if (scanf("%zu", &idx) != 1 || idx >= n) {
        printf("Indice non valido.\n");
        return (size_t)-1;
    }
    return idx;
}

/* Interattivo: segna in ritardo l’attività scelta */
void segna_ritardo_interattivo(lista_attivita lista) {
    size_t i = scegli_indice(lista, "Indice da segnare in ritardo l'attivita");
    if (i != (size_t)-1)
        lista_attivita_set_avanzamento(lista, i, "in ritardo");
}

/* Interattivo: segna completata l’attività scelta */
void segna_completata_interattivo(lista_attivita lista) {
    size_t i = scegli_indice(lista, "Indice da segnare completata l'attivita");
    if (i != (size_t)-1)
        lista_attivita_set_avanzamento(lista, i, "completata");
}

/* Interattivo: segna in corso l’attività scelta */
void segna_in_corso_interattivo(lista_attivita lista) {
    size_t i = scegli_indice(lista, "Indice da segnare in corso l'attivita");
    if (i != (size_t)-1)
        lista_attivita_set_avanzamento(lista, i, "in corso");
}

/* Imposta “in ritardo” per tutte le attività scadute */
void aggiorna_stati_ritardo(lista_attivita lista) {
    size_t n = lista_attivita_size(lista);
    Data dm = data_odierna();
    for (size_t i = 0; i < n; i++) {
        AttivitaDiStudio a = lista_attivita_get(lista, i);
        if (giorni_alla_scadenza_attivita(a, dm) < 0)
            attivita_set_avanzamento(a, "in ritardo");
    }
}

/* Stampa una sezione di attività con titolo */
void stampa_sezione(const char *titolo, List sezione) {
    printf("=== %s ===\n", titolo);
    if (isEmpty(sezione)){
        printf("Nessuna attività\n");
        printf("\n");
    }else{
        printList(sezione);
        printf("\n");
    }
}

/* Genera un report suddiviso per stato di avanzamento */
void genera_report(lista_attivita lista) {
    List com = newList(), cor = newList(), rit = newList();
    size_t n = lista_attivita_size(lista);

    for (size_t i = 0; i < n; ++i) {
        AttivitaDiStudio a = lista_attivita_get(lista, i);
        const char *st = attivita_get_avanzamento(a);
        if (strcmp(st, "completata") == 0) addListTail(com, a);
        else if (strcmp(st, "in corso") == 0) addListTail(cor, a);
        else if (strcmp(st, "in ritardo") == 0) addListTail(rit, a);
    }

    stampa_sezione("Completate", com);
    stampa_sezione("In corso", cor);
    stampa_sezione("In ritardo", rit);

    while (!isEmpty(com)) removeHead(com);
    while (!isEmpty(cor)) removeHead(cor);
    while (!isEmpty(rit)) removeHead(rit);
    free(com);
    free(cor);
    free(rit);
}

/* Stampa l’elenco completo delle attività con indice */
void stampa_elenco_attivita(lista_attivita lista) {
    size_t n = lista_attivita_size(lista);
    if (n == 0) {
        printf("\n=== Lista Vuota ===\n");
        return;
    }
    for (size_t i = 0; i < n; i++) {
        AttivitaDiStudio a = lista_attivita_get(lista, i);
        printf("[%zu]\n", i);
        stampa_attivita(a);
        printf("\n");
    }
}
