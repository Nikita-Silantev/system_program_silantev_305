#include <stdio.h>
#include <stdlib.h>
#include "datastruct.h"

// ---- стек ----

void stack_init(Stack *s) {
    s->top = NULL;
    s->size = 0;
}

// новый узел становится вершиной, ссылается на старую вершину
void stack_push(Stack *s, int val) {
    StackNode *node = malloc(sizeof(StackNode));
    if (node == NULL) { printf("Error: no memory\n"); return; }
    node->data = val;
    node->next = s->top;
    s->top = node;
    s->size++;
}

// берём верхний узел, освобождаем его, возвращаем значение
int stack_pop(Stack *s) {
    if (stack_empty(s)) { printf("Error: stack is empty\n"); return -1; }
    StackNode *tmp = s->top;
    int val = tmp->data;
    s->top = tmp->next;
    free(tmp);
    s->size--;
    return val;
}

int stack_peek(Stack *s) {
    if (stack_empty(s)) return -1;
    return s->top->data;
}

int stack_empty(Stack *s) {
    return s->top == NULL;
}

void stack_free(Stack *s) {
    while (!stack_empty(s)) stack_pop(s);
}

// ---- очередь ----

void queue_init(Queue *q) {
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
}

// новый узел добавляется в хвост
void queue_push(Queue *q, int val) {
    QueueNode *node = malloc(sizeof(QueueNode));
    if (node == NULL) { printf("Error: no memory\n"); return; }
    node->data = val;
    node->next = NULL;
    if (q->back != NULL) q->back->next = node;
    q->back = node;
    if (q->front == NULL) q->front = node;   // первый элемент
    q->size++;
}

// забираем из головы
int queue_pop(Queue *q) {
    if (queue_empty(q)) { printf("Error: queue is empty\n"); return -1; }
    QueueNode *tmp = q->front;
    int val = tmp->data;
    q->front = tmp->next;
    if (q->front == NULL) q->back = NULL;   // очередь опустела
    free(tmp);
    q->size--;
    return val;
}

int queue_empty(Queue *q) {
    return q->front == NULL;
}

void queue_free(Queue *q) {
    while (!queue_empty(q)) queue_pop(q);
}

// ---- связный список ----

// добавляем в начало: новый узел ссылается на старый head
void list_push_front(ListNode **head, int val) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) { printf("Error: no memory\n"); return; }
    node->data = val;
    node->next = *head;
    *head = node;
}

// добавляем в конец: идём до последнего узла
void list_push_back(ListNode **head, int val) {
    ListNode *node = malloc(sizeof(ListNode));
    if (node == NULL) { printf("Error: no memory\n"); return; }
    node->data = val;
    node->next = NULL;
    if (*head == NULL) { *head = node; return; }
    ListNode *cur = *head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = node;
}

// удаляем первое вхождение значения, перешиваем указатели
void list_remove(ListNode **head, int val) {
    ListNode *cur = *head;
    ListNode *prev = NULL;
    while (cur != NULL) {
        if (cur->data == val) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

void list_print(ListNode *head) {
    ListNode *cur = head;
    while (cur != NULL) {
        printf("%d", cur->data);
        if (cur->next != NULL) printf(" -> ");
        cur = cur->next;
    }
    printf("\n");
}

void list_free(ListNode **head) {
    ListNode *cur = *head;
    while (cur != NULL) {
        ListNode *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    *head = NULL;
}
