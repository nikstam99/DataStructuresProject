#pragma once // #include το πολύ μία φορά
#include "common_types.h"



// Επιστρέφει το υποδέντρο του tree στη θέση pos. Η αρίθμηση των θέσεων ξεκινάει
// από το 0 (ρίζα) και κινείται κατά επίπεδα, τα παιδιά της ρίζας έχουν θέση 1
// και 2, τα δικά τους παιδιά έχουν θέσεις 3,4,5,6, κλπ. Αν το υποδέντρο δεν
// υπάρχει θα επιστρέφεται REC_TREE_EMPTY. 

RecTree rectree_get_subtree(RecTree tree, int pos);

// Δημιουργεί και επιστρέφει ένα νέο δέντρο, το οποίο προκύπτει αντικαθιστώντας
// το υποδέντρο του tree στη θέση pos με το subtree που δίνεται.  Η θέση pos
// πρέπει να αντιστοιχεί είτε σε υπάρχον κόμβο (που αντικαθίσταται), είτε στο
// κενό παιδί ενός υπάρχοντος κόμβου (οπότε προστίθεται εκεί το subtree).  Αν το
// subtree τοποθετείται στη ρίζα (pos == 0) τότε επιστρέφεται το ίδιο το subtree.
//
// Η συνάρτηση καταστρέφει αυτόματα τόσο το παλιό υποδέντρο που αντικαθίσταται
// (αν υπάρχει), καθώς και όλους τους προγόνους του που μεταβάλλονται (οπότε
// ξαναδημιουργούνται).

RecTree rectree_replace_subtree(RecTree tree, int pos, RecTree subtree);