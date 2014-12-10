#include<stdlib.h>
#include<stdio.h>
typedef struct node 
{
    int val;
    struct node * next;
} node_t;

node_t* initialize(node_t *node,int n)
{
	node=(node_t*)malloc(sizeof(node_t));
	if(node==NULL) puts("Error");
	node->val=n;
	node->next=NULL;
	return node;
}
int size(node_t *node)
{
	node_t *current=node;
	int i=0;
	if(current==NULL) exit(0);
	else
	{
		
		do
		{
			i++;
			current=current->next;
		}
		while(current!=NULL);
		return i;
	}
}
int capacity(node_t *node)
{
	node_t *current=node;
	int cap=0;
	if(current==NULL) return 0;
	else
	{
		do
		{
			cap+=sizeof(*current);
			current=current->next;
		}
		while(current!=NULL);
		return cap;
	}
}
int empty(node_t *node)
{
	return (size(node))? 1:0;
}
int push_back(node_t *node,int n)
{
	node_t *current=node;
	if(current!=NULL)
	{
		while(current->next) current=current->next;
		current->next=malloc(sizeof(node_t));
		current->next->val=n;
		current->next->next=NULL;
		return 1;
	}
	else return 0;
}
void insert(node_t** node,int n, int position)
{
	int i=1;
	node_t *current=*node,*tmp=NULL;
	if(position>size(*node))
	{
		puts("List too short");
		return;
	}
	else if(position==1)
	{
		tmp=malloc(sizeof(node_t));
		tmp->val=n;
		tmp->next=*node;
		*node=tmp;
		return;
	}
	else
	{
		for(i=1;i<position;i++) current=current->next;
		tmp=malloc(sizeof(node_t));
		tmp->val=n;
		tmp->next=current->next;
		current->next=tmp;
		return;
	}
}
void remove_node(node_t** node,int position) /* stdio.h has remove() to for removing file */
{
	int i=1;
	node_t *current=*node,*tmp=NULL;
	if(position>size(*node))
	{
		puts("No element to remove from the list");
		return;
	}
	else if(position==1)
	{
		tmp=(*node)->next;
		free(*node);
		*node=tmp;
		return;
	}
	else
	{
		for(i=1;i<(position-1);i++) current=current->next;
		tmp=current->next->next;
		free(current->next);
		current->next=tmp;
		return;
	}
}
int at(node_t* node,int position)
{
	int i=1;
	node_t* current=node;
	for(i=1;i<position;i++) current=current->next;
	return current->val;
}
void reverse(node_t** node)
{
	node_t* current=*node,*tmp=NULL;
	while(current->next)
	{
		tmp=current->next;
		current->next=tmp->next;
		tmp->next=*node;
		*node=tmp;
	}
}
void print_list(node_t* node)
{
	int i=1;
	node_t *current=node;
	if(current!=NULL)
	{
		do
		{
			printf("%d. %d\n",i++,current->val);
			current=current->next;
		}
		while(current!=NULL);
	}
}
void check(node_t* node)
{
	print_list(node);
	printf("The list has %d elements.\n",size(node));
	printf("The list has %d bytes.\n",capacity(node));
	printf("The list is%s empty.\n",empty(node)?" not":"");
}
int main()
{
	node_t *List=NULL;
	List=initialize(List, 5);
	push_back(List,7);
	check(List);
	insert(&List,2,1);
	check(List);
	insert(&List,9,3);
	check(List);
	reverse(&List);
	check(List);
	remove_node(&List,1);
	check(List);
	remove_node(&List,2);
	check(List);
	printf("The %d. element of the list is %d\n",2,at(List,2));
	exit(0);
}