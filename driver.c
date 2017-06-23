#include <stdio.h>
#include <stdio.h>
#include "eps.h"
#include "tree.h"

int main() {

	const char * file_path = "out.eps";


	FILE * file_ptr = fopen(file_path, "w+");
	write_eps_header(file_ptr, "lines", CANVAS_WIDTH, CANVAS_HEIGHT);
	//setup the (0,0) of the coordinate system
	fprintf(file_ptr, "\n %d %d translate \n", CANVAS_WIDTH /2, CANVAS_HEIGHT -100 );




	ITEM it1 = create_item(25, 'a');
	ITEM it2 = create_item(20, 'b');
	ITEM it3 = create_item(27, 'c');
	ITEM it4 = create_item(10, 'd');
	ITEM it5 = create_item(22, 'e');
	ITEM it6 = create_item(26, 'd');
	ITEM it7 = create_item(30, 'e');


	TREE root = create_node(it1); // root

	TREE left = create_node(it2);

	TREE right = create_node(it3);

	insert(root, left, right);
	insert(left, create_node(it4), create_node(it5));
	insert(right, create_node(it6), create_node(it7));
	 


	print_tree_pre_order(root); printf("\n");
	print_tree_in_order(root); printf("\n");
	print_tree_post_order(root); printf("\n");

	search_remove_node_BST(25, &root);



	 // to draw a tree given its root use
	mirror_tree(&root);draw_tree(file_ptr, root, (float)get_tree_height(root) + 2, 1, 0 , 0, 0 );
	fprintf(file_ptr, "\nshowpage\n");
	fclose(file_ptr);

	
		
	return 0;
}
