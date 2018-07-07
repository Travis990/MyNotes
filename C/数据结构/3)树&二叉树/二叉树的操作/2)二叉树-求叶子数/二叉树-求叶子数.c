#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 二叉树的节点
typedef struct TreeNode {
	char ch;

	struct TreeNode *Lchild;
	struct TreeNode *Rchild;
}TreeNode;

// 求树的叶子数
void leafNum(TreeNode *root, int *num)
{
	// 递归条件退出
	if (NULL == root)
	{
		return;
	}

	// 当节点的左孩子和右孩子都为空时, 这个节点就是叶子节点
	if (NULL == root->Lchild && NULL == root->Rchild)
	{
		(*num)++;
	}
	// 遍历左孩子树
	leafNum(root->Lchild, num);
	// 遍历右孩子树
	leafNum(root->Rchild, num);
}

int main()
{
	/*
	树:
				A
			   / \
			  B   F
			  \    \
			   C	G
			  /\	/
			 D  E  H

	先序遍历(根左右): A B C D E F G H
	中序遍历(左根右): B D C E A F H G
	后序遍历(左右根): D E C B H G F A
	*/

	// 模拟树
	TreeNode node1 = { 'A',NULL,NULL };
	TreeNode node2 = { 'B',NULL,NULL };
	TreeNode node3 = { 'C',NULL,NULL };
	TreeNode node4 = { 'D',NULL,NULL };
	TreeNode node5 = { 'E',NULL,NULL };
	TreeNode node6 = { 'F',NULL,NULL };
	TreeNode node7 = { 'G',NULL,NULL };
	TreeNode node8 = { 'H',NULL,NULL };

	// 建立二叉树
	node1.Lchild = &node2; // B
	node1.Rchild = &node6; // F

	node2.Rchild = &node3; // C

	node3.Lchild = &node4; // D
	node3.Rchild = &node5; // E

	node6.Rchild = &node7; // G

	node7.Lchild = &node8; // H


	// 求叶子数
	int num = 0;
	leafNum(&node1, &num);
	printf("num=%d\n", num);

	system("pause");
	return 0;
}