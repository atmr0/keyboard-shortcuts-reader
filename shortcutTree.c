#include <stdlib.h>

typdef struct node {
  char *keystroke;
  void (*function)();
  int isLeaf;
  struct node *continuations;
} Node;



