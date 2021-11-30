#include "bst.h"
#include <string.h>
#include "node.h"
#include <stdio.h>
Node *bst_create(void) {
    return NULL;
}

uint32_t bst_height(Node *root) {
    if (root) {
        int l = bst_height(root->left);
        int r = bst_height(root->right);
        if (l > r) {
            return 1 + l;

        } else {
            return 1 + r;
        }
    }
    return 0;
}

uint32_t bst_size(Node *root) {
    if (root) {
        return 1 + bst_size(root->left) + bst_size(root->right);
    }

    return 0;
}

void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&((*root)->left));
        bst_delete(&((*root)->right));
        node_delete(root);
        *root = NULL;
    }
}
Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            return bst_find(root->left, oldspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) {
            return bst_find(root->right, oldspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) == 0) {
            return root;
        }
    }

    return root;
}

Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            root->left = bst_insert(root->left, oldspeak, newspeak);
            return root;
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) {
            root->right = bst_insert(root->right, oldspeak, newspeak);
            return root;
        }
        if (strcmp(root->oldspeak, oldspeak) == 0) {
            return root;
        }
    }

    return node_create(oldspeak, newspeak);
}

void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
    return;
}
