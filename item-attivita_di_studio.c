/*
 * File: item-attivita_di_studio.c
 * Scopo: Gestione interazione utente per creare e gestire oggetti
 *        AttivitaDiStudio, includendo input validato e confronto tra
 *        attività.
 *
 * Questo file contiene funzioni per:
 *  - Creare un oggetto AttivitaDiStudio tramite input testuale.
 *  - Validare input utente (stringhe, numeri, date).
 *  - Confrontare attività in base alla data di scadenza.
 *  - Stampare i dettagli di un'attività.
 *
 * Le funzioni sono progettate per garantire robustezza
 * nell'interazione utente e mantenere i dati coerenti.
 */

#include "item-attivita_di_studio.h"
#include <stdio.h>
#include "data.h"
#include "attivita_di_studio.h"
#include <string.h>

#define MASS_STR      128
#define MASS_AVANZAMENTO       64
#define MASS_TEMPO_ORE         1000.0f
#define MIN_TEMPO_ORE         0.10f
#define MIN_PRIORITA 1
#define MASS_PRIORITA  3

/*
 * Funzione: valida_stringa
 * Scopo: Verifica se una stringa è valida, rispettando lunghezza massima
 *        e possibilità di essere vuota.
 * Parametri:
 *  - str: puntatore alla stringa.
 *  - max_len: lunghezza massima ammessa.
 *  - consenti_str_vuota: true se sono permesse stringhe vuote.
 * Ritorna: true se valida, false altrimenti.
 */
bool valida_stringa(char *str, int max_len,bool consenti_str_vuota)
{
    if (!str)
        return false;

    int len = strlen(str);

    if (len > max_len) {
        return false;
    }
    if (len == 0) {
        return consenti_str_vuota;
    }

    return true;
}

/*
 * Funzione: svuotamento_buffer
 * Scopo: Svuota il buffer di input fino a newline o EOF.
 * Motivazione: Previene problemi di input residuo in stdin.
 */
void svuotamento_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
 * Funzione: stdin_pulizia
 * Scopo: Legge una stringa da input, rimuove newline e pulisce il buffer
 *        se necessario.
 * Parametri:
 *  - stringa: buffer di destinazione.
 *  - max_len: lunghezza massima.
 *  - stream: stream di input.
 * Ritorna: puntatore alla stringa o NULL se errore.
 */
char *stdin_pulizia(char* stringa, int max_len, FILE *stream) {
    char *ret = fgets(stringa, max_len, stream);
    if (ret == NULL) {
        return NULL;
    }

    if (strchr(stringa, '\n') == NULL) {
        int ch;
        while ((ch = fgetc(stream)) != '\n' && ch != EOF)
            ;
        stringa[max_len - 1] = '\0';
        return NULL;
    }
    stringa[strcspn(stringa, "\n")] = '\0';
    return stringa;
}

/*
 * Funzione: input_stringa
 * Scopo: Gestisce l'input di una stringa con validazione.
 * Parametri:
 *  - stringa: buffer destinazione.
 *  - max_lun_stringa: lunghezza massima.
 * Ritorna: puntatore alla stringa o NULL se errore.
 */
char *input_stringa(char* stringa, int max_lun_stringa) {
    for (;;) {
        if (stdin_pulizia(stringa,max_lun_stringa,stdin) == NULL) {
            fprintf(stderr,"Errore stringa troppo lunga\n");
            return NULL;
        }
        if (!valida_stringa(stringa, max_lun_stringa,true)) {
            svuotamento_buffer();
            return NULL;
        }
        stringa[strcspn(stringa, "\n")] = '\0';
        return stringa;
    }
}

/*
 * Funzione: generic_input_control_float
 * Scopo: Gestisce input float generico con validazione di range.
 * Parametri:
 *  - a: attività di riferimento.
 *  - generic_float: valore float.
 *  - min_value, max_value: range ammesso.
 *  - messaggio: prompt utente.
 *  - setter, getter: funzioni per modificare e leggere il valore.
 * Ritorna: float validato.
 */
float generic_input_control_float(AttivitaDiStudio a, float generic_float, float min_value, float max_value,char *messaggio, bool (*setter)(AttivitaDiStudio,float), float (*getter)(AttivitaDiStudio)) {
    char buf[MASS_STR];
    generic_float = getter(a);
    for (;;) {
        printf("%s", messaggio);

        if (input_stringa(buf, MASS_STR) == NULL) {
            svuotamento_buffer();
            continue;
        }
        if (buf[0] == '\0') {
            svuotamento_buffer();
            continue;
        }
        if (sscanf(buf, "%f", &generic_float) != 1 || generic_float < min_value || generic_float > max_value) {
            printf("Numero non valido o troppo piccolo! Riprova.\n");
            svuotamento_buffer();
            continue;
        }
        setter(a, generic_float);
        return generic_float;
    }
}

/*
 * Funzione: generic_input_int_range
 * Scopo: Gestisce input intero generico con validazione di range.
 * Parametri:
 *  - a: attività.
 *  - generic_int: valore intero.
 *  - min_valore, max_valore: limiti ammessi.
 *  - messaggio: prompt.
 *  - setter, getter: funzioni di accesso.
 * Ritorna: int validato.
 */
int generic_input_int_range(
    AttivitaDiStudio a,
    int generic_int,
    int min_valore,
    int max_valore,
    char *messaggio,
    bool (*setter)(AttivitaDiStudio, int),
    int (*getter)(AttivitaDiStudio)
) {
    char buf[MASS_STR];
    generic_int = getter(a);
    for (;;) {
        printf("%s", messaggio);
        if (input_stringa(buf, MASS_STR) == NULL) {
            svuotamento_buffer();
            continue;
        }
        if (buf[0] == '\0') {
            continue;
        }

        if (sscanf(buf, "%d", &generic_int) != 1 ) {
            printf("Input non valido! Riprova.\n");
            svuotamento_buffer();
            continue;
        }
        if (generic_int < min_valore || generic_int > max_valore) {
            printf("Valore fuori dal range [%d, %d]! Riprova.\n", min_valore, max_valore);
            svuotamento_buffer();
            continue;
        }
        setter(a, generic_int);
        return generic_int;
    }
}

/*
 * Funzione: controllo_stringa_accettati
 * Scopo: Permette solo stringhe corrispondenti a un valore specifico.
 * Parametri:
 *  - a: attività.
 *  - stringa: valore accettato.
 * Ritorna: nuova stringa duplicata valida.
 */
char* controllo_stringa_accettati(AttivitaDiStudio a,char *stringa) {
    char buf[MASS_AVANZAMENTO];

    for (;;) {
        if (input_stringa(buf,MASS_AVANZAMENTO)==NULL) {
            svuotamento_buffer();
            continue ;
        }
        buf[strcspn(buf, "\n")] = '\0';

        if (buf[0] == '\0') {
            continue;
        }

        if (strcmp(buf, stringa) == 0)
        {
            return strdup(buf);
        }
    }
}

/*
 * Funzione: generic_input_control_Data
 * Scopo: Gestisce l'input di una data valida non antecedente a oggi.
 * Parametri:
 *  - att: attività.
 *  - giorno, mese, anno: dati data.
 *  - messaggio: prompt.
 *  - max_lun_stringa: lunghezza massima.
 *  - setter, getter: accesso data.
 * Ritorna: Data validata.
 */
Data generic_input_control_Data(
    AttivitaDiStudio att,
    int giorno, int mese,int anno,
    char* messaggio,
    int max_lun_stringa,
    bool (*setter)(AttivitaDiStudio, Data),
    Data (*getter)(AttivitaDiStudio)) {

    char buf[MASS_STR];
    Data data_funz = getter(att);
    int g = data_get_giorno(data_funz);
    int m = data_get_mese(data_funz);
    int a = data_get_anno(data_funz);
    for (;;) {
        printf("%s(%d %d %d): ",messaggio, g, m, a);
        if (input_stringa(buf, max_lun_stringa) == NULL) {
            printf("Input troppo lungo o errore. Riprova.\n");
            continue;
        }

        if (buf[0] == '\0') {
            printf("Input vuoto. Riprova.\n");
            continue;
        }

        if (sscanf(buf, "%d %d %d", &giorno, &mese, &anno) != 3) {
            printf("Formato data non valido! Usa: GG MM AAAA\n");
            continue;
        }
        data_funz = crea_data(giorno, mese, anno);

        if (!data_valida(data_funz)) {
            printf("La data inserita non è valida! Riprova.\n");
            continue;
        }
        if (confronta_date(data_funz, data_odierna()) < 0) {
            printf("La data inserita è antecedente a oggi. Riprova.\n");
            continue;
        }
        setter(att,data_funz);
        return data_funz;
    }
}

/*
 * Funzione: generic_str_set
 * Scopo: Gestisce l'input e il set di una stringa con validazione
 *        interna.
 * Parametri:
 *  - stringa: buffer.
 *  - messaggio: prompt.
 *  - max_lun_stringa: lunghezza massima.
 *  - att: attività.
 *  - setter, getter: funzioni.
 * Ritorna: stringa impostata.
 */
char *generic_str_set(char *stringa,char*messagio, int max_lun_stringa,AttivitaDiStudio att,bool (*setter) (AttivitaDiStudio, char*),char* (*getter)(AttivitaDiStudio)){
    strncpy(stringa, getter(att), max_lun_stringa-1);
    stringa[max_lun_stringa-1] = '\0';
    for (;;) {
        printf("%s", messagio);
        if (input_stringa(stringa, max_lun_stringa) == NULL)
            continue;
        if (setter(att, stringa)) {
            break;
            }
        fprintf(stderr,"contenuto %s non valido. Riprova.\n",stringa);
    }
    return stringa;
}

/*
 * Funzione: inputItem
 * Scopo: Effettua interazione utente per creare una nuova attività.
 * Dettagli:
 *  - Richiede descrizione, corso, data valida, tempo stimato,
 *    priorità e stato.
 * Ritorna: nuovo oggetto AttivitaDiStudio o NULL se errore.
 */
Item inputItem() {
    char descrizione[MASS_STR];
    char corso[MASS_STR];

    AttivitaDiStudio att = crea_attivita_di_studio(
        "", "", data_odierna(), MIN_TEMPO_ORE, 0, "in corso"
    );
    if (!att) return NULL;

    generic_str_set(descrizione,"Inerisci descrizione del corso: ",MASS_STR, att, attivita_set_descrizione,attivita_get_descrizione);

    generic_str_set(corso,"Inserire nome corso: ",MASS_STR, att, attivita_set_corso,attivita_get_corso);

    Data data_oggi = attivita_get_data_scadenza(att);
    int g = data_get_giorno(data_oggi);
    int m = data_get_mese(data_oggi);
    int a = data_get_anno(data_oggi);

    generic_input_control_Data(att,g,m,a,"inserisci data di scadenza es ",MASS_AVANZAMENTO,attivita_set_data_scadenza,attivita_get_data_scadenza);

    float tempo_stimato_ore;
    generic_input_control_float(att,tempo_stimato_ore,MIN_TEMPO_ORE,MASS_TEMPO_ORE,"Inserire tempo stimao al completamento dell'attivita: ",attivita_set_tempo_stimato,attivita_get_tempo_stimato);

    int priorita;
    generic_input_int_range(att, priorita, MIN_PRIORITA, MASS_PRIORITA, "Inserire priorità (1 a 3) '1 = Alta, 2 = Media, 3 = Bassa: ", attivita_set_priorita, attivita_get_priorita);

    char avanzamento[MASS_AVANZAMENTO];
    generic_str_set(avanzamento,"Inserisci stato attivita 'completata, in corso, in ritardo': ",MASS_AVANZAMENTO,att,attivita_set_avanzamento,attivita_get_avanzamento);

    return att;
}

/*
 * Funzione: outputItem
 * Scopo: Stampa i dettagli di un'attività usando stampa_attivita.
 * Parametri:
 *  - item_a_schermo: attività da mostrare.
 */
void outputItem(Item item_a_schermo) {
    stampa_attivita(item_a_schermo);
}

/*
 * Funzione: cmpItem
 * Scopo: Confronta due attività in base alla loro data di scadenza.
 * Parametri:
 *  - item1, item2: attività da confrontare.
 * Ritorna: <0 se item1 < item2, 0 se uguali, >0 se item1 > item2.
 */
int cmpItem(Item item1, Item item2) {
    AttivitaDiStudio a1 = item1;
    AttivitaDiStudio a2 = item2;
    return confronta_date(
        attivita_get_data_scadenza(a1),
        attivita_get_data_scadenza(a2)
    );
}
