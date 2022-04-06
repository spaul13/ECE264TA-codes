// tree.h
#ifndef TREE_H
#define TREE_H
typedef struct treenode
{
  struct treenode * left;
  struct treenode * right;
  unsigned char letter; 
} TreeNode;
TreeNode * TreeNode_create(unsigned char val);
TreeNode * Tree_merge(TreeNode * tn1, TreeNode * tn2);
void Tree_destroy(TreeNode * tn);
void Tree_printCode(TreeNode * tn, unsigned char * buff, int level);
/*
void Tree_print(TreeNode * tn, int level);
int Tree_height(TreeNode * tn);
int Tree_leaf(TreeNode * tn);
void Tree_header(TreeNode * tn, unsigned int numChar, char * outfile);
void Tree_destroy(TreeNode * tn);
*/
#endif
