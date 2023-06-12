// C implementation of the First
// Fit memory management algorithm
// using a linked list. This implementation
// is exactly the same as the ordinary First Fit
// memory management discusesd in that file
// except we use a linked
// list instead of an array. Some important
// and common  C features are used. We have stucture
// pointers as well as several pointers to structures.
// But now we can delete elements as well as add them.

#include <stdio.h>
#include <stdlib.h>

// Two global counters
int g = 0, k = 0;

// Structure for free list
struct free {
	int tag;
	int size;
	struct free* next;
} *free_head = NULL, *prev_free = NULL;

// Structure for allocated list
struct alloc {
	int block_id;
	int tag;
	int size;
	struct alloc* next;
} *alloc_head = NULL, *prev_alloc = NULL;

// Function to create free
// list with given sizes
void create_free(int c)
{
	struct free *p
		= (struct free*)malloc(sizeof(struct free));
	p->size = c;
	p->tag = g;
	p->next = NULL;
	if (free_head == NULL)
		free_head = p;
	else
		prev_free->next = p;
	prev_free = p;
	g++;
}

// Function to print free list which
// prints free blocks of given sizes
void print_free()
{
	struct free *p = free_head;
	printf("Tag\tSize\n");
	while (p != NULL) {
	        printf("%d", p->tag);
	        printf("%d",p->size);
		printf("\n");
		p = p->next;
	}
}

// Function to print allocated list which
// prints allocated blocks and their block ids
void print_alloc()
{
	struct alloc *p = alloc_head;
	printf("Tag\tBlock ID\tSize\n");
	while (p != NULL) {
	        printf("%d\t", p->tag);
	        printf("%d\t",p->block_id);
		printf("%d\t\t", p->size);
		printf("\n");
		p = p->next;
	}
}

// Function to allocate memory to
// blocks as per First fit algorithm
void create_alloc(int c)
{
	// create node for process of given size
	struct alloc* q
		= (struct alloc*)malloc(sizeof(struct alloc));
	q->size = c;
	q->tag = k;
	q->next = NULL;
	struct free* p = free_head;

	// Iterate to find first memory
	// block with appropriate size
	while (p != NULL) {
		if (q->size <= p->size)
			break;
		p = p->next;
	}

	// Node found to allocate
	if (p != NULL) {
		// Adding node to allocated list
		q->block_id = p->tag;
		p->size -= q->size;
		if (alloc_head == NULL)
			alloc_head = q;
		else {
			prev_alloc = alloc_head;
			while (prev_alloc->next != NULL)
				prev_alloc = prev_alloc->next;
			prev_alloc->next = q;
		}
		k++;
	}
	else // Node found to allocate space from
	           printf("Block of size %d cannot be allocated\n", c);
		        
}

// Function to delete node from
// allocated list to free some space
void delete_alloc(int t)
{
	// Standard delete function
	// of a linked list node
	struct alloc *p = alloc_head, *q = NULL;

	// First, find the node according
	// to given tag id
	while (p != NULL) {
		if (p->tag == t)
			break;
		q = p;
		p = p->next;
	}
	if (p == NULL)
	     printf("Tag ID doesn't exist\n");
	else if (p == alloc_head)
		alloc_head = alloc_head->next;
	else
		q->next = p->next;
	struct free *temp = free_head;
	while (temp != NULL) {
		if (temp->tag == p->block_id) {
			temp->size += p->size;
			break;
		}
		temp = temp->next;
	}
}

// Driver Code
int main()
{
	int blockSize[] = { 100, 500, 200 };
	int processSize[] = { 417, 112, 426, 95 };
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);

	for (int i = 0; i < m; i++)
		create_free(blockSize[i]);

	for (int i = 0; i < n; i++)
		create_alloc(processSize[i]);

	print_alloc();

	// Block of tag id 0 deleted
	// to free space for block of size 426
	delete_alloc(0);

	create_alloc(426);
	printf("After deleting block  with tag id 0.\n");
	print_alloc();
}
