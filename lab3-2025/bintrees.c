#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
  int key;
  struct node *parent;
  struct node *left;
  struct node *right;
} node;

typedef node *bintree;

node *createNode(int value);
int read(node *node);
void write(node *node, int value);
node *parent(node *node);
node *left(node *node);
node *right(node *node);
void insertLeft(node *inode, node *child);
void insertRight(node *inode, node *child);
void deleteLeft(node *inode);
void deleteRight(node *inode);
void preOrder(node *inode);
void inOrder(node *inode);
void postOrder(node *inode);
int minDepth(node *inode);

int main() { return EXIT_SUCCESS; }

node *createNode(int value) {
  node *newNode = (node *)malloc(sizeof(node));
  newNode->key = value;
  newNode->parent = newNode->left = newNode->right = NULL;
  return newNode;
}

int read(node *node) {
  return node->key;
}

void write(node *node, int value) {
  node->key = value;
}

node *parent(node *node) {
  return node->parent;
}

node *left(node *node) {
  return node->left;
}

node *right(node *node) {
  return node->right;
}

void insertLeft(node *inode, node *child) {
  if (!inode->left) inode->left = child;
}

void insertRight(node *inode, node *child) {
  if (!inode->right) inode->right = child;
}

void deleteBoth(node *inode) {
  if (!inode) {
    deleteBoth(inode->left);
    deleteBoth(inode->right);

    free(inode);
  }
}

void deleteLeft(node *inode) {
  if (inode) {
    deleteBoth(inode->left);
  }
}

void deleteRight(node *inode) {
  if (inode) {
    deleteBoth(inode->right);
  }
}

void preOrder(node *inode) {
  if (!inode) return;

  preOrder(inode->left);
  preOrder(inode->right);
  printf("%d ", inode->key);
}

void inOrder(node *inode) {
  if (!inode) return;

  inOrder(inode->left);
  inOrder(inode->right);
  printf("%d ", inode->key);
}

void postOrder(node *inode) {
  if (!inode) return;

  printf("%d ", inode->key);
  postOrder(inode->left);
  postOrder(inode->right);
}

typedef struct minDepthInfo {
  int val;
  int depth;
} minDepthInfo;

minDepthInfo minDepthHelper(node *inode) {
  if (!inode) {
    minDepthInfo res;
    res.val = INT_MAX;
    return res;
  }
  
  minDepthInfo leftInfo = minDepthHelper(inode->left);
  leftInfo.depth++;
  minDepthInfo rightInfo = minDepthHelper(inode->right);
  rightInfo.depth++;

  minDepthInfo res = leftInfo;
  if (rightInfo.val < res.val) {
    res = rightInfo;
  }
  if (inode->key < res.val) {
    res.val = inode->key;
    res.depth = 0;
  }

  return res;
}

int minDepth(node *inode) {
  return minDepthHelper(inode).depth;
}
