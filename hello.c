#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *next;
};

void printList(struct Node *n)
{
	while (n != NULL)
	{
		printf(" %d ", n->data);
		n = n->next;
	}
	printf("\n");
}

void deleteNodeAtPos(struct Node** head_ref, int position)
{
	struct Node* node_delete = *head_ref;
	struct Node *prev;
	int counter = 0;

	if(head_ref == NULL)
	{
		printf("You cannot give a null head reference");
		return;
	} else if(position == 0) //head node
	{
		*head_ref = node_delete->next;
		free(node_delete);
		return;
	}

	while(node_delete != NULL && position != counter)
	{
		counter++;
		prev = node_delete;
		node_delete = node_delete->next;
	}

	if(node_delete == NULL) return;

	prev->next = node_delete->next;

	free(node_delete);
}

void deleteLast(struct Node* head, int key)
{
	int curr_pos = 0;
	int last_pos = -1;
	if(head == NULL) return;
	struct Node *curr_node = head;
	while(curr_node != NULL)
	{
		if(curr_node->data == key) {
			last_pos = curr_pos;
		}
		curr_node = curr_node->next;
		curr_pos++;
	}
	if(last_pos == -1) return;
	deleteNodeAtPos(&head, last_pos);
}

void deleteNode(struct Node** head_ref, int key)
{
	struct Node* node_delete = *head_ref;
	struct Node *prev;

	if(head_ref == NULL)
	{
		printf("You cannot give a null head reference");
		return;
	} else if(node_delete->data == key) //head node
	{
		*head_ref = node_delete->next;
		free(node_delete);
		return;
	}

	while(node_delete != NULL && node_delete->data != key)
	{
		prev = node_delete;
		node_delete = node_delete->next;
	}

	if(node_delete == NULL) return;

	prev->next = node_delete->next;

	free(node_delete);
}

void append(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	struct Node *last = *head_ref;

	new_node->data = new_data;

	new_node->next = NULL;

	if(*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	while(last->next != NULL)
	{
		last = last->next;
	}
	last->next = new_node;
}

void insertAfter(struct Node* prev_node, int new_data)
{
	if(prev_node == NULL)
	{
		printf("the given previous node cannot be NULL");
		return;
	}
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->data = new_data;

	new_node->next = prev_node->next;

	(prev_node)->next = new_node;
}

void push(struct Node** head_ref, int new_data)
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

	new_node->data = new_data;

	new_node->next = *head_ref;

	(*head_ref) = new_node;
}

void linkedList()
{
		struct Node* head = NULL;
		struct Node* second = NULL;
		struct Node* third = NULL;

		head = (struct Node*)malloc(sizeof(struct Node));
		second = (struct Node*)malloc(sizeof(struct Node));
		third = (struct Node*)malloc(sizeof(struct Node));

		head->data = 1;
		head->next = second;

		second->data = 2;
		second->next = third;

		third->data = 3;
		third->next = NULL;

		printList(head);
		push(&head, 0);
		printList(head);
		insertAfter(second, 4);
		printList(head);
		append(&head, 5);
		printList(head);
		deleteNode(&head, 2);
		printList(head);
		deleteNodeAtPos(&head, 1);
		printList(head);
		append(&head, 4);
		printList(head);
		deleteLast(head, 4);
		printList(head);
}

void regularList()
{
	int integers[10];
	for(int i = 0; i < 10; i++) {
		integers[i] = i;
	}
	for(int i = 0; i < 10; i++) {
		printf("%d(th/st/rd) elemnt in the array is: %d\n", i+1, integers[i]);
	}
}

void askPrintName()
{
	char name[20];
	printf("Hello, what is your name? ");
	fgets(name, 22, stdin);
	printf("Hey there, %s\n", name);
	//getchar();
}

int main()
{
	printf("hello world\n");
	linkedList();
	return 0;
}
