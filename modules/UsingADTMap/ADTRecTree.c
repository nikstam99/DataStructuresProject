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
	Pointer tree = count;
	if (!count) {
		map_val = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_Size = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_left = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_right = map_create((CompareFunc)compare_keys, NULL, NULL);
	}
	//int size_right = 0;
	//int size_left = 0;
	int s = 0;
	if (value != NULL) {
		count++;
		tree++;
		map_insert(map_val, tree, value);
		s = 1;
	}
	else map_insert(map_val, REC_TREE_EMPTY, REC_TREE_EMPTY);
	
	/*if (left != NULL) {
		map_insert(map_left, tree, left);
		size_left = map_find(map_Size, left) - (Pointer)0;
		s += size_left;
	}*/

	/*if (right != NULL) {
		map_insert(map_right, tree, right);
		size_right = map_find(map_Size, left) - (Pointer)0;
		s += size_right;
	}*/
	Pointer size = s + (Pointer)0;
	map_insert(map_Size, tree, size);
	return (RecTree)tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.
int rectree_size(RecTree tree) {
	if (tree != REC_TREE_EMPTY) {
		Pointer size = map_find(map_Size, tree);
		return size - (Pointer)0;
	}
	else return 0;
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.
void rectree_destroy(RecTree tree) {
	//if (tree != REC_TREE_EMPTY)
	//map_remove(map_val, tree);
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.
Pointer rectree_value(RecTree tree) {
	return map_find(map_val, REC_TREE_EMPTY);
}

RecTree rectree_left(RecTree tree) {
	return NULL;
}

RecTree rectree_right(RecTree tree) {
	return NULL;
}
