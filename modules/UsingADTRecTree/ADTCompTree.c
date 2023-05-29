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


// Εισάγει στη τελευταία θέση του δέντρου tree ένα νέο υποδέντρο ώστε το tree να παραμείνει complete
CompTree comptree_insert_last(CompTree tree, Pointer value) {

    // Δημιουργούμε το νέο υποδέντρο με τιμή value
    RecTree new_child = rectree_create(value, NULL, NULL);
    RecTree new_parent_tree;

    // Βρίσκουμε την τελευταία θέση 
    int last = comptree_size(tree) - 1;
    if (comptree_size(tree) == 1 && comptree_value(tree) == NULL) return (CompTree) new_child;

    // Βρίσκουμε τον πρόγονο της τελευταίας θέσης 
    int parent = last/2;
    RecTree parent_tree = rectree_get_subtree((RecTree)tree, parent);

    // Τοποθετούμε το νέο υποδέντρο ως αριστερό ή δεξί παιδί του προγόνου αναλόγως την θέση του τελευταίου υποδέντρου
    if (last % 2 == 0) {
        new_parent_tree = rectree_create(rectree_value(parent_tree), new_child, NULL);
    }
    else {
        new_parent_tree = rectree_create(rectree_value(parent_tree), rectree_left(parent_tree), new_child);
    }

    // Αντικαθιστούμε τον νέο πρόγονο του υποδέντρου στη θέση του παλιού με απόγονο το υποδέντρο
    tree = (CompTree)rectree_replace_subtree((RecTree)tree, parent, new_parent_tree);

    // Επιστρέφουμε το δέντρο tree
    return tree;

}

// Αφαιρεί το τελευταίο υποδέντρο του tree
CompTree comptree_remove_last(CompTree tree) {
    // Αντικαθιστά το υποδέντρο με το κενό δέντρο και επιστρέφει το tree
    return (CompTree)rectree_replace_subtree((RecTree)tree, comptree_size(tree) - 1, REC_TREE_EMPTY);
}

// Επιστρέφει το υποδέντρο του tree στη θέση pos
CompTree comptree_get_subtree(CompTree tree, int pos) {
    return (CompTree) rectree_get_subtree((RecTree)tree, pos);
}

//Αντικαθιστά το υποδέντρο του tree στην θέση pos με το subtree
CompTree comptree_replace_subtree(CompTree tree, int pos, CompTree subtree) {
    return (CompTree) rectree_replace_subtree((RecTree)tree, pos, (RecTree)subtree);
}
