#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

//prototype of methods
int numNodes(struct Node* root_ref);
bool isFullUtil(struct Node* root_ref);
bool isFull(struct Node* root_ref);
void boolToStr(bool val);
int numLevels(struct Node* root_ref);
void displayUtil(struct Node* root_ref, int space);
void display(struct Node* root_ref);
struct Node* newNode(int ndata);
char* ask(char things[], int len);
void addNodeUtil(struct Node* root_ref, int new_data);
void addNode(struct Node* root_ref);
int searchUtil(struct Node* root_ref, int value, int number);
void clear(struct Node* root_ref);
void removeNodeUtil(struct Node* root_ref, int value, bool remov, struct Node* prev);
void removeNode(struct Node* root_ref);
int wrapUtil(struct Node* root);
char* wrap(struct Node* root);
void binaryTree();


int numNodes(struct Node* root_ref)
{
  static int counter = 1;
  if(root_ref == NULL) return 0;
  if(root_ref->left != NULL)
  {
    counter++;
    numNodes(root_ref->left);
  }
  if(root_ref->right != NULL)
  {
    counter++;
    numNodes(root_ref->right);
  }
  return counter;
}

bool isFullUtil(struct Node* root_ref)
{
  static bool full = true;

  if(root_ref->left != NULL)
  {
    full = isFullUtil(root_ref->left);
  }
  if(root_ref->right != NULL)
  {
    full = isFullUtil(root_ref->right);
  }

  if(!((root_ref->left != NULL && root_ref->right != NULL) || (root_ref->left == NULL && root_ref->right == NULL)))
  {
    full = false;
    return false;
    printf("done\n");
  }

  return full;
}

bool isFull(struct Node* root_ref)
{
  if(numNodes(root_ref) % 2 != 1) return false;
  return isFullUtil(root_ref);
}

void boolToStr(bool val)
{
  if(val == true) {
    printf("true\n");
  } else {
    printf("false\n");
  }
}

int numLevels(struct Node* root_ref)
{
  return ((int) (log10(numNodes(root_ref))/log10(2)));
}

void displayUtil(struct Node* root_ref, int space)
{
  if(root_ref == NULL) return;

  space += 10;

  displayUtil(root_ref->right, space);

  printf("\n");
  for(int i = 10; i < space; i++)
    printf(" ");
  printf("%d\n", root_ref->data);

  displayUtil(root_ref->left, space);
  // int spaces1 = (((int) (log10(numNodes(root_ref))/log10(2)))*5) + 5;
}

void display(struct Node* root_ref)
{
  printf("+------------------------------------------+");
  displayUtil(root_ref, 0);
}


struct Node* newNode(int ndata)
{
  struct Node* node = (struct Node*)malloc(sizeof(struct Node));

  node->data = ndata;

  node->left = NULL;
  node->right = NULL;
  return(node);
}

char* ask(char things[], int len)
{
  int tries = 0;
  do {
      if(fgets(things, len, stdin) == NULL) {
          exit(1);
      }
      tries++;
  } while(strchr(things, '\n') == NULL);
  // printf("%s\n", things);
  if(tries != 1) {
    printf("Your entry was too long\n");
    printf("Try again: ");
    ask(things, len);
  }
  return things;
}

void addNodeUtil(struct Node* root_ref, int new_data)
{
  if(new_data <= root_ref->data) {
    if(root_ref->left == NULL) {
      root_ref->left = newNode(new_data);
    } else {
      addNodeUtil(root_ref->left, new_data);
    }
  } else if(new_data > root_ref->data) {
    if(root_ref->right == NULL) {
      root_ref->right = newNode(new_data);
    } else {
      addNodeUtil(root_ref->right, new_data);
    }
  }
}

void addNode(struct Node* root_ref)
{
  char nodeVal[12];
  int val;
  printf("Enter new node value [Max 10 char]: ");
  val = atoi(ask(nodeVal,12));
  printf("%d\n", val);
  addNodeUtil(root_ref, val);
  printf("Note: root added automatically\n");
}

int searchUtil(struct Node* root_ref, int value, int number)
{
  if(root_ref->data == value) {
    number++;
  }
  if(root_ref->left != NULL) number += searchUtil(root_ref->left, value, number);
  if(root_ref->right != NULL) number += searchUtil(root_ref->right, value, number);
  return number;
}

void search(struct Node* root_ref)
{
  char nodeVal[12];
  int val;
  printf("Enter node value to search [Max 10 char]: ");
  val = atoi(ask(nodeVal,12));
  // printf("%d\n", searchUtil(root_ref, val, 0));
  boolToStr(searchUtil(root_ref, val, 0) > 0);
}

void clear(struct Node* root_ref)
{
  if(root_ref->right != NULL) {
    // root_ref->right = newNode(0);
    removeNodeUtil(root_ref->right, root_ref->right->data, true, root_ref->right);
  }
  if(root_ref->left != NULL) {
    // root_ref->left = newNode(0);
    removeNodeUtil(root_ref->left, root_ref->left->data, false, root_ref->left);
  }
  root_ref->left = NULL;
  root_ref->right = NULL;
}

void removeNodeUtil(struct Node* root_ref, int value, bool remov, struct Node* prev)
{
  static bool left;
  if(root_ref->left != NULL && root_ref->left->data == value){
    prev = root_ref;
    left = true;
  } else if(root_ref->right != NULL && root_ref->right->data == value) {
    prev = root_ref;
    left = false;
  }
  if(root_ref->data == value) {
    remov = true;
  }
  if(root_ref->left != NULL) removeNodeUtil(root_ref->left, value, remov, prev);
  if(root_ref->right != NULL) removeNodeUtil(root_ref->right, value, remov, prev);
  if(remov) {
    // printf("value of node deleted : %d\n", root_ref->data);
    root_ref->left = NULL;
    root_ref->right = NULL;
    if(left) prev->left = NULL;
    if(!left) prev->right = NULL;
    free(root_ref);
    prev->data = 0;
  }
}

void removeNode(struct Node* root_ref)
{
  char nodeVal[12];
  int val;
  printf("Note that the first instance of the node with the inputed value will be deleted.\n");
  printf("Enter node value [Max 10 char]: ");
  val = atoi(ask(nodeVal,12));
  printf("%d\n", val);
  if(val == root_ref->data) {
    printf("You cannot delete the root of the binary tree.\n");
  } else if(!(searchUtil(root_ref, val, 0) > 0)) {
    printf("Value not found in binary tree\n");
  } else {
    removeNodeUtil(root_ref, val, false, root_ref);
    printf("Note: root deleted\n");
  }
}

int wrapUtil(struct Node* root)
{
////look at last option of possible user inputed
//basically this is not finished yet
}

char* wrap(struct Node* root)
{
  char* seed;
  sprintf(seed, "%d", root->data);
  printf("%s\n", seed);
  return seed;
}

void binaryTree()
{
  struct Node *root;// = newNode(1);

  // root->left = newNode(2);
  // root->right = newNode(3);
  //
  // root->left->left = newNode(4);
  // root->left->right = newNode(5);
  char roots[12];
  // printf("%zu\n", sizeof(roots));
  int rooti;
  printf("Enter root value [Max 10 char]: ");
  rooti = atoi(ask(roots, sizeof(roots)));
  printf("%d\n", rooti);
  root = newNode(rooti);

  //test
  root->right = newNode(5);
  root->left = newNode(2);
  root->left->left = newNode(1);
  root->left->right = newNode(3);
  root->left->right->right = newNode(4);
  root->left->right->left = newNode(3);
  // addNodeUtil(root, 6);
  // addNodeUtil(root, 7);
  // addNodeUtil(root, 6);
  // addNodeUtil(root, 5);

  while(true)
  {
    char things[3];
    char *thing;
    printf("Please choose an option: add(a), remove(r), search(s), display horizontally(d), check if full(f), save(v), clear except root(c) [Max 1 char]: ");
    thing = ask(things, 3);
    printf("%c\n", thing[0]);

    if(thing[0] == 'd') {
      printf("This is the display of your binary tree horizontally\n");
      display(root);
    } else if(thing[0] == 'a') {
      addNode(root);
    } else if(thing[0] == 'r') {
      removeNode(root);
    } else if (thing[0] == 's') {
      search(root);
    } else if (thing[0] == 'f') {
      printf("Full binary tree: ");
      boolToStr((isFull(root)));
    } else if (thing[0] == 'c') {
      printf("clearing\n");
      clear(root);
      printf("DONE\n");
    } else if (thing[0] == 'v') {
      ///NOT DONE
      FILE *fp;
      fp = fopen ("filename.csv","w+");
      if (fp!=NULL)
      {
        fprintf(fp,"Some String\n");
        fclose (fp);
      }
    } else {
      printf("Invalid input\n");
    }

  }

  // printf("%d\n", numLevels(root));
  // display(root);
  boolToStr((isFull(root)));
}

// int main() //uncomment for production of single c file
// {
//   binaryTree();
//   return 0;
// }
