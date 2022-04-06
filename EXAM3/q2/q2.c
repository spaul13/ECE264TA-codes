#include "tree.h"
#include <stdlib.h>

TreeNode * treenode_construct (int key) {
    TreeNode * tn = malloc(sizeof(*tn));
    tn -> value = key;
    tn -> left = NULL;
    tn -> right = NULL;
    return tn;
}

TreeNode * tree_insert (TreeNode * tn, int key) {
    if (tn == NULL) {
        return treenode_construct (key);
    }
    // There is a bug here: it does not check if key == (tn -> value)
    // Do NOT fix the bug and answer questions
    if (key < (tn -> value)) {
        tn -> left = tree_insert (tn -> left, key);
    }
    else {
        tn -> right = tree_insert (tn -> right, key);
    }
    return tn;
}

TreeNode * tree_delete(TreeNode * tn, int key) {
    // ----Search for the node to be deleted----
    if (tn == NULL) {
        return NULL;
    }
    if (key < (tn -> value)) {
        tn -> left = tree_delete(tn -> left, key);
        return tn;
    }
    if (key > (tn -> value)) {
        tn -> right = tree_delete(tn -> right, key);
        return tn;
    }

    // ----Implement the delete: tn is the node to delete----
    if (key == (tn -> value)) {
        // if tn has no child
        if (((tn -> left) == NULL) && ((tn -> right) == NULL)) {
            free(tn);
            return NULL;	
        }

        // if tn has one child: left child
        if ((tn -> left) != NULL && (tn -> right) == NULL) {
            TreeNode * sn = tn -> left; // sn is the substitue node
            free (tn); // free the current root
            return sn; // return the substitute node
        }
        // if tn has one child: right child
        if ((tn -> left) == NULL && (tn -> right) != NULL) {
            TreeNode * sn = tn -> right; // sn is the substitue node
            free(tn); // free the current root
            return sn; // return the substitute node
        }
        
        // if tn have two children 
        // step 1: find sn (substitute node)
        // sn is the rightmost node on the left subtree of tn
        TreeNode * sn = tn -> left; // go to the left subtree
        while ((sn -> right) != NULL) { // get the rightmost node
            sn = sn -> right;
        }
        // step 2: swap the values of sn and tn
        tn -> value = sn -> value;
        sn -> value = key;
        // step 3: delete sn via recursive function call
        tn -> left = tree_delete(tn -> left, key);
        return tn;
    }
    return tn;
}
