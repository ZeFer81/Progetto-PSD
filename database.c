#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista_attivita.h"
#include "attivita_di_studio.h"
#include "data.h"
#include "funzione_test.h"
#define MAX_STR 128

char **gen_ind_file(int n) {
    char **ind = malloc(n * sizeof(char *));
    if (ind == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        // Alloca spazio per ogni stringa (fino a 11 cifre + terminatore)
        ind[i] = malloc(12 * sizeof(char));
        if (ind[i] == NULL) {
            // Libera la memoria già allocata in caso di errore
            for (int j = 0; j < i; j++) free(ind[j]);
            free(ind);
            return NULL;
        }
        sprintf(ind[i], "%d", i); // Da 1 a n
    }
    return ind;
}

char* concatena(char **array, int n) {
    int len = 0;
    for (int i = 0; i < n; i++) {
        len += strlen(array[i]);
    }
    char *result = malloc(len + 1); // +1 per '\0'
    if (result == NULL) return NULL;
    result[0] = '\0';

    for (int i = 0; i < n; i++) {
        strcat(result, array[i]);
    }
    return result;
}
char *creazione_file_singolo(char* collegamento, int size) {

    FILE *link[size];
    for (int i = 0; i < size; i++) {
       link[size] = fopen(collegamento , "w");

        if(link[size] == NULL) {
            printf("database[%d] in opening file : \n", i);
        }
    }

    char * liked_file = collegamento;
     return liked_file;

}

char* creazione_database(char *database_file_name) {
    FILE *database_file = fopen(database_file_name, "w");
    if (database_file == NULL) {
        return NULL;
    }
    char * data_file_name = database_file_name;
    return data_file_name;
}

void scrittura_database(Item it, char* nome_database, char* collegamento) {


        FILE *database = fopen(nome_database , "a+");
        if(database == NULL)
        {
            database = fopen(collegamento , "r+");
            if(database == NULL)
            {
                printf("database in opening file : \n");
                return;
            }
        }


       FILE *file = fopen(collegamento , "a+");
        if(file == NULL)
        {
            file = fopen(collegamento , "r+");
            if(file == NULL)
            {
                printf("database in opening file : \n");
                return;
            }
        }
        //printf("Ciclo size_t fuori");
        AttivitaDiStudio att = it;
        Data data_provvioria = attivita_get_data_scadenza(att);
        Data data_di_creazione = attivita_get_data_scadenza(att);

        int g = data_get_giorno(data_provvioria);
        int m = data_get_mese(data_provvioria);
        int a = data_get_anno(data_provvioria);

        int gc = data_get_giorno(data_creazione);
        int mc = data_get_mese(data_creazione);
        int ac = data_get_anno(data_creazione);

        int sec = data_get_secondi(data_di_creazione);
        int min = data_get_secondi(data_di_creazione);
        int ore = data_get_secondi(data_di_creazione);

        Data d = crea_data(g, m, a);
            // Scrivi sul file con lo stesso formato dell’input:
        fprintf(file,"%s\n%s\n%d %d %d\n%d %d %d n%d %d %d\n%.2f\n%d\n%s\n",
                    attivita_get_descrizione(att),
                    attivita_get_corso(att),
                    data_get_giorno(d),
                    data_get_mese(d),
                    data_get_anno(d),

                    data_get_giorno(data_provvioria),
                    data_get_mese(data_di_creazione),
                    data_get_anno(data_di_creazione),


                    data_get_secondi(data_provvioria),
                    data_get_minuti(data_provvioria),
                    data_get_ore(data_di_creazione),


                    attivita_get_tempo_stimato(att),
                    attivita_get_priorita(att),
                    attivita_get_avanzamento(att));
    fprintf(database,"%s\n%s\n%d %d %d\n%d %d %d n%d %d %d\n%.2f\n%d\n%s\n",
            attivita_get_descrizione(att),
            attivita_get_corso(att),
            data_get_giorno(d),
            data_get_mese(d),
            data_get_anno(d),

            data_get_giorno(data_provvioria),
            data_get_mese(data_di_creazione),
            data_get_anno(data_di_creazione),


            data_get_secondi(data_provvioria),
            data_get_minuti(data_provvioria),
            data_get_ore(data_di_creazione),


            attivita_get_tempo_stimato(att),
            attivita_get_priorita(att),
            attivita_get_avanzamento(att));


    fclose(file);
    fclose(database);
}
lista_attivita lettura_database(char* database_name, lista_attivita lista, int ind) {

    FILE *database[ind];
    for (int i = 0; i < ind; i++) {
        database[ind] = fopen(database_name , "w");

        if(database[ind] == NULL) {
            printf("database[%d] in opening file : \n", i);
        }
    }
     lista = lettura_lista(database_name);
    return lista;
}

/*void eliminta_dal_database(char* database_name, lista_attivita lista) {
    FILE *f = fopen("database.dat", "w"); // "w" = scrittura, sovrascrive tutto
    if (f == NULL) {
        printf("Errore apertura file.\n");
    }


    lista_attivita L = lettura_database(database_name, lista);
    size_t n = lista_attivita_size(lista);
    for (size_t i = 0; i < n; i++) {
        AttivitaDiStudio att = lista_attivita_get(lista, i);
        printf("[%zu]\n", i);
        stampa_attivita(att);
        printf("\n");




    }





}*/

/*void scorrimento_lista(char* database_name, AttivitaDiStudio att) {
    FILE *database = fopen(database_name , "r");
    if (database == NULL) {
        printf("Errore apertura file.\n");
    }
    Data d = attivita_get_data_scadenza(att);
    char * descrizione = attivita_get_descrizione(att);
    char* corso = attivita_get_corso(att);
    int giorno = data_get_giorno(d);
    int mese= data_get_mese(d);
    int anno = data_get_anno(d);
    int tempo_stimato = attivita_get_tempo_stimato(att);
    int priorita = attivita_get_priorita(att);
    char * stato = attivita_get_avanzamento(att);

    fscanf(database,"%s\n%s\n%d %d %d\n%.2f\n%d\n%s\n",
                attivita_get_descrizione(att),
                attivita_get_corso(att),
                data_get_giorno(d),
                data_get_mese(d),
                data_get_anno(d),
                attivita_get_tempo_stimato(att),
                attivita_get_priorita(att),
                attivita_get_avanzamento(att));

    AttivitaDiStudio attivita = crea_attivita_di_studio(
        descrizione, corso, crea_data(giorno, mese, anno), tempo_stimato, priorita, stato);
    if (!att){}
    scrittura_database(att, database_name);
}*/

