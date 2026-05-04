#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

#define COUNT_NUMBERS 64

int isInArr(int arr[], int len, int target)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == target) return 1;
	}

	return 0;
}


int main() 
{
	printf("hello world!\n");
	
	//bst_node* head = create_bst_node("name", "phone");
	bst_node* head = NULL;

	int arr[COUNT_NUMBERS] = {0};
	
	int temp = 0;
	for (int i = 0; i < COUNT_NUMBERS; i++)
	{
		do 
		{
			temp = rand() % 100;
		}
		while (isInArr(arr, i - 1, temp));
		
		arr[i] = temp;

		head = bst_insert(head, arr[i]);
		printf("%d ", arr[i]);
	}

	printf("\n\ninorder traversal: \n");
	bst_inorder_traversal(head);

	printf("\n\npreorder traversal: \n");
	bst_preorder_traversal(head);

	int target_val = 4;
	printf("\n\nУдаляем элемент с значением %d:\n", target_val);
	
	head = bst_delete(head, target_val);

	bst_inorder_traversal(head);
	

	printf("\n\nВывод дерева:\n");

	printTree(head, 0);

	printf("\n\nОбход в ширину:\n");
	treeLevelTraversal(head);
	


	delete_bst(head);
	return 0;
}
