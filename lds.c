#include <stdio.h>
#include <malloc.h>

struct node{
    int data;
    struct node *next;
};

struct Stack{
    struct node *top;
};
void push(struct Stack *s, int data);
int pop(struct Stack *s);
int peek(struct Stack s);
int is_stackEmpty(struct Stack s);
void display_stack(struct Stack s);

void push(struct Stack *s, int data){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if(s->top == NULL)
        s->top = newNode;
    else{
        newNode->next = s->top;
        s->top = newNode;
    }
}

int pop(struct Stack *s){
    if(s->top == NULL)
        return -1;

    int ret = s->top->data;
    struct node *topop = s->top;
    s->top = s->top->next;
    free(topop);
    return ret;
}

int peek(struct Stack s){
    if(s.top == NULL)
        return -1;
    return s.top->data;
}

int is_stackEmpty(struct Stack s){
    if(s.top == NULL)
        return 1;   //  true
    return 0;    // false
}

void display_stack(struct Stack s){
    if(s.top == NULL){
        printf("The stack is empty!");
        return;
    }
    else{
        struct node *ptr = s.top;
        while(ptr != NULL){
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
    }
}

struct Queue{
    struct node *front, *rear;
};
void enqueue(struct Queue *q, int data);
int dequeue(struct Queue *q);
int front(struct Queue q);
int rear(struct Queue q);
int is_queueEmpty(struct Queue q); 
void display_queue(struct Queue q);

void enqueue(struct Queue *q, int data){
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if(q->rear == NULL)
        q->front = q->rear = newNode;
    else{
        q->rear->next = newNode;
        q->rear = q->rear->next;
    }
}

int dequeue(struct Queue *q){
    if(q->front == NULL)
        return -1;

    int ret = q->front->data;
    struct node *todequeue = q->front;
    q->front = q->front->next;
    free(todequeue);
    return ret;
}

int front(struct Queue q){
    if(q.front == NULL)
        return -1;
    return q.front->data;
}

int rear(struct Queue q){
    if(q.rear == NULL)
        return -1;
    return q.rear->data;
}

int is_queueEmpty(struct Queue q){
    if(q.front == NULL || q.rear == NULL)
        return 1;   //  true
    return 0;   //  false

}

void display_queue(struct Queue q){
    if(q.front == NULL || q.rear == NULL){
        printf("The queue is empty!");
        return;
    }
    else{
        struct node *ptr = q.front;
        while(ptr != NULL){
            printf("%d ", ptr->data);
            ptr = ptr->next;
        }
    }
}


//  This main was used to test the above functions
// int main(int argc, char const *argv[])
// {
//     struct Stack s = {NULL};
//     push(&s, 1);
//     push(&s, 2);
//     push(&s, 3);
//     printf("%d\n", pop(&s));
//     push(&s, 4);
//     display_stack(s);

//     printf("\n\n");

//     struct Queue q = {NULL, NULL};
//     enqueue(&q, 1);
//     enqueue(&q, 2);
//     enqueue(&q, 3);
//     printf("%d\n", dequeue(&q));
//     enqueue(&q, 4);
//     display_queue(q);

//     return 0;
// }
