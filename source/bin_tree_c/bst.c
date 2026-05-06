#include <stdio.h>
#include <stdlib.h>

#include "bst.h"
#include "queue.h"
/*
3. Двоичное дерево поиска
Узел — словарь: `{'val': '123', 'left': None, 'right': None}.`

Функции:

def bst_insert(root, name, phone) — рекурсивно или итеративно вставляет, возвращает новый корень (если корень меняется).

def bst_find(root, name) — поиск.

def bst_delete(root, name) — удаление, возвращает новый корень.

def bst_list_all(root) — центрированный обход (рекурсивно собирает записи в отсортированном порядке).
*/


bst_node* create_bst_node(int value)
{
	bst_node* node = (bst_node*)malloc(sizeof(bst_node));

	node->value = value; 	

	node->left = NULL;
	node->right = NULL;

	return node;
}

bst_node* bst_minimum(bst_node* node)
{
	if (node->left == NULL)
		return node;
	return bst_minimum(node->left);
}

bst_node* bst_maximum(bst_node* node)
{
	if (node->right == NULL)
		return node;
	return bst_maximum(node->right);
}

void print_bst(bst_node node)
{
	printf("value: %d\n", node.value);
}

void bst_inorder_traversal(bst_node* HEAD)
{
	if (HEAD != NULL)
	{
		bst_inorder_traversal(HEAD->left);
		print_bst(*HEAD);
		bst_inorder_traversal(HEAD->right);
	}
}

void bst_preorder_traversal(bst_node* HEAD)
{
	if (HEAD != NULL)
	{
		print_bst(*HEAD);
		bst_preorder_traversal(HEAD->left);
		bst_preorder_traversal(HEAD->right);
	}
}

bst_node* bst_search(bst_node* HEAD, char target_val)
{
	/*
	Node search(x : Node, k : T):
   if x == null or k == x.key
      return x
   if k < x.key
      return search(x.left, k)
   else
      return search(x.right, k)
	*/

	if ((HEAD == NULL) || (HEAD->value == target_val))
	{
		return HEAD;
	}
	if (target_val < HEAD->value)
	{
		return bst_search(HEAD->left, target_val);
	}
	else
	{
		return bst_search(HEAD->right, target_val);
	}
}

bst_node* bst_insert(bst_node* HEAD, int value)
{
	/*
  Node insert(x : Node, z : T):               // x — корень поддерева, z — вставляемый ключ
   if x == null 
      return Node(z)                        // подвесим Node с key = z
   else if z < x.key
      x.left = insert(x.left, z)
   else if z > x.key
      x.right = insert(x.right, z)
   return x
	*/

	if (HEAD == NULL)
	{
		return create_bst_node(value);
	}
	else if (value < HEAD->value)
	{
		HEAD->left = bst_insert(HEAD->left, value);
	}
	else if (value > HEAD->value)
	{
		HEAD->right = bst_insert(HEAD->right, value);
	}
	return HEAD;
}

bst_node* bst_delete(bst_node* root, int target_val)
{               // корень поддерева, удаляемый ключ
	if (root == NULL)
		return root;

	if (target_val < root->value)
    	root->left = bst_delete(root->left, target_val);
	else if (target_val > root->value)
    	root->right = bst_delete(root->right, target_val);
	else {
		if (root->left != NULL && root->right != NULL)
		{
    		root->value = bst_minimum(root->right)->value;
    		root->right = bst_delete(root->right, root->value);
		} 
		else 
		{
    		bst_node* temp = root;
			if (root->left != NULL)
				root = root->left;
			else
				root = root->right;
			free(temp);
		}
	}
  	return root;
}

void delete_bst(bst_node* root)
{
	if (root == NULL)
		return;
	else
	{
		delete_bst(root->left);
		delete_bst(root->right);
		free(root);
	}
}

void printTree(bst_node* node, int depth) {

    if (node == NULL) return;
    
    printTree(node->right, depth + 1);
    
    for (int i = 0; i < depth; i++)
        printf("\t");
    printf("%d\n", node->value);
    
    printTree(node->left, depth + 1);
}

void treeLevelTraversal(bst_node* node) {
  	if (!node) return;

  	Queue q;
  	Queue* hq = &q;
  	queueInit(hq);

  	queuePush(hq, node);
  	while(!queueEmpty(hq)) 
  	{
    	bst_node* hn = queuePop(hq);
    	printf("%d\n", hn->value);
    	
		if(hn->left) 
			queuePush(hq, hn->left);
    	if(hn->right) 
			queuePush(hq, hn->right);

  	};
}; 
