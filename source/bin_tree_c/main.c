#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

#define NAME_BUFF_SIZE 50
#define PHONE_BUFF_SIZE 12+1 // +1 for end symbol	

int main()
{
	Node* list = NULL;
	char phone[] = "1234";
	for (int i = 0; i < 12; i++)
	{
		char num[3];
		sprintf_s(num, 3, "%d", i);
		
		char name[] = "name ";
		strcat_s(name, 9, num);
		printf("%d %s %s\n", i, name, phone);
		list = insert(list, name, phone, 0);
	}
	char test_name[] = "name 20";
	char test_phone[] = "phone 343";

	list = insert(list, test_name, test_phone, 1);
	
	printAllNodes(list);

	printf("\n%s\n", find(list, test_name));
	
	strcpy_s(test_name, NAME_BUFF_SIZE, "name 10");
	list = deleteNode(list, test_name);
	
	printAllNodes(list);

	Node* listNodes = listAll(list);
	printListNode(listNodes, getListNodeLength(list));

	free(listNodes);

    return 0;
}
