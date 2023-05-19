///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω maps
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"
#include "ADTMap.h"

Pointer count = (Pointer)0;
Map map_val;
Map map_Size;
Map map_left;
Map map_right;


int compare_keys(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}



RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
    int Counter = count - (Pointer)0;
   if (count == (Pointer)0) {
        map_val = map_create((CompareFunc)compare_keys, NULL, NULL);
   }
    Counter++;
    count = Counter + (Pointer)0;
   map_insert(map_val, count, value);
   return (RecTree)count;
}
// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.
int rectree_size(RecTree tree) {
	 return 0;
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.
void rectree_destroy(RecTree tree) {
   map_remove(map_val, tree);
}

Pointer rectree_value(RecTree tree) {
    return NULL;
}

RecTree rectree_left(RecTree tree) {
	return NULL;
}

RecTree rectree_right(RecTree tree) {
	return NULL;
}