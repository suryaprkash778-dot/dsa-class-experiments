#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node* next;
}node;

node* create_node(int data){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next=NULL;
    return new_node;
}

void insert_at_end(node** head,int data){
    node* new_node = create_node(data);
    if(*head==NULL){
        new_node->next=new_node;
        *head = new_node;
        return;
    }
    node* temp = *head;
    while(temp->next!=*head){
        temp=temp->next;
    }
    temp->next=new_node;
    new_node->next=*head;
}

void display(node* head){
    if(head==NULL){
        printf("list is empty");
    }
    node* temp = head;
    do{
        printf("%d ",temp->data);
        temp=temp->next;
    }while(temp!=head);
    printf("\n");
}

void delete(node** head, int position) {
    if (*head == NULL) {
        printf("List is empty, nothing to delete\n");
        return;
    }

    node* temp = *head;
    node* prev = NULL;

    // delete head node
    if (position == 0) {
        // find last node
        while (temp->next != *head) {
            temp = temp->next;
        }
        node* to_delete = *head;
        temp->next = (*head)->next;
        *head = (*head)->next;
        free(to_delete);
        return;
    }

    // delete non-head node
    temp = *head;
    for (int i = 0; i < position; i++) {
        prev = temp;
        temp = temp->next;
        if (temp == *head) {
            printf("Position out of range\n");
            return;
        }
    }
    prev->next = temp->next;
    free(temp);
}


int search(node** head,int target,int list_length){
    if(*head==NULL){
        printf("list is empty, nothing to search");
    }
    node* temp = *head;
    for(int i=0;i<list_length;i++){
        if(temp->data==target){
            return i;
        }
        temp=temp->next;
    }
    return -1;
}

int main(){
    node* head=NULL;
    insert_at_end(&head,1);
    insert_at_end(&head,2);
    insert_at_end(&head,3);
    insert_at_end(&head,4);
    display(head);
    delete(&head,3);
    display(head);
    return 0;
}
