#include <stdio.h>
#include <dlfcn.h>       // dlopen, dlsym, dlclose
#include "datastruct.h"  // наши структуры данных из статической/динамической библиотеки

// путь к плагину передаётся через Makefile флагом -DPLUGIN_FILE
// если собирать вручную без Makefile — используется значение по умолчанию
#ifndef PLUGIN_FILE
    #define PLUGIN_FILE "./libplugin.so"
#endif

int main(void) {
    // --- стек: LIFO, последним пришёл — первым ушёл ---
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

    // --- очередь: FIFO, первым пришёл — первым ушёл ---
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

    // --- связный список ---
    printf("\n--- Linked list ---\n");
    ListNode *list = NULL;
    list_push_back(&list, 10);
    list_push_back(&list, 20);
    list_push_back(&list, 30);
    list_push_front(&list, 5);   // добавляем в начало
    printf("List: ");
    list_print(list);
    list_remove(&list, 20);
    printf("After remove 20: ");
    list_print(list);
    list_free(&list);

    // --- линковка во время выполнения через dlopen ---
    printf("\n--- Runtime linking (dlopen) ---\n");

    // открываем динамическую библиотеку по пути; RTLD_LAZY — символы ищем при первом обращении
    void *handle = dlopen(PLUGIN_FILE, RTLD_LAZY);
    if (handle == NULL) {
        printf("dlopen error: %s\n", dlerror());
    } else {
        // получаем адреса функций по имени
        void (*hello)(void)  = dlsym(handle, "plugin_hello");
        int  (*add)(int,int) = dlsym(handle, "plugin_add");

        if (hello) hello();
        if (add)   printf("plugin_add(3, 4) = %d\n", add(3, 4));

        dlclose(handle);   // выгружаем библиотеку из памяти
        printf("Plugin unloaded\n");
    }

    return 0;
}
