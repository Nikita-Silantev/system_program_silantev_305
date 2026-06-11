#include <stdio.h>
#include <dlfcn.h>
#include "datastruct.h"

#ifndef PLUGIN_FILE
    #define PLUGIN_FILE "./libplugin.so"
#endif

int main(void) {
    printf("--- Stack ---\n");
    Stack s;
    stack_init(&s);
    stack_push(&s, 10);
    stack_push(&s, 20);
    stack_push(&s, 30);
    printf("Top = %d\n", stack_peek(&s));
    printf("Pop: %d\n", stack_pop(&s));
    printf("Pop: %d\n", stack_pop(&s));
    printf("Size = %d\n", s.size);
    stack_free(&s);

    printf("\n--- Queue ---\n");
    Queue q;
    queue_init(&q);
    queue_push(&q, 1);
    queue_push(&q, 2);
    queue_push(&q, 3);
    printf("Pop: %d\n", queue_pop(&q));
    printf("Pop: %d\n", queue_pop(&q));
    printf("Size = %d\n", q.size);
    queue_free(&q);

    printf("\n--- Linked list ---\n");
    ListNode *list = NULL;
    list_push_back(&list, 10);
    list_push_back(&list, 20);
    list_push_back(&list, 30);
    list_push_front(&list, 5);
    printf("List: ");
    list_print(list);
    list_remove(&list, 20);
    printf("After remove 20: ");
    list_print(list);
    list_free(&list);

    printf("\n--- Runtime linking (dlopen) ---\n");
    void *handle = dlopen(PLUGIN_FILE, RTLD_LAZY);
    if (handle == NULL) {
        printf("dlopen error: %s\n", dlerror());
    } else {
        void (*hello)(void)  = dlsym(handle, "plugin_hello");
        int  (*add)(int,int) = dlsym(handle, "plugin_add");
        if (hello) hello();
        if (add)   printf("plugin_add(3, 4) = %d\n", add(3, 4));
        dlclose(handle);
        printf("Plugin unloaded\n");
    }

    return 0;
}
