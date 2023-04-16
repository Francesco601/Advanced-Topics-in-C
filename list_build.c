/* simple list building with malloc
   to illustrate dynamic memory allocatio
   in C */

#include <stdio.h>
#include <stdlib.h>

struct listrec {
  int  value;
  struct listrec *next;
} ;

// prototype declarations 

struct listrec *build_list (void);
void visit_list (struct listrec *listptr);

struct listrec *build_list (void) {

  struct listrec *liststart = NULL,*listend,*newentry;
  int val;

  while (scanf ("%d",&val) == 1 ) {
    newentry= malloc (sizeof (struct listrec));

    if (newentry == NULL) {
        printf("malloc failed: \n");
	  exit(EXIT_FAILURE);
    }

    if (liststart == NULL)
      /* first entry in list */
      liststart=listend=newentry;
    else {
      /* link new entry into list */
      listend->next = newentry;
      listend = newentry;

    }
    listend->value = val;
  }
  listend->next=NULL;
  return (liststart);
  
}

void visit_list(struct listrec *listptr)
{
  while(listptr != NULL) {
    printf("%d\n",listptr -> value);
    listptr = listptr -> next;
  } }

int main ()
{
  struct listrec  *liststart;
  liststart=build_list ();
  visit_list (liststart);

  return(0);
}

