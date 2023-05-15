#include "acutest.h"			// Απλή βιβλιοθήκη για unit testing

#include "ADTRecTree.h"

// Επιστρέφει έναν ακέραιο σε νέα μνήμη με τιμή value
int* create_int(int value) {
	int* p = malloc(sizeof(int));
	*p = value;
	return p;
}

void test_create(void) {
    RecTree tree = rectree_create(NULL, NULL, NULL);
    TEST_ASSERT(tree != NULL);

	rectree_destroy(tree);
}

void test_size(void) {
	RecTree tree_empty = rectree_create(NULL, NULL, NULL);
	TEST_ASSERT(!rectree_size(tree_empty));
	rectree_destroy(tree_empty);

	Pointer value = create_int(100);
	RecTree tree1 = rectree_create(value, NULL, NULL);
	TEST_ASSERT(rectree_size(tree1) == 1);

	RecTree tree2 = rectree_create(value, NULL, NULL);

	RecTree tree = rectree_create(value, tree1, tree2);

	TEST_ASSERT(rectree_size(tree) == 3);

	rectree_destroy(tree);
	rectree_destroy(tree1);
	rectree_destroy(tree2);
	free(value);
}

void test_value(void) {
	Pointer value = create_int(100);
	RecTree tree = rectree_create(value, NULL, NULL);
	TEST_ASSERT(*(int*)rectree_value(tree) == 100);
	rectree_destroy(tree);
	free(value);
}

void test_right_and_left(void) {
	RecTree tree_left = rectree_create(NULL, NULL, NULL);
	RecTree tree_right = rectree_create(NULL, NULL, NULL);
	RecTree tree = rectree_create(NULL, tree_left, tree_right);
	
	TEST_ASSERT(rectree_left(tree) == tree_left);
	TEST_ASSERT(rectree_right(tree) == tree_right);

	rectree_destroy(tree);
	rectree_destroy(tree_left);
	rectree_destroy(tree_right);
	
}	










// Λίστα με όλα τα tests προς εκτέλεση
TEST_LIST = {
	{ "rectree_create", test_create },
	{ "rectree_size", test_size },
	{ "rectree_value", test_value},
	{ "rectree_left_and_right", test_right_and_left},
	{ NULL, NULL } // τερματίζουμε τη λίστα με NULL
};