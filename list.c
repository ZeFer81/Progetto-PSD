#include "list.h"
#include <stdlib.h>
#include "utils.h"

struct list
{
    int size;
    struct node *head;
};

struct node
{
    Item value;
    struct node *next;
};

struct node * minimo(struct node *p);

List newList()
{
    List l = malloc(sizeof(struct list));
    l->size = 0;
    l->head = NULL;
    return l;
}

int isEmpty(List l)
{
    if (l->size == 0)
        return 1;
    else
        return 0;
}

void addHead(List l, Item a)
{
    if (!l) return;
    struct node *n = malloc(sizeof(struct node));
    if (!n) return;
    n->next = l->head;
    n->value = a;
    l->head = n;
    l->size++;
}

Item removeHead(List l)
{
    if (isEmpty(l))
    {
        return NULL;
    }
    struct node *t = l->head;
    l->head = t->next;
    Item v = t->value;
    free(t);
    l->size--;
    return v;
}

Item getHead(List l)
{
    if (isEmpty(l))
    {
        return NULL;
    }
    return l->head->value;
}

int sizeList(List l)
{
    return l->size;
}

void printList(List l)
{
    struct node *p;
    for (p = l->head; p != NULL; p = p->next)
    {
        outputItem(p->value);
    }
}

void sortList(List l)
{
    struct node *p, *pos_minimo;
    for(p = l->head; p != NULL; p = p->next){
      pos_minimo = minimo(p);
      swap(&(pos_minimo->value), &(p->value));
    }
}

struct node * minimo(struct node *p)
{
    struct node *i, *min = p;
    for(i = p; i != NULL; i = i->next){
      if((cmpItem(min->value, i->value)) > 0)
        min = i;
    }
    return min;
}

Item searchListItem(List list, Item item, int *pos)
{
    struct node *p;
    *pos = 0;
    for (p = list->head; p != NULL; p = p->next)
    {

        if (cmpItem(item, p->value) == 0)
            return p->value;

        (*pos)++;
    }
    *pos = -1;
    return NULL;
}
Item removeListItem(List list, Item item)
{
    struct node *p;
    struct node *prev= NULL;
    if (isEmpty(list))
        return NULL;

    for (p = list->head; p != NULL; prev = p, p = p->next)
    {
        if (cmpItem(item, p->value) == 0)
        {
            if (prev == NULL)
                return removeHead(list);

            prev->next = p->next;
            Item v = p->value;
            free(p);
            list->size--;
            return v;
        }
    }
    return NULL;
}
Item removeListPos(List list, int pos)
{
    struct node *p;
    struct node *prev = NULL;
    int count = 0;

    if (isEmpty(list) || pos < 0 || pos >= list->size)
        return NULL;

    for (p = list->head; p != NULL; prev = p, p = p->next, count++)
    {

        if (count == pos)
        {

            if (prev == NULL)
                return removeHead(list);

            prev->next = p->next;
            Item v = p->value;
            free(p);
            list->size--;
            return v;
        }
    }
    return NULL;
}

int addListPos(List l, Item item, int pos){

    int i=0;
    struct node *p;

    if (!l)
        return 0;

    if(pos<0 || pos>(l->size))
        return 0;

    if(pos==0){
        addHead(l,item);
        return 1;
    }

    for(p=l->head;p!=NULL && i<pos-1 ;i++,p=p->next) {

    }

    if (!p)
        return 0;

    struct node *newNode=malloc(sizeof(struct node));
    newNode->value=item;
    newNode->next=p->next;

    p->next=newNode;

    l->size++;

    return 1;

}


int addListTail(List l, Item item){
    return addListPos(l,item, l->size);
}


void reverseList(List l){

    struct node *p, *prev=NULL, *temp;
    for(p=l->head; p!=NULL;prev=p, p=temp){

        temp=p->next;
        p->next=prev;

    }

    l->head=prev;

}

List cloneList(List l){
    if (!l)
        return NULL;

    List clone = newList();
    if (!clone)
        return NULL;

    struct node *p;
    for(p=l->head;p!=NULL;p=p->next){
        addListTail(clone,p->value);
    }

    return clone;

}
