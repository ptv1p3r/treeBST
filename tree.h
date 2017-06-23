#include <stdlib.h>
#include <stdio.h>
#include "treeType.h"
#include <math.h>

#ifndef _TREE_TYPE
typedef struct t_node *TREE;
// macros for the heap array
#define PARENT(i)  floor( i / 2)
#define LEFT(i)   2 * i
#define RIGHT(i)  2 * i + 1

#endif


// generic functions
TREE create_node(ITEM item);
TREE create_tree_from_array(int * array, int n, int i); // create a tree from a heap array
void insert_left(TREE parent, TREE son);
void insert_right(TREE parent, TREE son);
void insert(TREE parent, TREE left, TREE right);
TREE get_left(TREE parent);
TREE get_right(TREE parent);
int get_tree_height(TREE tree);
ITEM get_item(TREE tree);

void search_and_delete_node(TREE * root, int key);
void mirror_tree(TREE *root);

// traversing functions
void print_tree_pre_order(TREE tree);
void print_tree_in_order(TREE tree);
void print_tree_post_order(TREE tree);


void delete_node(TREE * node);


// BST functions

TREE get_min_BST(TREE root);
TREE search_BST(int item_to_find, TREE root);
void insert_BST(TREE node_to_insert, TREE *root);
void remove_node_BST(TREE * root);
void search_remove_node_BST(int item_to_find, TREE * root);

void TREEzigE(TREE *root);

