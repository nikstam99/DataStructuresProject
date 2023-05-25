///////////////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT CompTree μέσω RecTree
//
///////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include "ADTRecTree.h"
#include "ADTCompTree.h"
#include "ADTRecTree_utils.h"


//  Ένα δέντρο είναι pointer σε αυτό το struct
struct comp_tree {
	Pointer value;
	RecTree left;
	RecTree right; 
	int size;
};

// Δημιουργεί και επιστρέφει ένα νέο δέντρο, με τιμή (στη ρίζα) value και υποδέντρα left και right.

CompTree comptree_create(Pointer value, CompTree left, CompTree right) {
    RecTree tree = rectree_create(value, (RecTree)left, (RecTree)right);
    return (CompTree)tree;
}

// Επιστρέφει τον αριθμό στοιχείων που περιέχει το δέντρο (0 για κενά δέντρα).

int comptree_size(CompTree tree) {
    return rectree_size((RecTree)tree);
}

// Ελευθερώνει όλη τη μνήμη που δεσμεύει το δέντρο tree.

void comptree_destroy(CompTree tree) {
	rectree_destroy((RecTree)tree);
}

// Επιστρέφουν την τιμή (στη ρίζα), το αριστερό και το δεξί υποδέντρο του δέντρου tree.

Pointer comptree_value(CompTree tree) {
	return rectree_value((RecTree)tree);
}

CompTree comptree_left(CompTree tree) {
	return (CompTree)rectree_left((RecTree)tree);
}

CompTree comptree_right(CompTree tree) {
	return (CompTree)rectree_right((RecTree)tree);
}

CompTree comptree_insert_last(CompTree tree, Pointer value) {
    RecTree new_child = rectree_create(value, NULL, NULL);
    RecTree new_parent_tree;
    int last = comptree_size(tree) - 1;
    int parent = last/2;
    RecTree parent_tree = rectree_get_subtree((RecTree)tree, parent);
    if (last % 2 == 0) {
        new_parent_tree = rectree_create(rectree_value(parent_tree), new_child, NULL);
    }
    else {
        new_parent_tree = rectree_create(rectree_value(parent_tree), rectree_left(parent_tree), new_child);
    }
    tree = (CompTree)rectree_replace_subtree((RecTree)tree, parent, new_parent_tree);
    return tree;

}

CompTree comptree_remove_last(CompTree tree) {
    tree = (CompTree)rectree_replace_subtree((RecTree)tree, comptree_size(tree) - 1, REC_TREE_EMPTY);
    return tree;
}