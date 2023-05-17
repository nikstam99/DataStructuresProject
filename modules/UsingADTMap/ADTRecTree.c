///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω maps
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"
#include "ADTMap.h"

RecTree count;
Map map_val, map_Size, map_left, map_right;


int compare_ints(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

//  Ένα δέντρο είναι pointer σε αυτό το struct
struct rec_tree {
	Pointer value;
	RecTree left;
	RecTree right; 
	int size;
};

RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
	Pointer c = count;
	if (!count) {
		map_val = map_create(compare_ints, NULL, NULL);
		map_Size = map_create(compare_ints, NULL, NULL);
		map_left = map_create(compare_ints, NULL, NULL);
		map_right = map_create(compare_ints, NULL, NULL);
	}
	if (value != NULL) {
		map_insert(map_val, c, value);
		count++;
	}
	if (left != NULL) {
		map_insert(map_left, c, left);
		count++;
	}
	if (right != NULL) {
		map_insert(map_right, c, right);
		count++;
	}
	if (value == NULL) return 0;
	else return c;
}

int rectree_size(RecTree tree) {
	
}