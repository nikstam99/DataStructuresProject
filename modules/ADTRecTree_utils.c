#include "ADTRecTree.h"
#include "ADTVector.h"
#include "ADTRecTree_utils.h"
#include <stdlib.h>
#include "ADTMap.h"

// Επιστρέφει το υποδέντρο στην θέση pos του δέντρου tree
RecTree rectree_get_subtree(RecTree tree, int pos) {

    // Αν το pos είναι μηδέν επιστρέφουμε το ίδιο το δέντρο
    if (!pos) return tree;

    // Στον ακέραιο parent αποθηκεύουμε τη θέση του υποδέντρου
    int parent = pos;
    RecTree subtree = tree;

    // Δημιουργούμε ένα vector στο οποίο αποθηκεύουμε τη θέση κάθε υποδέντρου του path προς το pos
    Vector path = vector_create(0, NULL);

    // Εισάγουμε στο vector το pos
    vector_insert_last(path, parent + (Pointer)0);

    // Όσο το parent δεν είναι 0 ακολουθούμε το path από το pos προς την ρίζα
    while (parent) {

        // Ελέγχουμε αν το parent είναι περιττό ή άρτιο ώστε να καταλάβουμε αν είναι
        // δεξί ή αριστερό υποδέντρο
        if (!(parent % 2)) {
            parent = parent/2 - 1;
        }
        else {
            parent = parent/2;
        }

        // Αν το parent δεν είναι 0 το εισάγουμε στο vector
        if (parent)
        vector_insert_last(path, parent + (Pointer)0);
    }

    // Κάνουμε προσπέλαση το vector από το τέλος προς την αρχή
    VectorNode node = vector_last(path); 
    int value = vector_node_value(path, node) - (Pointer)0;

    // Όσο το value που περιέχει το vector δεν είναι pos κατεβαίνουμε προς το pos
    while (value != pos) {

        // Αν το value είναι περιττό παίρνουμε το αριστερό υποδέντρο
        if ((vector_node_value(path, node) - (Pointer)0) % 2) {
            subtree = rectree_left(subtree); 
        }

        // Αν το value είναι άρτιο παίρνουμε το δεξί υποδέντρο
        else {
            subtree = rectree_right(subtree);
        }
        node = vector_previous(path, node);
        value = vector_node_value(path, node) - (Pointer)0;
    }

    // Όταν το value γίνει pos ελέγχουμε αν το υποδέντρο στην θέση pos είναι δεξί ή αριστερό
    if (value % 2) subtree = rectree_left(subtree);
    else subtree = rectree_right(subtree);

    // Κατασρτέφουμε το vector path
    vector_destroy(path);

    // Επιστρέφουμε το υποδέντρο στη θέση pos
    return subtree;
}

// Αντικαθιστά το υποδέντρο στην θέση pos του δέντρου tree με το υποδέντρο subtree
RecTree rectree_replace_subtree(RecTree tree, int pos, RecTree subtree) {
    RecTree help_tree;

    // Αν το pos είναι 0 αντικαθιστά όλο το δέντρο
    if (!pos) {
        rectree_destroy(tree);
        return subtree;
    }
    RecTree new_tree;
    RecTree old_tree;
    // Περιέχει την θέση του υποδέντρου 
    int parent = pos;
    Pointer value;

    // Βρίσκουμε το υποδέντρο στην θέση pos 
    help_tree = rectree_get_subtree(tree, parent);
    
    // Βρίσκουμε απο το υποδέντρο που θέλουμε να αντικαταστήσουμε είναι αριστερό η δεξί
    // και δημιουργούμε τον πρόγονό του από την αρχή με υποδέντρο το subtree
    if (parent % 2 == 0) {
        parent = parent/2 - 1;
        help_tree = rectree_get_subtree(tree, parent);
        value = rectree_value(help_tree);
        new_tree = rectree_create(value, rectree_left(help_tree), subtree);
        rectree_destroy(rectree_right(help_tree));
    }
    else {
        parent = parent/2;
        help_tree = rectree_get_subtree(tree, parent);
        value = rectree_value(help_tree);
        new_tree = rectree_create(value, subtree, rectree_right(help_tree));
        rectree_destroy(rectree_left(help_tree));
    }

    // Καταστρέφουμε τον παλιό πρόγονο
    rectree_destroy(help_tree);
    
    // Όσο η θέση δεν είναι 0 κάνουμε προσπέλαση το path προς την ρίζα
    while(parent) {

        // Βρίσκουμε αν ο πρόγονος είναι αριστερό η δεξί υποδέντρο, δημιουργούμε έναν καινούριο
        // με απόγονο το new_tree και καταστρέφουμε το προηγούμενο υποδέντρο
        if (parent % 2 == 0) {
            parent = parent/2 - 1;
            help_tree = rectree_get_subtree(tree, parent);
            value = rectree_value(help_tree);
            old_tree = new_tree;
            new_tree = rectree_create(value, rectree_left(help_tree), old_tree);
            rectree_destroy(help_tree);
        }
        else {
            parent = parent/2;
            help_tree = rectree_get_subtree(tree, parent);
            value = rectree_value(help_tree);
            old_tree = new_tree;
            new_tree = rectree_create(value, old_tree, rectree_right(help_tree));
            rectree_destroy(help_tree);
        }
    }

    // Επιστρέφουμε το νέο δέντρο με το subtree στη θέση pos και τα υπόλοιπα υποδέντρα ίδια
    return new_tree;
}
