#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"


int main(void)
{

	bst_t *bst = create_bst();
	
	insert_bst(bst, 100);
	insert_bst(bst, 50);
	insert_bst(bst, 25);
	insert_bst(bst, 75);
	insert_bst(bst, 65);
	insert_bst(bst, 150);
	insert_bst(bst, 125);
	insert_bst(bst, 130);
	insert_bst(bst, 175);

	assert(search_bst(bst, 75) == TRUE);
	assert(search_bst(bst, 166)== FALSE);

	printf("IN-ORDER: ");
	inorder(bst);
	printf("PRE-ORDER: ");
	preorder(bst);
	printf("POST-ORDER: ");
	postorder(bst);

	assert(destroy_bst(&bst) == BST_SUCCESS && bst == NULL);

	exit(EXIT_SUCCESS);
}
