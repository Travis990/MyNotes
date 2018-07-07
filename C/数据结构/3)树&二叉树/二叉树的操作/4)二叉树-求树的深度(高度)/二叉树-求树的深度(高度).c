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

// 获取树的高度(深度)
int TreeHeight(TreeNode *root)
{
	if (NULL == root)
	{
		return -1;
	}
	// 求左子树的高度
	int Lheight = TreeHeight(root->Lchild);
	// 求右子树的高度
	int Rheight = TreeHeight(root->Rchild);
	// 左右子树, 哪个高就取那个, 然后再加1
	int height = Lheight > Rheight ? Lheight + 1 : Rheight + 1;

	return height;
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

	int height = TreeHeight(&node1);
	printf("height:%d\n", height);

	system("pause");
	return 0;
}