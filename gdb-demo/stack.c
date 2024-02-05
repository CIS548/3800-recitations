#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *below;
} Node;

void push(Node **top, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  *newNode = (Node){data, *top};
  *top = newNode;
}

Node *getMaxNode(Node *top) {
  if (top && top->below && top->data < top->below->data) {
    return getMaxNode(top->below);
  }
  return top;
}

int main() {
  printf("Demo!\n");
  Node *top = NULL;
  push(&top, 1);
  push(&top, 3);
  push(&top, 2);

  // Results
  Node *maxNode = getMaxNode(top);
  printf("Max: %d\n", maxNode->data);
  return 0;
}
