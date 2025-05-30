#include <stdio.h>
#include "funzione_test.h"
#include "lista_attivita.h"
#include <string.h>
#include "item-attivita_di_studio.h"
#include <stdlib.h>
#define MAX_STR 128


void svuotamento_buffer_file(char* buffer , FILE* stream  ) {
    if (strchr(buffer, '\n') == NULL) {
        int c;
        while ((c = fgetc(stream)) != '\n' && c != EOF);
    }
}

lista_attivita lettura_lista(char *nome_file_ingresso) {
    char descrizione[MAX_STR];
    char corso[MAX_STR];
    char buffer[MAX_STR];
    char stato[MAX_STR];
    int g, m, a;
    float ore;
    int priorita;

    FILE *fp = fopen(nome_file_ingresso, "r");
    if (!fp) {
        fprintf(stderr, "apertura %s fp fallita\n", nome_file_ingresso);
        return NULL;
    }

    lista_attivita L = crea_lista_attivita();
    int num_attivita = 1;

    while (1) {
        printf("DEBUG: Lettura attività %d\n", num_attivita);

        // DESCRIZIONE
        if (!stdin_pulizia(descrizione, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su descrizione\n");
            break;
        }
        descrizione[strcspn(descrizione, "\r\n")] = '\0';
        printf("DEBUG: descrizione = [%s]\n", descrizione);

        // CORSO
        if (!stdin_pulizia(corso, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su corso\n");
            break;
        }
        corso[strcspn(corso, "\r\n")] = '\0';
        printf("DEBUG: corso = [%s]\n", corso);

        // DATA
        if (!stdin_pulizia(buffer, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su data\n");
            break;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        printf("DEBUG: data = [%s]\n", buffer);
        if (sscanf(buffer, "%d %d %d", &g, &m, &a) != 3) {
            printf("DEBUG: Errore di parsing su data (attività %d)\n", num_attivita);
            break;
        }

        // ORE
        if (!stdin_pulizia(buffer, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su ore\n");
            break;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        printf("DEBUG: ore = [%s]\n", buffer);
        if (sscanf(buffer, "%f", &ore) != 1) {
            printf("DEBUG: Errore di parsing su ore (attività %d)\n", num_attivita);
            break;
        }

        // PRIORITA'
        if (!stdin_pulizia(buffer, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su priorita\n");
            break;
        }
        buffer[strcspn(buffer, "\r\n")] = '\0';
        printf("DEBUG: priorita = [%s]\n", buffer);
        if (sscanf(buffer, "%d", &priorita) != 1) {
            printf("DEBUG: Errore di parsing su priorita (attività %d)\n", num_attivita);
            break;
        }

        // STATO
        if (!stdin_pulizia(stato, MAX_STR, fp)) {
            printf("DEBUG: Fine file o errore su stato\n");
            break;
        }
        stato[strcspn(stato, "\r\n")] = '\0';
        printf("DEBUG: stato = [%s]\n", stato);

        // Se siamo arrivati qui, tutti i dati sono ok
        AttivitaDiStudio att = crea_attivita_di_studio(
            descrizione, corso, crea_data(g, m, a), ore, priorita, stato);
        if (!att) {
            printf("DEBUG: Errore creazione attività (attività %d)\n", num_attivita);
            continue;
        }
        aggiungi_attivita(L, att);
        printf("DEBUG: Attività %d aggiunta con successo\n", num_attivita);

        num_attivita++;
    }
    int s = lista_attivita_size(L);
    printf("DEBUG dimensione lista %d\n", s);
    fclose(fp);
    return L;
}
void scrittura_lista(char *nome_file_out, lista_attivita lista) {
    printf("Entrato in scrittura_lista\n");

    FILE *output = fopen(nome_file_out, "w");
    if (!output) {
        printf("apertura %s fallita\n", nome_file_out);
        return;
    } else
        printf("%s aperto\n", nome_file_out);


    int n = lista_attivita_size(lista);
    printf("Ciclo size_t fuori");

    for (int i = 0; i < n; i++)
    {
        printf("Ciclo size_t dentro");
        printf("Ciclo i=%d\n", i); // DEBUG
        AttivitaDiStudio att = lista_attivita_get(lista, i);
        if (!att) {
            fprintf(output, "Attivita non valida\n");
            continue;
        }
        Data d = attivita_get_data_scadenza(att);
        if (!data_valida(d)) {
            fprintf(output, "Errore: la data %02d/%02d/%04d non è valida.\n",
                    data_get_giorno(d), data_get_mese(d), data_get_anno(d));
            continue;
        }

        // Scrivi sul file con lo stesso formato dell’input:
        fprintf(output,"%s\n%s\n%d %d %d\n%.2f\n%d\n%s\n",
                attivita_get_descrizione(att),
                attivita_get_corso(att),
                data_get_giorno(d),
                data_get_mese(d),
                data_get_anno(d),
                attivita_get_tempo_stimato(att),
                attivita_get_priorita(att),
                attivita_get_avanzamento(att));

        printf("%s\n", attivita_get_descrizione(att));
        printf("%s\n", attivita_get_corso(att));
        Data d1 = attivita_get_data_scadenza(att);
        printf("%d %d %d\n", data_get_giorno(d1), data_get_mese(d1), data_get_anno(d1));
        printf("%.2f\n", attivita_get_tempo_stimato(att));
        printf("%d\n", attivita_get_priorita(att));
        printf("%s\n", attivita_get_avanzamento(att));
    }

    fclose(output);
}


void confronta_file(char *oracle_file, char *output_file, char *TC)
{
    FILE *res = fopen("result.txt","a");
    if (!res) {
        fprintf(res,"ERRORE apertura result.txt\n");
    } else {
        printf("Apertura result.txt riuscita\n");
    }

    FILE *orc = fopen(oracle_file, "r");
    if (!orc) {
        printf("%s - FAIL (no oracle)\n", oracle_file);
        fclose(res);
        fclose(orc);
        return;
    } else {
        printf("Apertura %s riuscita\n", oracle_file);
    }

    FILE *out = fopen(output_file, "r");
    if (!out) {
        fprintf(out,"%s - FAIL (no output)\n", output_file);
        fclose(res);
        fclose(orc);
        return;
    } else {
        printf("Apertura %s riuscita\n", output_file);
    }

    int diff = 0, c1, c2, pos = 0;
    printf("Sto confrontando i file: %s e %s\n", output_file, oracle_file);
    // Ciclo che legge finché entrambi i file NON sono finiti

    while (c1!= EOF || c2 != EOF) {


        printf("Posizione %d: output=%d (char='%c'), oracle=%d (char='%c')\n", pos, c1, (c1 >= 32 && c1 <= 126) ? c1 : '.', c2, (c2 >= 32 && c2 <= 126) ? c2 : '.');
        if (c1 != c2) {
            printf("Differenza trovata a posizione %d: output=%d, oracle=%d\n", pos, c1, c2);
            diff = 1;
            break;
        }
        c1 = fgetc(out) ;
        c2 = fgetc(orc) ;
        pos++;
    }

    // Se solo uno dei due file è finito, i file sono diversi
    if ((c1 != c2) && (diff == 0)) {
        printf("Fine file non simultanea: c1=%d, c2=%d a posizione %d\n", c1, c2, pos);
    }

    if (diff == 0 && c1 == c2) {
        printf("%s-PASS\n", TC);
        fprintf(res, "%s-PASS\n", TC);
    } else {
        printf("%s-FAIL\n", TC);
        fprintf(res, "%s-FAIL\n", TC);
    }
    fclose(out);
    fclose(orc);
    fclose(res);
}


void run_test(char *tc_name,
              char *input_file,
              char *output_file,
              char *oracle_file)
{
    lista_attivita L = lettura_lista(input_file);
    scrittura_lista(output_file, L);
    confronta_file(oracle_file, output_file, tc_name);
    libera_lista(L);
}
