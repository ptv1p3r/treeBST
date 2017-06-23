
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

struct t_node
{
	TREE left;
	TREE right;
	ITEM item;
};


TREE create_node(ITEM item)
{
	TREE node = (TREE)malloc(sizeof(TREE));
	if (!node) {
		fprintf(stdout, "Memmory allocation error!\n");
		exit(1);
	}

	node-> left = NULL;
	node-> right = NULL;
	node-> item = item;

	return node;
}



TREE create_tree_from_array(int * array, int n, int i) // create a tree from a heap array
{
		   TREE node = (TREE)malloc(sizeof(TREE));
			if (!node) {
				fprintf(stdout, "Memmory allocation error!\n");
				exit(1);
			}
			 // put the item
			node -> item = create_item(array[i - 1], ' ');
			

			int l = LEFT(i);
			int r = RIGHT(i);

			// put the left
			if(l <= n)
			{
			 insert_left(node, create_tree_from_array(array, n , LEFT(i)));	
			}
			// put the right
			if(r <= n)
			{
			 insert_right(node, create_tree_from_array(array, n, RIGHT(i)));		
			}

			//print_tree(node);
		

	return node;

}


void insert_left(TREE parent, TREE son)
{
	parent->left = son;
}

void insert_right(TREE parent, TREE son)
{
	parent->right = son;
}

void insert(TREE parent, TREE left_son, TREE right_son)
{
	parent->left = left_son;
	parent->right = right_son;
}

TREE get_left(TREE parent)
{
	return parent->left;
}

TREE get_right(TREE parent)
{
	return parent->right;
}

ITEM get_item(TREE node)
{
	return node->item;
}


void print_tree_pre_order(TREE tree)
{
	if(tree != NULL)
	{
		printf("%d,\t", get_item_key(tree->item));
		print_tree_pre_order(tree->left);
		print_tree_pre_order(tree->right);

	}

}

void print_tree_in_order(TREE tree)
{
	if(tree != NULL)
	{
		print_tree_in_order(tree->left);
		printf("%d,\t", get_item_key(tree->item));
		print_tree_in_order(tree->right);

	}
}

void print_tree_post_order(TREE tree)
{
	if(tree != NULL)
	{
		print_tree_post_order(tree->left);
		print_tree_post_order(tree->right);
		printf("%d,\t", get_item_key(tree->item));
	}


}

int get_tree_height(TREE tree)
{	int left_height = 0;
	int right_height = 0;
	
	if( tree != NULL)
	{	if(tree->left) left_height = 1;
		if(tree->right) right_height = 1;
		left_height += get_tree_height(tree->left);
		right_height += get_tree_height(tree->right);
	}

	return (left_height > right_height?left_height:right_height);

}

void delete_node(TREE * node){
	(*node)->left = NULL;
	(*node)->right = NULL;
	free(*node);
	*node = NULL;
}

void search_and_delete_node(TREE * node, int key)
{
	if(*node!=NULL)
	{
		if (get_item_key((*node)->item)==key)
		{
			delete_node(node);
			return; // break the search
		}else
		{
			search_and_delete_node(&((*node)->left), key);
			search_and_delete_node(&((*node)->right), key);
		}
	}
}

void mirror_tree(TREE *root)
{
	if((*root)!=NULL)
	{
		TREE temp = (*root)->left;
		(*root)->left = (*root)->right;
		(*root)->right = temp;

		mirror_tree(&((*root)->left));
		mirror_tree(&((*root)->right));
	}
}





// BST functions

void search_remove_node_BST(int item_to_find, TREE * node)
{

		if(*node!=NULL)
		{
			if(get_item_key((*node)->item)==item_to_find) // if it is the current node,
			{
				if ((*node)->right == NULL) // if the right child equals NULL, please note we do not need to check the left,
											// since if the left = NULL, then then node will be removed
				{
					TREE temp = *node;
					*node = (*node)->left;
					delete_node(&temp);
				}else // otherwise it has a right child
				{
				  TREE min =  get_min_BST((*node)->right);
		  		  set_item_key((*node)->item, get_item_key(min->item));
		  		  search_and_delete_node(&((*node)->right), get_item_key(min->item));	
				}
			}else //it is not the current node, so we search in the left or right depending if it is > or <
			if(get_item_key((*node)->item) < item_to_find) // search in the left
				search_remove_node_BST(item_to_find, &((*node)->right));
			else if (get_item_key((*node)->item) > item_to_find) // search in the right
				search_remove_node_BST(item_to_find, &((*node)->left));
	}

}

TREE get_min_BST(TREE node)
{
	TREE indicator = node;

	while(indicator->left!=NULL)
	{
		indicator = indicator->left;

	}
	return indicator;
}


TREE search_BST(int item_to_find, TREE node)
{
	if(node!=NULL)
	{
	if(item_to_find == get_item_key(node->item))
		return node;
	if(item_to_find > get_item_key(node->item))
		search_BST(item_to_find, node->right);
	else
		search_BST(item_to_find,node->left);
	}
}


void insert_BST(TREE node_to_insert, TREE *root)
{
	if(*root == NULL || get_item_key((*root)->item) == get_item_key(node_to_insert->item))
	{
		*root = node_to_insert;
		return;
	}

	if(get_item_key((*root)->item) > get_item_key(node_to_insert->item))
	{
		insert_BST(node_to_insert, &((*root)->left));
	}else
	{
		insert_BST(node_to_insert, &((*root)->right));
	}

}