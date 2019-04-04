#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "rbt.h"


int main(void)
{

	data_t d;
	res_t res;
	rbt_t *rbt = create_rbt();
	
	printf("INSERT(100)\n");
	insert_rbt(rbt, 100);
	//res = successor(rbt, 100, &d);
	//assert(res == BST_NO_SUCCESSOR);
	//printf("SUCCESSOR(100)=NO_SUCCESSOR\n");
	//res = predecessor(rbt, 100, &d);
	//assert(res == BST_NO_PREDECESSOR);
	//printf("SUCCESSOR(100)=NO_PREDECESSOR\n");
	printf("INSERT(50)\n");
	insert_rbt(rbt, 50);
	printf("INSERT(25)\n");
	insert_rbt(rbt, 25);
	printf("INSERT(75)\n");
	insert_rbt(rbt, 75);
	printf("INSERT(65)\n");
	insert_rbt(rbt, 65);
	printf("INSERT(150)\n");
	insert_rbt(rbt, 150);
	printf("INSERT(125)\n");
	insert_rbt(rbt, 125);
	printf("INSERT(130)\n");
	insert_rbt(rbt, 130);
	printf("INSERT(175)\n");
	insert_rbt(rbt, 175);

	assert(search_rbt(rbt, 75) == TRUE);
	assert(search_rbt(rbt, 166)== FALSE);

	printf("IN-ORDER  : ");
	inorder(rbt);
	printf("PRE-ORDER : ");
	preorder(rbt);
	printf("POST-ORDER: ");
	postorder(rbt);

	res = minimum(rbt, &d);
	assert(res == SUCCESS);
	printf("MIN: %d\n", d);
	res = maximum(rbt, &d);
	assert(res == SUCCESS);
	printf("MAX: %d\n", d);

	res = successor(rbt, 50, &d);
	assert(res == SUCCESS);
	printf("SUCCESSOR(50)=%d\n", d);
	res = successor(rbt, 100, &d);
	assert(res == SUCCESS);
	printf("SUCCESSOR(100)=%d\n", d);
	res = successor(rbt, 75, &d);
	assert(res == SUCCESS);
	printf("SUCCESSOR(75)=%d\n", d);
	res = successor(rbt, 175, &d);
	assert(res == NO_SUCCESSOR);
	printf("SUCCESSOR(175)=NO_SUCESSOR\n");
	res = successor(rbt, 25, &d);
	assert(res == SUCCESS);
	printf("SUCCESSOR(25)=%d\n", d);

	res = predecessor(rbt, 65, &d);
	assert(res == SUCCESS);
	printf("PREDECESSOR(65)=%d\n", d);
	res = predecessor(rbt, 125, &d);
	assert(res == SUCCESS);
	printf("PREDECESSOR(125)=%d\n", d);
	res = predecessor(rbt, 100, &d);
	assert(res == SUCCESS);
	printf("PREDECESSOR(100)=%d\n", d);
	res = predecessor(rbt, 25, &d);
	assert(res == NO_PREDECESSOR);
	printf("PREDECESSOR(25)=NO_PREDECESSOR\n");
	res = predecessor(rbt, 175, &d);
	assert(res == SUCCESS);
	printf("PREDECESSOR(175)=%d\n", d);
	
/*	printf("INORDER-NRC:  ");
	inorder_nrc(rbt);
	printf("PREORDER-NRC: ");
	preorder_nrc(rbt);
	printf("POSTORDER-NRC: Implementation In Progress\n");
	//postorder_nrc(rbt);
*/	
	printf("DELETE(75)\n");
	res = delete_rbt(rbt, 75);
	//printf("DELETE(125)\n");
	//res = delete_rbt(rbt, 125);
	//printf("DELETE(50)\n");
	//res = delete_rbt(rbt, 50);
	//printf("DELETE(100)\n");
	//res = delete_rbt(rbt, 100);
	assert(res == SUCCESS);	
	printf("IN-ORDER  : ");
	inorder(rbt);
	printf("PRE-ORDER : ");
	preorder(rbt);
	printf("POST-ORDER: ");
	postorder(rbt);

	assert(destroy_rbt(&rbt) == SUCCESS && rbt == NULL);

	exit(EXIT_SUCCESS);
}
