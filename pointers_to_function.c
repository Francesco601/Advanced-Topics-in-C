/* Program to illustrate the use
   of pointers to function and dispatch
   tables in C */


#include <stdio.h>
#include <string.h>


struct command  {
  char *name;
  int (*function) (void);
};

int addentry();
int calcvals();
int delentry();
int listdb();
int quit();
int updentry();


// dispatch table
struct command dispatch[] = {
  { "add", addentry  },
  { "calc", calcvals  },
  { "delete", delentry },
  { "list", listdb  },
  { "quit",  quit },
  { "update", updentry }
};

/* function prototype */
int execute(char *,struct command *,int);

#define UNKNOWNCMD  -1
#define QUITCMD  999
#define OKCMD   0

  
int execute(char *typedcmd,struct command dispatch[],int numcmds)
{
  int i,fnresult=UNKNOWNCMD;

  for(i=0;i < numcmds;i++) {
    if(strcmp(typedcmd,dispatch[i].name) == 0) {
      fnresult = (*dispatch[i].function) ();
      break;
    }}
  return (fnresult);

}

void main() {

  char buf[81];
  int status;
  int addentry (void),calcvals (void),delentry (void),listdb (void),
    quit (void), updentry (void);

  int entries = sizeof(dispatch) / sizeof (struct command);

  do {
    printf("\n Enter your command: ");
    scanf("%s",buf);
    status = execute(buf,dispatch,entries);

    if(status == UNKNOWNCMD)
      printf("Unknown command: %s\n",buf);

  } while(status != QUITCMD);
}

/* dummy functions for testing */
int addentry (void) {
  printf("in addentry\n");
  return OKCMD; }

int calcvals (void) {
  printf("in calcvals\n");
  return OKCMD; }

int delentry (void) {
  printf("in delentry\n");
  return OKCMD; }

int listdb (void) {
    printf("in listdb\n");
    return OKCMD; }

int quit (void) {
    printf("in quit\n");
    return QUITCMD; }
int updentry (void) {
    printf("in updentry\n");
    return OKCMD; }

  

  

  
