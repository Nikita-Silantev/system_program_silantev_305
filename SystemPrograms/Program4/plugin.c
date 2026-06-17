#include <stdio.h>

// этот файл компилируется в отдельную динамическую библиотеку (.dylib / .so)
// main.c загружает её во время выполнения через dlopen — без знания о ней на этапе сборки

void plugin_hello(void) {
    printf("Hello from plugin (runtime linking)!\n");
}

int plugin_add(int a, int b) {
    return a + b;
}
