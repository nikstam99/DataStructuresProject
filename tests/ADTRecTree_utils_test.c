#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing
#include "ADTRecTree_utils.h"
#include "ADTRecTree.h"

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int2(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

void test_rectree_get_subtree(void) {
    Pointer value = create_int2(1);
    RecTree tree1 = rectree_create(value, NULL, NULL);
    value++;
    RecTree tree2 = rectree_create(value, NULL, NULL);
    value++;
    RecTree tree3 = rectree_create(value, tree1, tree2);
    value++;
    RecTree tree4 = rectree_create(value, tree3, NULL);
    value++;
    RecTree tree5 = rectree_create(value, NULL, NULL);
    value++;
    RecTree tree6 = rectree_create(value, tree5, tree4);

   TEST_ASSERT(rectree_get_subtree(tree6, 5) == tree3);
   TEST_ASSERT(rectree_get_subtree(tree6, 0) == tree6);
   TEST_ASSERT(rectree_get_subtree(tree6, 2) == tree4);
   TEST_ASSERT(rectree_get_subtree(tree6, 1) == tree5);
}








// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{"rectree_get_subtree", test_rectree_get_subtree},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};