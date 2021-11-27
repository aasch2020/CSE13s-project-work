#include "bv.h"
#include "node.h"
#include <stdio.h>

int main(){
	printf("main");
	char test[] = "newspeaks";
	char testing[] = "oldspeaks";
	char asdf[] = "badspeaks";
	Node *a = node_create(test, testing);
	node_print(a);
	test[3] = 'z';
	node_print(a);
	Node *b = node_create(asdf, NULL);
	node_print(b);
	BitVector *bv = bv_create(8);
	bv_print(bv);
	bv_set_bit(bv, 0);
	bv_set_bit(bv, 6);
	bv_print(bv);
	bv_clr_bit(bv, 0);
	bv_print(bv);
	node_delete(&a);
	node_delete(&b);
	bv_delete(&bv);


}
