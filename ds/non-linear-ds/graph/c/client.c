#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bst.h"


int main(void)
{

	data_t d;
	res_t res;
	bst_t *bst = create_bst();
	
	printf("INSERT(100)\n");
	insert_bst(bst, 100);
	res = successor(bst, 100, &d);
	assert(res == BST_NO_SUCCESSOR);
	printf("SUCCESSOR(100)=NO_SUCCESSOR\n");
	res = predecessor(bst, 100, &d);
	assert(res == BST_NO_PREDECESSOR);
	printf("SUCCESSOR(100)=NO_PREDECESSOR\n");
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

	printf("IN-ORDER  : ");
	inorder(bst);
	printf("PRE-ORDER : ");
	preorder(bst);
	printf("POST-ORDER: ");
	postorder(bst);

	res = minimum(bst, &d);
	assert(res == BST_SUCCESS);
	printf("MIN: %d\n", d);
	res = maximum(bst, &d);
	assert(res == BST_SUCCESS);
	printf("MAX: %d\n", d);

	res = successor(bst, 50, &d);
	assert(res == BST_SUCCESS);
	printf("SUCCESSOR(50)=%d\n", d);
	res = successor(bst, 100, &d);
	assert(res == BST_SUCCESS);
	printf("SUCCESSOR(100)=%d\n", d);
	res = successor(bst, 75, &d);
	assert(res == BST_SUCCESS);
	printf("SUCCESSOR(75)=%d\n", d);
	res = successor(bst, 175, &d);
	assert(res == BST_NO_SUCCESSOR);
	printf("SUCCESSOR(175)=NO_SUCESSOR\n");
	res = successor(bst, 25, &d);
	assert(res == BST_SUCCESS);
	printf("SUCCESSOR(25)=%d\n", d);

	res = predecessor(bst, 65, &d);
	assert(res == BST_SUCCESS);
	printf("PREDECESSOR(65)=%d\n", d);
	res = predecessor(bst, 125, &d);
	assert(res == BST_SUCCESS);
	printf("PREDECESSOR(125)=%d\n", d);
	res = predecessor(bst, 100, &d);
	assert(res == BST_SUCCESS);
	printf("PREDECESSOR(100)=%d\n", d);
	res = predecessor(bst, 25, &d);
	assert(res == BST_NO_PREDECESSOR);
	printf("PREDECESSOR(25)=NO_PREDECESSOR\n");
	res = predecessor(bst, 175, &d);
	assert(res == BST_SUCCESS);
	printf("PREDECESSOR(175)=%d\n", d);
	
	printf("INORDER-NRC:  ");
	inorder_nrc(bst);
	printf("PREORDER-NRC: ");
	preorder_nrc(bst);
	printf("POSTORDER-NRC: Implementation In Progress\n");
	//postorder_nrc(bst);
	
	//printf("DELETE(75)\n");
	//res = delete_bst(bst, 75);
	//printf("DELETE(125)\n");
	//res = delete_bst(bst, 125);
	//printf("DELETE(50)\n");
	//res = delete_bst(bst, 50);
	printf("DELETE(100)\n");
	res = delete_bst(bst, 100);
	assert(res == BST_SUCCESS);
	printf("IN-ORDER  : ");
	inorder(bst);
	printf("PRE-ORDER : ");
	preorder(bst);
	printf("POST-ORDER: ");
	postorder(bst);

	assert(destroy_bst(&bst) == BST_SUCCESS && bst == NULL);

	exit(EXIT_SUCCESS);
}
