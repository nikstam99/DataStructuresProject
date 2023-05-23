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

    RecTree tree2 = rectree_create(value, NULL, NULL);
    
    RecTree tree3 = rectree_create(value, tree1, tree2);
    
    RecTree tree4 = rectree_create(value, tree3, NULL);
    
    RecTree tree5 = rectree_create(value, NULL, NULL);
    
    RecTree tree6 = rectree_create(value, tree5, tree4);

   TEST_ASSERT(rectree_get_subtree(tree6, 5) == tree3);
   TEST_ASSERT(rectree_get_subtree(tree6, 0) == tree6);
   TEST_ASSERT(rectree_get_subtree(tree6, 2) == tree4);
   TEST_ASSERT(rectree_get_subtree(tree6, 1) == tree5);

   rectree_destroy(tree1);
   rectree_destroy(tree2);
   rectree_destroy(tree3);
   rectree_destroy(tree4);
   rectree_destroy(tree5);
   rectree_destroy(tree6);
   free(value);
}

void test_rectree_replace_subtree(void) {
    Pointer value = create_int2(1);
    Pointer value2 = create_int2(2);
    Pointer value3 = create_int2(3);
    Pointer value4 = create_int2(4);

    RecTree tree1 = rectree_create(value, NULL, NULL);

    RecTree tree2 = rectree_create(value, NULL, NULL);
    
    RecTree tree3 = rectree_create(value, tree1, tree2);
    
    RecTree tree4 = rectree_create(value2, tree3, NULL);
    
    RecTree tree5 = rectree_create(value3, NULL, NULL);
    
    RecTree tree6 = rectree_create(value4, tree5, tree4);

    RecTree rep = rectree_create(value, NULL, NULL);

    tree6 = rectree_replace_subtree(tree6, 5, rep);

    TEST_ASSERT(rectree_get_subtree(tree6, 5) == rep);
    TEST_ASSERT(rectree_get_subtree(tree6, 0) == tree6);
    TEST_ASSERT(rectree_value(rectree_get_subtree(tree6, 2)) == rectree_value(tree4));
    TEST_ASSERT(rectree_get_subtree(tree6, 1) == tree5);

}

// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{"rectree_get_subtree", test_rectree_get_subtree},
    {"rectree_replace_subtree", test_rectree_replace_subtree},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};