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

RecTree rectree_replace_subtree(RecTree tree, int pos, RecTree subtree) {
    RecTree help_tree;
    RecTree new_tree;
    RecTree old_tree;
    int parent = pos;
    Pointer value;
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
    rectree_destroy(help_tree);

    while(parent) {
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
    return new_tree;
}
