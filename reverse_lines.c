/* Code snippet to illiustate
   dymamic memory allocation in C  using
   malloc and calloc */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX   100

main()
{
  char *linetab[MAX],buf[257];
  int i;

  for(i=0;i <= MAX && gets(buf) != NULL;i++) {
    linetab[i] = malloc (strlen(buf) + 1);

    if (linetab[i] == NULL) {
        printf("Malloc failed \n");
	exit(EXIT_FAILURE);	}


    strcopy(linetab[i],buf);
  }

  /* now print out the lines in reverse order */

  while (--i >= 0)
    printf("%s\n",linetab[i]);

  exit(EXIT_SUCCESS);

}
