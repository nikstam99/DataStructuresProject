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
struct rec_tree {
	Pointer value;
	RecTree left;
	RecTree right; 
	int size;
};

RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
	if (!count) {
		map_val = map_create(compare_ints, NULL, NULL);
		map_Size = map_create(compare_ints, NULL, NULL);
		map_left = map_create(compare_ints, NULL, NULL);
		map_right = map_create(compare_ints, NULL, NULL);
	}
	int size = 0;
	if (value != NULL) {
		count++;
		map_insert(map_val, count, value);
		size++;
	}
	
	
	if (left != NULL) {
		map_insert(map_left, count, left);
		size += rectree_size(left);
	}

	if (right != NULL) {
		map_insert(map_right, count, right);
		size += rectree_size(right);
	}

	Pointer S = create_int(size);
	map_insert(map_Size, count, S);
	RecTree tree = count;
	return tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.
int rectree_size(RecTree tree) {
	Pointer size = map_find(map_Size, tree);
	return *(int*)size;
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
