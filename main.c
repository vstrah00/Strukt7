#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"


int main(){
    queue headOfQ={.leaf=NULL, .next=NULL};
    positionQ head=&headOfQ;
    Position root=NULL;
    Position newDir=NULL;
    Position temp=NULL;
    char input[30]={0};
    char order[6]={0};
    char command[30]={0};
    int check=0;
    int checkPush=0;

    root=makeDir("C:");
    checkPush=Push(head, root);
    if(checkPush<0){
        printf("Memory allocation error!\n");
        return -1;
    }

    while(1){
        temp=head->next->leaf;
        printf("\033[0;32m");
        printDirs(head->next);
        printf(">");
        printf("\033[0m");
        fgets(input, 50, stdin);
        check=sscanf(input, " %s %s", order, command);


        if(strcmp(order, "md")==0 && check==2){
            newDir=makeDir(command);
            if(newDir==NULL){
                printf("Allocation error!\n");
                return -1;
            }
        
            if(temp->child==NULL){
                temp->child=newDir;
            }
            else{
                temp=temp->child;
                while(temp!=NULL){
                    if(strcmp(temp->name, command)==0){         //osiguravamo da ne bude duplikata
                        printf("Directory already exists!\n");
                        free(newDir);
                        newDir=NULL;
                        break;
                    }
                    else{
                        if(temp->sibling!=NULL){
                            temp=temp->sibling;
                        }
                        else    
                            break;
                    }
                }
                if(newDir!=NULL){
                    temp->sibling=newDir;
                }
            }
        }


        else if(strcmp(order, "cd")==0 && check==2){
            if(temp->child==NULL){
                printf("No such directory!\n");
            }
            else{
                temp=temp->child;
                while(1){
                    if(temp==NULL){
                       printf("No such directory!\n");
                       break; 
                    }

                    if( strcmp(temp->name, command)==0 ){
                        checkPush=Push(head, temp);
                        if(checkPush<0){
                            printf("Memory allocation error!\n");
                            return -1;
                        }
                        break;
                    }
                    temp=temp->sibling;
                }
            }
        }


        else if(strcmp(order, "cd..")==0 && check==1){
            if(head->next->leaf!=root){
                Pop(head);
            }
        }


        else if(strcmp(order, "dir")==0 && check==1){
            temp=temp->child;
            if(temp==NULL){
                printf("Empty!\n");
            }
            else{
                printf("\nStored directories:\n");
                while(temp){
                    printf("<DIR>\t%s\n", temp->name);
                    temp=temp->sibling;
                }
                printf("\n");
            }
        }


        else if(strcmp(order, "exit")==0 && check==1){
            freeList(head);
            root=freeTree(root);
            return 0;
        }
        else
            printf("No such order!\n");
    }

    return 0;
}
