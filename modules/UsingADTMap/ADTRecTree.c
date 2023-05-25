///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω maps
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"
#include "ADTMap.h"

// Counter που μετράει το σύνολο των δέντρων που έχουν δημιουργηθεί
Pointer count = (Pointer)0;

// Global maps στα οποία αναθέτουμε το περιεχόμενο και το μέγεθος ενός δέντρου,
// καθώς και το δεξί και το αριστερό υποδέντρο του (αν υπάρχουν)
Map map_val;
Map map_Size;
Map map_left;
Map map_right;


int compare_keys(Pointer a, Pointer b) {
	return a - b;
}



RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
	// Το δέντρο παίρνει την τιμή του global counter
	Pointer tree = count;

	// Στην πρώτη φορά που καλείται η create δημιουργούμε τα global maps
	if (count == (Pointer)0) {
		map_val = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_Size = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_left = map_create((CompareFunc)compare_keys, NULL, NULL);
		map_right = map_create((CompareFunc)compare_keys, NULL, NULL);
	}
	int size_right = 0;
	int size_left = 0;
	int s = 0;
	if (value != NULL) {
		count++;
		tree++;

		// Αν το δέντρο δεν είναι κενό αυξάνουμε τον counter και τοποθετούμε το 
		// value στο κατάλληλο map
		map_insert(map_val, tree, value);
		s = 1;
	}
	// Αν το δέντρο είναι κενό τοποθετούμε το 0 στο map
	else map_insert(map_val, REC_TREE_EMPTY, REC_TREE_EMPTY);
	
	//Αν το αριστερό υποδέντρο δεν είναι NULL το τοποθετούμε στο map_left
	// και αυξάνουμε το size του δέντρου
	if (left != NULL) {
		map_insert(map_left, tree, left);
		size_left = map_find(map_Size, left) - (Pointer)0;
		s += size_left;
	}

	//Αν το δεξί υποδέντρο δεν είναι NULL το τοποθετούμε στο map_right
	// και αυξάνουμε το size του δέντρου
	if (right != NULL) {
		map_insert(map_right, tree, right);
		size_right = map_find(map_Size, left) - (Pointer)0;
		s += size_right;
	}
	// Κάνουμε cast το size σε pointer γιατί το map δέχεται pointers 
	// και το τοποθετούμε στο map_size
	Pointer size = s + (Pointer)0;
	map_insert(map_Size, tree, size);

	// Επιστρέφουμε το casted σε RecTree δέντρο
	return (RecTree)tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.
int rectree_size(RecTree tree) {

	// Αν το δέντρο δεν είναι κενό, το βρίσκουμε στο map_size και επιστρέφουμε το size του
	if (tree != REC_TREE_EMPTY) {
		Pointer size = map_find(map_Size, tree);
		return size - (Pointer)0;
	}
	else return 0;
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.
void rectree_destroy(RecTree tree) {

	// Αφαιρούμε το δέντρο που θέλουμε να καταστρέψουμε απο τα maps
	if (map_size(map_val)) {
		map_remove(map_Size, tree);
		map_remove(map_val, tree);
		map_remove(map_left, tree);
		map_remove(map_right, tree);
	}
	// Αν το map_size είναι άδειο καταστρέφουμε τα maps
	if (!map_size(map_val)){
		map_destroy(map_Size);
		map_destroy(map_val);
		map_destroy(map_left);
		map_destroy(map_right);

		// Επαναφέρουμε τον pointer σε 0
		count = (Pointer)0;
	}
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree
// ψάχνοντας το δέντρο στα κατάλληλα maps
Pointer rectree_value(RecTree tree) {
	return map_find(map_val, tree);
}

RecTree rectree_left(RecTree tree) {
	return map_find(map_left, tree);
}

RecTree rectree_right(RecTree tree) {
	return map_find(map_right, tree);
}
