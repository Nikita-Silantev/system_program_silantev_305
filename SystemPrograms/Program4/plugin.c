#include <stdio.h>

void plugin_hello(void) {
    printf("Hello from plugin (runtime linking)!\n");
}

int plugin_add(int a, int b) {
    return a + b;
}
