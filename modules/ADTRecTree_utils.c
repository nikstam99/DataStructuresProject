#include "ADTRecTree.h"
#include "ADTVector.h"
#include "ADTRecTree_utils.h"
#include <stdlib.h>
#include "ADTMap.h"

RecTree rectree_get_subtree(RecTree tree, int pos) {
    if (!pos) return tree;
    int parent = pos;
    RecTree subtree = tree;
    Vector path = vector_create(0, NULL);
    vector_insert_last(path, parent + (Pointer)0);
    while (parent) {
        if (!(parent % 2)) {
            parent = parent/2 - 1;
        }
        else {
            parent = parent/2;
        }
        if (parent)
        vector_insert_last(path, parent + (Pointer)0);
    }
    VectorNode node = vector_last(path);
    int value = vector_node_value(path, node) - (Pointer)0;
    while (value != pos) {
        if ((vector_node_value(path, node) - (Pointer)0) % 2) {
            subtree = rectree_left(subtree); 
        }
        else {
            subtree = rectree_right(subtree);
        }
        node = vector_previous(path, node);
        value = vector_node_value(path, node) - (Pointer)0;
    }
    if (value % 2) subtree = rectree_left(subtree);
    else subtree = rectree_right(subtree);
    vector_destroy(path);
    return subtree;
}
int compare_ints2(Pointer a, Pointer b) {
	return *(int*)a - *(int*)b;
}

RecTree rectree_replace_subtree(RecTree tree, int pos, RecTree subtree) {
    int parent = pos;
    RecTree tree_remove = rectree_get_subtree(tree, pos);
    Vector path = vector_create(0, NULL);
    Map subtrees = map_create((CompareFunc)compare_ints2, NULL, NULL);
    vector_insert_last(path, parent + (Pointer)0);
    while (parent) {
        if (!(parent % 2)) {
            parent = parent/2 - 1;
            map_insert(subtrees, parent + (Pointer)0, rectree_left(rectree_get_subtree(tree, parent)));
        }
        else {
            parent = parent/2;
            map_insert(subtrees, parent + (Pointer)0, rectree_right(rectree_get_subtree(tree, parent)));
        }
        vector_insert_last(path, parent + (Pointer)0);
    }
    Pointer tree_value = rectree_value(tree);
    RecTree sub = tree;
    RecTree help_tree;
    VectorNode node = vector_last(path);
    int value = vector_node_value(path, node) - (Pointer)0;
    while (value != pos) {
        if ((vector_node_value(path, node) - (Pointer)0) % 2 || !value) {
            help_tree = rectree_left(sub); 
            rectree_destroy(sub);
            sub = rectree_create(tree_value, help_tree, map_find(subtrees, value + (Pointer)0));
            tree_value = rectree_value(sub);
        }
        if ((vector_node_value(path, node) - (Pointer)0) % 2 == 0 || !value) {
            help_tree = rectree_right(sub);
            rectree_destroy(sub);
            sub = rectree_create(tree_value, map_find(subtrees, value + (Pointer)0), help_tree);
            tree_value = rectree_value(sub);
        }
        node = vector_previous(path, node);
        value = vector_node_value(path, node) - (Pointer)0;
    }
    if (value % 2) sub = rectree_left(sub);
    else sub = rectree_right(sub);
    rectree_destroy(tree);
}
