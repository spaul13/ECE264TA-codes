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
void Tree_createCode(TreeNode * tn, unsigned char * buff,
		     int level, int * * codebook);
#endif
