///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω maps
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"
#include "ADTMap.h"

Pointer count = 0;
Map map_val, map_Size, map_left, map_right;


int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

int* create_int(int value); /* {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}*/

//  Ένα δέντρο είναι pointer σε αυτό το struct


RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
	Pointer tree = count;
	if (!count) {
		map_val = map_create(compare_ints, NULL, NULL);
		map_Size = map_create(compare_ints, NULL, NULL);
		map_left = map_create(compare_ints, NULL, NULL);
		map_right = map_create(compare_ints, NULL, NULL);
	}
	int size_right = 0;
	int size_left = 0;
	int s = 0;
	if (value != NULL) {
		count++;
		tree++;
		map_insert(map_val, tree, value);
		s = 1;
	}
	else map_insert(map_val, (Pointer)0, REC_TREE_EMPTY);
	
	
	if (left != NULL) {
		map_insert(map_left, tree, left);
		size_left = map_find(map_Size, left) - (Pointer)0;
	}

	if (right != NULL) {
		map_insert(map_right, tree, right);
		size_right = map_find(map_Size, left) - (Pointer)0;
	}
	s = s + size_right + size_left;
	Pointer size = s + (Pointer)0;
	map_insert(map_Size, tree, size);
	return tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.
int rectree_size(RecTree tree) {
	Pointer size = map_find(map_Size, tree);
	return size - (Pointer)0;
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.
void rectree_destroy(RecTree tree) {
	free(tree);
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.
Pointer rectree_value(RecTree tree) {
	return map_find(map_val, tree);
}

RecTree rectree_left(RecTree tree) {
	return map_find(map_left, tree);
}

RecTree rectree_right(RecTree tree) {
	return map_find(map_right, tree);
}
