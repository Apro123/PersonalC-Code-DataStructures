#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include "binarytree.c"

#define MAX_INDIV 100
#define MAX_STR_LEN 20

typedef struct {
  int Family_ID;
  int Individual_ID;
  char* Name;
} my_record;

my_record records[MAX_INDIV];
int num_indiv;
char* filename;
struct Node* Familytree;
struct Node* Individualtree;


//prototype of functions
void read(char* filenamess);
char* setup(char filenames[]);
void printFileContents();
void addElement(char* filename);
void mainMenu();


void read(char* filenamess)
{
  FILE *fp = fopen(filenamess,"r");

  //allocation for buffer for each line
  char* buf = malloc(MAX_STR_LEN);
  char* tmp;
  clear(Familytree);
  clear(Individualtree);

  int i = 0;
  while(fgets(buf, 99, fp) != NULL)
  {
    if ((strlen(buf)>0) && (buf[strlen (buf) - 1] == '\n'))
      buf[strlen (buf) - 1] = '\0';

    tmp = strtok(buf, ",");
    records[i].Family_ID = atoi(tmp);
    addNodeUtil(Familytree, atoi(tmp));

    tmp = strtok(NULL, ",");
    records[i].Individual_ID = atoi(tmp);
    addNodeUtil(Individualtree, atoi(tmp));

    tmp = strtok(NULL, ";");
    records[i].Name = strdup(tmp);

    free(buf);
    buf = malloc(MAX_STR_LEN);
    i++;
  }
  // printFileContents();
  num_indiv = i;
  fclose(fp);
}

void printFileContents()
{
  printf("-------------------------------------------------------\n");
  printf("Current number of Individuals in database: %d\n", num_indiv);
  for (int i = 0; i <= sizeof(records); i++)
  {
    if (records[i].Family_ID != 0)
      printf("index i= %i  Family_ID: %d; Individual_ID: %d; Name: %s\n",i, records[i].Family_ID , records[i].Individual_ID, records[i].Name);
    else
      break;
  }
  printf("-------------------------------------------------------\n");
}

void addElement(char* filename)
{
  // printf("%zu\n", sizeof(records)); 1600
  // printf("%d\n", num_indiv); works correctly
  // printf("%s\n", filename); the full filename
  int Family_ID, Individual_ID;
  char* Name;
  char Family_ID_STR[22], Individual_ID_STR[22], Name_STR[22];
  char person_details[65];
  bool ok = true;

  printf("Enter Family_ID [Max 20 char]: ");
  Family_ID = atoi(ask(Family_ID_STR, 22));
  printf("Entered Family_ID: %d\n", Family_ID);

  printf("Enter Individual_ID [Max 20 char]: ");
  Individual_ID = atoi(ask(Individual_ID_STR, 22));
  printf("Entered Individual_ID: %d\n", Individual_ID);

  printf("Enter Name of Individual [Max 20 char]: ");
  Name = ask(Name_STR, 22);
  printf("Entered Name: %s", Name);

  //check if Invalid

  for (int i = 0; i <= sizeof(records); i++)
  {
    if (records[i].Family_ID != 0) {
      ok = false;
      if(records[i].Family_ID == Family_ID) { //can have the same family id but not the same individual id
          if(records[i].Individual_ID == Individual_ID) { //can have same individual id if the family id is different
              printf("Invalid Individual_ID [Already exists within Family_ID]\n");
          } else {
            ok = true;
          }
      } else if(Family_ID == 0) {
          printf("Family ID cannot be '0'\n");
      } else {
        ok = true;
      }
      if(!ok) { //stops if error
        break;
      }
    }
    else
      break;
  }

  //add everything to the String
  sprintf(person_details, "%d,%d,", Family_ID, Individual_ID);
  strncat(person_details, Name, 22);
  printf("%s", person_details);

  // ok = false; //comment for production
  if(ok) {
    FILE *fp;
    fp = fopen (filename,"a");
    if (fp!=NULL)
    {
      printf("sdrger\n");
      fprintf(fp,"%s",person_details);
      fclose (fp);
    }

    printf("Person details added\n");
  }
}

char* setup(char filenames[]) //char*
{
  char anss[3]; //used for first choice
  char *ans;
  char *filenameTmp;
  printf("Do you want to create a new csv (database) file? (Y/N) [default is N]: ");
  ans = ask(anss, 3);
  printf("Answer: %s", ans);
  bool yes;
  // printf("%s\n", ans);
  if(ans[0] == 'Y' || ans[0] == 'y') {
    printf("Enter filename for new csv file [Max 20 char]: ");
    yes = true;
  } else {
    printf("What csv file do you want to open. Enter filename [Max 20 char]: ");
    yes = false;
  }
  filenameTmp = ask(filenames, 22);
  FILE *csvFile;
  filenameTmp[strlen(filenameTmp) - 1] = 0; //strip newline
  filenameTmp = strncat(filenames,".csv", 4);
  printf("Filename: %s\n",filenameTmp);
  if(yes) { //uncomment for production
    csvFile = fopen (filenameTmp,"w+");
    // fprintf(csvFile,"Family ID,Individual ID,Name\n");
    fclose (csvFile);
  }
  // free(ans);
  return filenameTmp;
}

void searchPeople()
{
  char anss[22];
  int ans;
  printf("Enter Family_ID or Individual_ID to see if person exists: ");
  ans = atoi(ask(anss,22));
  printf("Family_ID: ");
  if(searchUtil(Familytree, ans, 0)) {
    printf("exists\n");
  } else {
    printf("doesn't exist\n");
  }
  printf("Individual_ID: ");
  if(searchUtil(Individualtree, ans, 0)) {
    printf("exists\n");
  } else {
    printf("doesn't exist\n");
  }
}

void mainMenu()
{
  read(filename);

  printf("Do you want to list contents of the file ('r'), or add element ('a'), or search for element('s'), or quit('q') [Default is 'q']: ");
  char anss[3];
  char *ans;
  ans = ask(anss, 3);

  if(ans[0] == 'A' || ans[0] == 'a') {
    addElement(filename);
  } else if(ans[0] == 'S' || ans[0] == 's') {
    searchPeople();
  } else if(ans[0] == 'R' || ans[0] == 'r'){
    printFileContents();
  } else {
    exit(0);
  }

  mainMenu();
}

int main()
{
  char filenames[22];
  // char* filename;
  filename = setup(filenames);

  Familytree = newNode(0);
  Individualtree = newNode(0);
  // read(filename);

  mainMenu(filename);
  return 0;
}
