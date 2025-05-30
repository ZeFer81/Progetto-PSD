#include "item-attivita_di_studio.h"

void swap(Item *a, Item *b)
{
  Item temp = *b;
  *b = *a;
  *a = temp;
}
