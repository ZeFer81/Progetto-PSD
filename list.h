#ifndef ITEM_H
#define ITEM_H
#include "item-attivita_di_studio.h"

typedef struct list *List;

/* Crea una lista vuota.
 * Pre-condizione: nessuna.
 * Post-condizione: restituisce una List valida, vuota.
 */
List newList();

/* Verifica se la lista è vuota.
 * Pre-condizione: l != NULL.
 * Post-condizione: nessuna.
 * Ritorna: 1 se vuota, 0 altrimenti.
 */
int isEmpty(List);

/* Inserisce un elemento in testa.
 * Pre-condizione: l != NULL.
 * Post-condizione: head aggiornato, size incrementato.
 */
void addHead(List, Item);

/* Rimuove e restituisce l’elemento in testa.
 * Pre-condizione: l != NULL.
 * Post-condizione: head spostato, size decrementato.
 * Ritorna: Item rimosso o NULL se vuota.
 */
Item removeHead(List);

/* Legge l’elemento in testa senza rimuoverlo.
 * Pre-condizione: l != NULL.
 * Post-condizione: nessuna.
 * Ritorna: Item in testa o NULL se vuota.
 */
Item getHead(List);

/* Restituisce il numero di elementi.
 * Pre-condizione: l != NULL.
 * Post-condizione: nessuna.
 * Ritorna: intero >= 0.
 */
int sizeList(List);

/* Stampa tutti gli elementi in ordine.
 * Pre-condizione: l != NULL.
 * Post-condizione: output su stdout.
 */
void printList(List);

/* Ordina la lista in loco (selezione).
 * Pre-condizione: l != NULL.
 * Post-condizione: elementi ordinati.
 */
void sortList(List);

/* Cerca un elemento nella lista.
 * Pre-condizione: l != NULL, pos != NULL.
 * Post-condizione: *pos = indice o -1.
 * Ritorna: Item trovato o NULL.
 */
Item searchListItem(List, Item, int *);

/* Rimuove il primo elemento uguale a item.
 * Pre-condizione: l != NULL.
 * Post-condizione: size decrementato.
 * Ritorna: Item rimosso o NULL.
 */
Item removeListItem(List, Item);

/* Rimuove l’elemento in posizione pos.
 * Pre-condizione: l != NULL.
 * Post-condizione: size decrementato.
 * Ritorna: Item rimosso o NULL se pos invalido.
 */
Item removeListPos(List, int);

/* Inserisce item in posizione pos.
 * Pre-condizione: l != NULL.
 * Post-condizione: size incrementato se ok.
 * Ritorna: 1 se inserito, 0 altrimenti.
 */
int addListPos(List, Item, int);

/* Aggiunge item in coda.
 * Pre-condizione: l != NULL.
 * Post-condizione: size incrementato se ok.
 * Ritorna: 1 se aggiunto, 0 altrimenti.
 */
int addListTail(List, Item);

/* Inverte l’ordine dei nodi.
 * Pre-condizione: l != NULL.
 * Post-condizione: lista invertita.
 */
void reverseList(List);

/* Crea e restituisce una copia profonda.
 * Pre-condizione: l != NULL.
 * Post-condizione: nuova lista allocata.
 * Ritorna: copia o NULL se errore.
 */
List cloneList(List);

#endif // ITEM_H