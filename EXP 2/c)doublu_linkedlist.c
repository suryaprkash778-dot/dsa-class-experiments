#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node* next;
    struct node* prev;
}node;

node* create_node(int data){
    node* new_node = (node*)malloc(sizeof(node));
    new_node->data = data;
    new_node->next=NULL;
    new_node->prev=NULL;
    return new_node;
}

void insert_at_end(node** head,int data){
    node* new_node = create_node(data);
    if(*head==NULL){
        *head = new_node;
        return;
    }
    node* temp = *head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=new_node;
    new_node->prev=temp;
}

void display(node* head){
    if(head==NULL){
        printf("list is empty");
    }
    node* temp = head;
    do{
        printf("%d ",temp->data);
        temp=temp->next;
    }while(temp!=NULL);
    printf("\n");
}

void delete(node** head, int position) {
    if (*head == NULL) {
        printf("List is empty, nothing to delete\n");
        return;
    }

    node* temp = *head;

    // delete head node
    if (position == 0) {
        *head = temp->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
        free(temp);
        return;
    }

    // traverse to the node at given position
    for (int i = 0; temp != NULL && i < position; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of range\n");
        return;
    }

    // unlink the node safely
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }

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
    display(head);   // Output: 1 2 3 4
    delete(&head,3); // delete last node
    display(head);   // Output: 1 2 3
    delete(&head,0); // delete head
    display(head);   // Output: 2 3
    return 0;
}
