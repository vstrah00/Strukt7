#ifndef DECLARATIONS_H
#define DECLARATIONS_H

struct Stablo;
typedef struct Stablo* Position;
typedef struct Stablo{
    char name[25];
    Position sibling;
    Position child;
}cvor;

struct Queue;
typedef struct Queue* positionQ;
typedef struct Queue{
    Position leaf;
    positionQ next;
}queue;

Position makeDir(char newName[25]);
int Pop(positionQ head);
int Push(positionQ head, Position current);
int freeList(positionQ head);
Position freeTree(Position root);
int printDirs(positionQ afterHead);

#endif