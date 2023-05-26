#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTRecTree.h"
#include "ADTCompTree.h"
#include "ADTRecTree_utils.h"

int* create_int3(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

// Ελέγχει τη σωστή λειτουργία της comptree_insert_last
void test_insert_last(void) {

    RecTree tree1 = rectree_create(NULL, NULL, NULL);
    RecTree tree2 = rectree_create(NULL, NULL, NULL);
    RecTree tree3 = rectree_create(NULL, tree1, tree2);
    RecTree tree4 = rectree_create(NULL, NULL, NULL);
    CompTree tree5 = comptree_create(NULL, (CompTree)tree3, (CompTree)tree4);

    Pointer value = create_int3(1);
    TEST_ASSERT((CompTree)rectree_get_subtree((RecTree)tree5, 5) == NULL);

    tree5 = comptree_insert_last(tree5, value);
    RecTree new_tree = rectree_get_subtree((RecTree)tree5, 5);

    TEST_ASSERT(rectree_value(new_tree) == value);

      
   
    rectree_destroy(tree1);
    rectree_destroy(tree2);
    rectree_destroy(tree3);
    comptree_destroy(comptree_right(tree5));
    comptree_destroy(tree5);
    rectree_destroy(new_tree);
    free(value);
}

// Ελέγχει τη σωστή λειτουργία της comptree_remove_last
void test_remove_last(void) {
    RecTree tree1 = rectree_create(NULL, NULL, NULL);
    RecTree tree2 = rectree_create(NULL, NULL, NULL);
    RecTree tree3 = rectree_create(NULL, tree1, tree2);
    RecTree tree4 = rectree_create(NULL, NULL, NULL);
    CompTree tree5 = comptree_create(NULL, (CompTree)tree3, (CompTree)tree4);

    tree5 = comptree_remove_last(tree5);
    comptree_destroy(comptree_left(tree5));
    comptree_destroy(tree5);
    rectree_destroy(tree1);
    rectree_destroy(tree4);
}



// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "comptree_insert_last", test_insert_last },
	{ "comptree_remove_last", test_remove_last },
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};