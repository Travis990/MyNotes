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
void print_1(TreeNode *root) 
{
	if (NULL == root)
	{
		return;
	}

	// 先序遍历 (根左右)
	printf("%c\t",root->ch);
	// 再访问左子树
	print_1(root->Lchild);
	// 再访问右子树
	print_1(root->Rchild);
}

// 打印树 - 中序遍历 (左根右)
void print_2(TreeNode *root)
{
	if (NULL == root)
	{
		return;
	}

	// 再访问左子树
	print_2(root->Lchild);
	// 中序遍历 (左根右)
	printf("%c\t", root->ch);
	// 再访问右子树
	print_2(root->Rchild);
}

// 打印树 - 后序遍历 (左右根)
void print_3(TreeNode *root)
{
	if (NULL == root)
	{
		return;
	}

	// 再访问左子树
	print_3(root->Lchild);
	// 再访问右子树
	print_3(root->Rchild);
	// 后序遍历 (左右根)
	printf("%c\t", root->ch);
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

	printf("遍历二叉树 - 先序\n");
	print_1(&node1);
	printf("\n遍历二叉树 - 中序\n");
	print_2(&node1);
	printf("\n遍历二叉树 - 后序\n");
	print_3(&node1);
	printf("\n\n");

	system("pause");
	return 0;
}