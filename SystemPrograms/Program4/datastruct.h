#ifndef DATASTRUCT_H
#define DATASTRUCT_H

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} Stack;

void stack_init(Stack *s);
void stack_push(Stack *s, int val);
int  stack_pop(Stack *s);
int  stack_peek(Stack *s);
int  stack_empty(Stack *s);
void stack_free(Stack *s);

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *back;
    int size;
} Queue;

void queue_init(Queue *q);
void queue_push(Queue *q, int val);
int  queue_pop(Queue *q);
int  queue_empty(Queue *q);
void queue_free(Queue *q);

typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode;

void list_push_front(ListNode **head, int val);
void list_push_back(ListNode **head, int val);
void list_remove(ListNode **head, int val);
void list_print(ListNode *head);
void list_free(ListNode **head);

#endif
