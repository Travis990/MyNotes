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

// 打印树 - 先序遍历 (根左右)
void print_r(TreeNode *root)
{
	if (NULL == root)
	{
		return;
	}

	// 先序遍历 (根左右)
	printf("%c\t", root->ch);
	// 再访问左子树
	print_r(root->Lchild);
	// 再访问右子树
	print_r(root->Rchild);
}

// 拷贝数
TreeNode *copyTree(TreeNode *root)
{
	if (NULL == root)
	{
		return NULL;
	}

	// 递归拷贝左子树
	TreeNode *l = copyTree(root->Lchild);
	// 递归拷贝右子树
	TreeNode *r = copyTree(root->Rchild);
	// 定义空间, 装数据
	TreeNode *newnode = (TreeNode*)malloc(sizeof(TreeNode));
	// 拷贝
	newnode->ch = root->ch;
	newnode->Lchild = l;
	newnode->Rchild = r;
	return newnode;
}

// 释放堆空间
void freeSpace(TreeNode *root)
{
	if (NULL == root)
	{
		return;
	}
	// 释放左子树
	freeSpace(root->Lchild);
	// 释放右子树
	freeSpace(root->Rchild);
	// 释放根节点
	free(root);
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

	// 拷贝二叉树
	TreeNode *root = copyTree(&node1);
	// 打印原来的树
	print_r(&node1);
	printf("\n--------------------------------------\n");
	// 打印拷贝的树
	print_r(root);

	// 释放拷贝的二叉树空间
	freeSpace(root);

	system("pause");
	return 0;
}