#include<stdio.h>
#include<stdlib.h>
typedef struct node{
    int data ;
    struct node* next;
}node;
node *createnode(int data){
    node *newnode = (node*)malloc(sizeof(node));
    newnode->data=data;
    newnode->next=NULL;
    return newnode;
}
void insert_at_end(int data,node** head){
    node *new_node=createnode(data);
    if(*head==NULL){
        *head=new_node;
    }else{
        node *temp = *head;
        while(temp->next!=NULL){
            temp=temp->next;
        }
        temp->next = new_node;
    }
}
void insert_at_beginnig(int data,node** head){
    node *new_node = createnode(data);
    new_node->next = head;
    *head = new_node; 
}
void print_list(node* head){
    node *temp = head;
    while(temp!=NULL){
            printf("%d ",temp->data);
            temp=temp->next;
        }
}
int main(){
    int size,data;
    node *head = NULL;
    printf("how many nodes you want to add");
    scanf("%d",&size);
    printf("enter data in linked list\n");
    for(int i=0;i<size;i++){
        scanf("%d",&data);
        insert_at_end(data,&head);
    }
    print_list(head);
    return 0;
}
