# Lab 3

## Lists

### Exercises

Using the following type definitions:

```c
typedef struct node {
    node *next;
    int value;
} node;

typedef node *list;
```

#### Exercise 1, Beginner

Implement all the most common functions:

- Insertion of a node `void insert(list *list, int value)`
- Deletion of a node `int removeAt(list *list, int index)` (that also returns the value at index `index`)

#### Exercise 2, Intermediate

Implement a function `void insertOrdered(list *list, int value)` that expects to have an ordered list as a first parameter and inserts the new value in the correct place to keep the list ordered

