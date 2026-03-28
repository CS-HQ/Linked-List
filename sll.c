#include<stdio.h>
#include<stdlib.h>
#define NDEBUG
#include <assert.h>

assert(newnode != NULL);
struct node {
    int data;
    struct node * next;
};

void add_at_beg(struct node **head_ref, int data){
    struct node *newnode;
     
    newnode=malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=*head_ref;
    *head_ref=newnode;
}

void add_at_end(struct node ** head_ref, int data){
    struct node *newnode;
    newnode=malloc(sizeof(struct node));

    struct node * temp=* head_ref;// review difference b/w head_ref, *head_ref and **head_ref in this line
    while(temp->next!=NULL){
        temp=temp->next;
    }
    newnode->data=data;
    newnode->next=NULL;
    temp->next=newnode;
}

void add_at_pos(struct node ** head_ref, int data, int pos){
    struct node * temp= * head_ref;
    int count=1;
    while(count!=pos-1){
         temp=temp->next;
         count++;
    }
    struct node * newnode;
    newnode=malloc(sizeof(struct node));
    newnode->data=data;
    newnode->next=temp->next;
    temp->next=newnode;
  
}

void reverse(struct node **head_ref){
    struct node * previous, *current, *nextnode;

    current = *head_ref;
    previous=current;
    current=current->next;
    nextnode=current->next;
    previous->next=NULL;
 while(nextnode->next!=NULL){
    current->next=previous;
    previous=current;
    current=nextnode;
    nextnode=nextnode->next;
 }
 current->next=previous;
 nextnode->next=current;
 *head_ref = nextnode;
}

void delete_from_beg(struct node **head){
    struct node * temp=*head;
    *head=temp->next;
    free(temp);
}

void delete_from_end(struct node **head){
    struct node * temp=*head;
    while(temp->next->next!=NULL){
        temp=temp->next;
    }
    struct node * temp1= temp->next->next;
    temp->next=NULL;
    free(temp1);
   
}

void delete_pos(struct node **head, int pos){
    struct node * temp = * head;
    int count =1;
    while(count !=pos-1){
        temp=temp->next;
        count++;
    }

    struct node * temp1= temp->next;
    temp->next= temp->next->next;
    free(temp1);
}

    void display(struct node * head){
        struct node * temp= head; // review why *head needed wny not head
        while(temp!=NULL){
            printf("[%d]-> ",temp->data);
            temp=temp->next;
        }
        printf("NULL\n");
    }
 void menu(){
    printf("Actions: \n");
    printf("1. Add A Node \n");
    printf("2. Delete A Node \n");

 }


int main(){
    struct node * head = NULL;
    int choice;
    while(1){
        printf("Actions: \n");
    }

    
    add_at_beg(&head,0);
    add_at_end(&head, 4);
    //add_at_pos(&head, 10,4);
    display(head);
    reverse(&head);// should we use &head or just head here
    display(head);
    delete_from_beg(&head);
    display(head);
    delete_from_end(&head);
    display(head);
    delete_pos(&head,2);
    display(head);

    return 0;


}