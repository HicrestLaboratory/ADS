#include <stdlib.h>

typedef struct node {
  struct node *next;
  int value;
} node;

typedef node *list;

void insert(list *list, int value);
int removeAt(list *list, int index);
void insertOrdered(list *list, int value);

int main() { return EXIT_SUCCESS; }

void insert(list *inlist, int value) {
  if (!inlist) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = NULL;
    *inlist = newNode;
    return;
  }
  return insert(&(*inlist)->next, value);
}

int removeAt(list *inlist, int index) {
  if (index == 0) {
    list temp = *inlist;
    *inlist = (*inlist)->next;
    int result = (temp)->value;
    free(temp);
    return result;
  }

  return removeAt(&(*inlist)->next, index - 1);
}

void insertOrdered(list *inlist, int value) {
  if (!inlist || (*inlist)->value > value) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->value = value;
    newNode->next = *inlist;
    *inlist = newNode;
    return;
  }

  return insertOrdered(&(*inlist)->next, value);
}
