#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

Position makeDir(char newName[25]){
    Position newDir=NULL;

    newDir=(Position)malloc(sizeof(cvor));
    if(newDir==NULL){
        return NULL;
    }

    strcpy(newDir->name, newName);
    newDir->sibling=NULL;
    newDir->child=NULL;

    return newDir;
}

int Push(positionQ head, Position current){
    positionQ newEl=NULL;

    newEl=(positionQ)malloc(sizeof(queue));
    if(newEl==NULL){
        return -1;
    }

    newEl->next=head->next;
    head->next=newEl;

    newEl->leaf=current;

    return 0;
}

int Pop(positionQ head){
    positionQ temp=NULL;

    if(head->next!=NULL){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    return 0;
}

int freeList(positionQ head){
    positionQ temp=NULL;
    while(head->next){
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    return 0;
}

Position freeTree(Position root){
    if(root==NULL){
        return NULL;
    }
    else if(root->child){
        root->child=freeTree(root->child);
    }
    else if(root->sibling){
        root->sibling=freeTree(root->sibling);
    }
    free(root);
    return NULL;
}


int printDirs(positionQ afterHead){
    if(afterHead->next){
        printDirs(afterHead->next);
    }
    printf("%s\\", afterHead->leaf->name);
    return 0;
}
