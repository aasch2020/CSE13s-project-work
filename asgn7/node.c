#include "node.h"
#include <stdlib.h>
Node *node_create(char *oldspeak, char *newspeak){
	Node *n = (Node *) calloc(1, sizeof(Node));
	if(newspeak){
		n->newspeak = strdup(newspeak);
	}else{

		n->newspeak = NULL;
	}
	n->oldspeak = strdup(oldspeak);
	return n

}

Node node_delete(Node **n){
	if(oldspeak){
		free(*n->oldspeak);
	}
	if(newspeak){
		free(*n->newspeak);
	}
	free(*n);
	*n=NULL;

}

void node+print(Node *n){
	if(n->newspeak){
		printf("%s -> %s\n", n->oldspeak , n->newspeak);
	}else{
		printf("%s\n", n->oldspeak);
	}

}
