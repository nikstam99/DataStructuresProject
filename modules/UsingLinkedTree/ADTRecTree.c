///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT RecTree μέσω links
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"


// Προς υλοποίηση...


//  Ένα δέντρο είναι pointer σε αυτό το struct
struct rec_tree {
	Pointer value;
	RecTree left;
	RecTree right; 
	int size;
};


// Δημιουργεί και επιστρέφει ένα νέο δέντρο, με τιμή (στη ρίζα) value και υποδέντρα left και right.

RecTree rectree_create(Pointer value, RecTree left, RecTree right) {
	// Δέσμευση μνήμης για το δέντρο
	RecTree tree = malloc (sizeof (*tree)); 

	// Ανάθεση του value
	tree->value = value;
	// Αρχικοποίηση του size σε 1
	tree->size = 1;
	if (left != NULL) {
	tree->left = left;
	// Προσθέτουμε στο size το size του αριστερού υποδέντρου
	tree->size += left->size;
	}
	else tree->left = NULL;
	if (right != NULL) {
	// Προσθέτουμε στο size το size του δεξιού υποδέντρου
	tree->right = right;
	tree->size += right->size;
	}
	else tree->right = NULL;
	return tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο.

int rectree_size(RecTree tree) {
	return tree->size;
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.

void rectree_destroy(RecTree tree) {
	free(tree);
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.

Pointer rectree_value(RecTree tree) {
	return tree->value;
}

RecTree rectree_left(RecTree tree) {
	return tree->left;
}

RecTree rectree_right(RecTree tree) {
	return tree->right;
}

