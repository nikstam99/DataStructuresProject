///////////////////////////////////////////////////////////
//
// Υλοποίηση του ADT Priority Queue μέσω σωρού.
//
///////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "ADTPriorityQueue.h"
#include "ADTVector.h"			// Η υλοποίηση του PriorityQueue χρησιμοποιεί Vector
#include "ADTCompTree.h"
#include "ADTRecTree.h"
#include "ADTRecTree_utils.h"

// Ενα PriorityQueue είναι pointer σε αυτό το struct
struct priority_queue {
	CompTree tree;				// Τα δεδομένα αποθηκευμένα σε δέντρο
	CompareFunc compare;		// Η διάταξη
	DestroyFunc destroy_value;	// Συνάρτηση που καταστρέφει ένα στοιχείο του vector.
};


// Βοηθητικές συναρτήσεις ////////////////////////////////////////////////////////////////////////////

// Προσοχή: στην αναπαράσταση ενός complete binary tree με πίνακα, είναι βολικό τα ids των κόμβων να
// ξεκινάνε από το 1 (ρίζα), το οποίο απλοποιεί τις φόρμουλες για εύρεση πατέρα/παιδιών. Οι θέσεις
// ενός vector όμως ξεκινάνε από το 0. Θα μπορούσαμε απλά να αφήσουμε μία θέση κενή, αλλά δεν είναι ανάγκη,
// μπορούμε απλά να αφαιρούμε 1 όταν διαβάζουμε/γράφουμε στο vector. Για απλοποίηση του κώδικα, η
// πρόσβαση στα στοιχεία του vector γίνεται από τις παρακάτω 2 βοηθητικές συναρτήσεις.

// Επιστρέφει την τιμή του κόμβου node_id

static Pointer node_value(PriorityQueue pqueue, int node_id) {
	// τα node_ids είναι 1-based, το node_id αποθηκεύεται στη θέση node_id - 1
	return comptree_value(comptree_get_subtree(pqueue->tree, node_id - 1));
}

// Ανταλλάσει τις τιμές των κόμβων node_id1 και node_id2

static void node_swap(PriorityQueue pqueue, int node_id1, int node_id2) {
	// τα node_ids είναι 1-based, το node_id αποθηκεύεται στη θέση node_id - 1
	Pointer value1 = node_value(pqueue, node_id1);
	Pointer value2 = node_value(pqueue, node_id2);
	CompTree help_tree = comptree_get_subtree(pqueue->tree, node_id1 - 1);
	CompTree tree_left = comptree_left(help_tree);
	CompTree tree_right = comptree_right(help_tree);
	CompTree new;
	if (comptree_value(tree_left) == value2) {
		new = comptree_create(value1, comptree_left(tree_left), comptree_right(tree_left));
		help_tree = comptree_create(value2, new, tree_right);
		pqueue->tree = comptree_replace_subtree(pqueue->tree, node_id1 - 1, help_tree);
	}
	else if (comptree_value(tree_right) == value2) {
		new = comptree_create(value1, comptree_left(tree_right), comptree_right(tree_right));
		help_tree = comptree_create(value2, tree_left, new);
		pqueue->tree = comptree_replace_subtree(pqueue->tree, node_id1 - 1, help_tree);
	}
	else if (node_id1 == 1 && node_id2 == comptree_size(pqueue->tree)) {
		help_tree = comptree_create(value1, NULL, NULL);
		pqueue->tree = comptree_replace_subtree(pqueue->tree, node_id2 - 1, help_tree);
		tree_left = comptree_left(pqueue->tree);
		tree_right = comptree_right(pqueue->tree);
		CompTree tree = comptree_create(value2, tree_left, tree_right);
		pqueue->tree = tree;
	}
	
}

		
	

	




// Αποκαθιστά την ιδιότητα του σωρού.
// Πριν: όλοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού, εκτός από
//       τον node_id που μπορεί να είναι _μεγαλύτερος_ από τον πατέρα του.
// Μετά: όλοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού.

static void bubble_up(PriorityQueue pqueue, int node_id) {
	// Αν φτάσαμε στη ρίζα, σταματάμε
	if (node_id == 1)
		return;

	int parent = node_id / 2;		// Ο πατέρας του κόμβου. Τα node_ids είναι 1-based

	// Αν ο πατέρας έχει μικρότερη τιμή από τον κόμβο, swap και συνεχίζουμε αναδρομικά προς τα πάνω
	if (pqueue->compare(node_value(pqueue, parent), node_value(pqueue, node_id)) < 0) {
		node_swap(pqueue, parent, node_id);
		bubble_up(pqueue, parent);
	}
}

// Αποκαθιστά την ιδιότητα του σωρού.
// Πριν: όλοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού, εκτός από τον
//       node_id που μπορεί να είναι _μικρότερος_ από κάποιο από τα παιδιά του.
// Μετά: όλοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού.

static void bubble_down(PriorityQueue pqueue, int node_id) {
	// βρίσκουμε τα παιδιά του κόμβου (αν δεν υπάρχουν σταματάμε)
	int left_child = 2 * node_id;
	int right_child = left_child + 1;

	int size = pqueue_size(pqueue);
	if (left_child > size)
		return;

	// βρίσκουμε το μέγιστο από τα 2 παιδιά
	int max_child = left_child;
	if (right_child <= size && pqueue->compare(node_value(pqueue, left_child), node_value(pqueue, right_child)) < 0)
			max_child = right_child;

	// Αν ο κόμβος είναι μικρότερος από το μέγιστο παιδί, swap και συνεχίζουμε προς τα κάτω
	if (pqueue->compare(node_value(pqueue, node_id), node_value(pqueue, max_child)) < 0) {
		node_swap(pqueue, node_id, max_child);
		bubble_down(pqueue, max_child);
	}
}

static void efficient_heapify(PriorityQueue pqueue, Vector values) {
	int size = vector_size(values);
	for (int i = 0; i < size; i++) {
		pqueue_insert(pqueue, vector_get_at(values, i));
	}
	for (int node = size/2; node == 1; node--) {
		bubble_down(pqueue, node);
	}
}


// Συναρτήσεις του ADTPriorityQueue //////////////////////////////////////////////////

PriorityQueue pqueue_create(CompareFunc compare, DestroyFunc destroy_value, Vector values) {
	assert(compare != NULL);	// LCOV_EXCL_LINE

	PriorityQueue pqueue = malloc(sizeof(*pqueue));
	pqueue->compare = compare;
	pqueue->destroy_value = destroy_value;

	// Δημιουργία του vector που αποθηκεύει τα στοιχεία.
	// ΠΡΟΣΟΧΗ: ΔΕΝ περνάμε την destroy_value στο vector!
	// Αν την περάσουμε θα καλείται όταν κάνουμε swap 2 στοιχεία, το οποίο δεν το επιθυμούμε.
	pqueue->tree = comptree_create(NULL, NULL, NULL);

	// Αν values != NULL, αρχικοποιούμε το σωρό.
	if (values != NULL)
		efficient_heapify(pqueue, values);

	return pqueue;
}

int pqueue_size(PriorityQueue pqueue) {
	if (comptree_value(pqueue->tree) != NULL || comptree_size(pqueue->tree) > 1)
		return comptree_size(pqueue->tree);
	else return 0;
}

Pointer pqueue_max(PriorityQueue pqueue) {
	return node_value(pqueue, 1);		// root
}

void pqueue_insert(PriorityQueue pqueue, Pointer value) {
	// Προσθέτουμε την τιμή στο τέλος το σωρού
	pqueue->tree = comptree_insert_last(pqueue->tree, value);

 	// Ολοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού εκτός από τον τελευταίο, που μπορεί να είναι
	// μεγαλύτερος από τον πατέρα του. Αρα μπορούμε να επαναφέρουμε την ιδιότητα του σωρού καλώντας
	// τη bubble_up γα τον τελευταίο κόμβο (του οποίου το 1-based id ισούται με το νέο μέγεθος του σωρού).
	bubble_up(pqueue, pqueue_size(pqueue));
}

void pqueue_remove_max(PriorityQueue pqueue) {
	int last_node = pqueue_size(pqueue);
	assert(last_node != 0);		// LCOV_EXCL_LINE

	// Destroy την τιμή που αφαιρείται
	if (pqueue->destroy_value != NULL)
		pqueue->destroy_value(pqueue_max(pqueue));

	if (pqueue_size(pqueue) > 1) {
		// Αντικαθιστούμε τον πρώτο κόμβο με τον τελευταίο και αφαιρούμε τον τελευταίο
		node_swap(pqueue, 1, last_node);
	
		pqueue->tree = comptree_remove_last(pqueue->tree);

 		// Ολοι οι κόμβοι ικανοποιούν την ιδιότητα του σωρού εκτός από τη νέα ρίζα
 		// που μπορεί να είναι μικρότερη από κάποιο παιδί της. Αρα μπορούμε να
 		// επαναφέρουμε την ιδιότητα του σωρού καλώντας τη bubble_down για τη ρίζα.
		bubble_down(pqueue, 1);
	}
	else {
		pqueue->tree = comptree_replace_subtree(pqueue->tree, 0, NULL);
	}
	
}

DestroyFunc pqueue_set_destroy_value(PriorityQueue pqueue, DestroyFunc destroy_value) {
	DestroyFunc old = pqueue->destroy_value;
	pqueue->destroy_value = destroy_value;
	return old;
}

void pqueue_destroy(PriorityQueue pqueue) {
	// Αντί να κάνουμε εμείς destroy τα στοιχεία, είναι απλούστερο να
	// προσθέσουμε τη destroy_value στο vector ώστε να κληθεί κατά το vector_destroy.
	comptree_destroy(pqueue->tree);
	free(pqueue);
}