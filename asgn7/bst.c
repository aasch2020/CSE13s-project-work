#include "bst.h"
#include "node.h"
#include <string.h>
#include <stdio.h>

//create an empty binary search tree, which is NULL.
Node *bst_create(void) {
    return NULL;
}
uint64_t branches = 0;

//returns the height of the given bst.
//A recursive function
//If the node exists, call itself on the left and right nodes, and return 1 + the greater of the two heights.
//This means that the function returns 1+ the height of the larger subtree.
//If the node does not exist return 0.
//The implementation for this below code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021).
uint32_t bst_height(Node *root) {
    if (root) {
        uint32_t l = bst_height(root->left);
        uint32_t r = bst_height(root->right);
        if (l > r) {
            return 1 + l;

        } else {
            return 1 + r;
        }
    }
    return 0;
}

//Takes the given bst rooted at the root node and returns thee size of the bst.
//If the node is null, return 0.
//If it is not, return 1 + the sun of the size of the sizes of the trees rooted at the left and right nodes.
uint32_t bst_size(Node *root) {
    if (root) {
        return 1 + bst_size(root->left) + bst_size(root->right);
    }

    return 0;
}

//Deletes the treee rooted at the node root. Returns void
//This code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021)
//This function first checks if the given node exists, if it does, it calls itself on its left and right children,
//to delete them, and then deletes itself and sets its pointer to NULL.
//This ensures that there are no child nodes left unfreed, as children are alwasy deleted before parent nodes.
void bst_delete(Node **root) {
    if (*root) {
        bst_delete(&((*root)->left));
        bst_delete(&((*root)->right));
        node_delete(root);
        *root = NULL;
    }
    return;
}

//
//
//This function takes an oldspeak string and checks if it in the binary search tree rooted at root.
//The given insertion ensures that the nodes are ordered lexicographically, thus find can search lexicographically.
//This code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021)
//If the node exists, check the node with the string we are searching for. If the node is lexicographically greater,
//Search the right subtree, and return the result of that search.
//If the node is lexicographically less, search the right subtree and return the result of that search.
//If the node is equal to the string, we found the node, return the node.
//IF the node is null, we searched and didn't find the node, thus null is returned.
Node *bst_find(Node *root, char *oldspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) {
            branches++; //This increments the tracking var for stats
            return bst_find(root->left, oldspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) {
            branches++;
            return bst_find(root->right, oldspeak);
        }
        if (strcmp(root->oldspeak, oldspeak) == 0) {

            return root;
        }
    }

    return root;
}

//Takes two strings for oldspeak and newspeak, and inserts it into the binary search tree, it returns the node passed to it.
//If the node exists, either enter it's left or right subtree recursively using the lexicographical ordering with the given oldspeak.
//If the node exists and is equal to the given oldspeak, we have found a duplicate, which we do not wish to insert, return the current node and stop there.
//If the node does not exist, we have found where to insert the node, create a new node with given newspeak and oldspeak and return it.
//This code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021)
//To be noted: this function does not insert properly into a null tree, as if the initial pointer is null, it will create and return the node to be inserted,
//but not change the null pointer.
Node *bst_insert(Node *root, char *oldspeak, char *newspeak) {
    if (root) {
        if (strcmp(root->oldspeak, oldspeak) > 0) { //insert left.
            branches++; //This increments the tracking var for stats
            root->left = bst_insert(root->left, oldspeak, newspeak);
            return root;
        }
        if (strcmp(root->oldspeak, oldspeak) < 0) { //insert right.
            branches++; //This increments the tracking var for stats
            root->right = bst_insert(root->right, oldspeak, newspeak);
            return root;
        }
        if (strcmp(root->oldspeak, oldspeak) == 0) { //duplicate protection

            return root;
        }
    }

    return node_create(oldspeak, newspeak); //insert here
}

//Take the given tree rooted at root and lexicographcally ordered print the tree.
//This tree uses inorder traversal, by printing the left subtree first, then the right.
//It checks to ensure the given node exists before attempting to print it.
//This code inspired by/adapted from the code shown in the BST lecture 18 (Professor Long 2021)
void bst_print(Node *root) {
    if (root) {
        bst_print(root->left);
        node_print(root);
        bst_print(root->right);
    }
    return;
}
