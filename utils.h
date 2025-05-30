#include "item-attivita_di_studio.h"

/**
* swap - Scambia il contenuto di due elementi di tipo Item.
*
* Parametri:
*   a: Puntatore al primo Item da scambiare. Deve essere non-NULL e puntare
*       a una variabile di tipo Item valida e inizializzata.
*   b: Puntatore al secondo Item da scambiare. Deve essere non-NULL e puntare
*       a una variabile di tipo Item valida e inizializzata.
*
* Precondizioni:
*   - `a` != NULL
*   - `b` != NULL
*   - `*a` e `*b` devono essere stati allocati e inizializzati correttamente.
*
* Postcondizioni:
*   - Il valore originale di `*a` è ora in `*b`.
*   - Il valore originale di `*b` è ora in `*a`.
*   - Nessun altro oggetto o variabile globale viene modificato.
*   - Non ci sono perdite di memoria né side-effects non dichiarati
*/
void swap(Item *a, Item *b);
