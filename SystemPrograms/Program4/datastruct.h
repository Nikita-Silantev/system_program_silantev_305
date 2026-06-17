#ifndef DATASTRUCT_H
#define DATASTRUCT_H

// ---- стек (LIFO) ----
// узел стека хранит данные и указатель на следующий узел
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// стек: указатель на вершину и текущий размер
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

// ---- очередь (FIFO) ----
typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

// очередь: указатель на голову (front) и хвост (back)
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

// ---- односвязный список ----
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
