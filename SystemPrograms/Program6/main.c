#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>   // va_list, va_start, va_arg, va_end

// --- вариадические функции ---
// "..." означает что функция принимает любое количество аргументов
// count — обязательный первый параметр, он говорит сколько аргументов ждать

// сумма count целых чисел
int va_sum(int count, ...) {
    va_list args;
    va_start(args, count);   // инициализируем список аргументов после count
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);   // берём следующий аргумент как int
    }
    va_end(args);   // обязательно закрываем список
    return total;
}

// максимум из count целых чисел
int va_max(int count, ...) {
    va_list args;
    va_start(args, count);
    int max = va_arg(args, int);   // первый аргумент — начальный максимум
    for (int i = 1; i < count; i++) {
        int val = va_arg(args, int);
        if (val > max) max = val;
    }
    va_end(args);
    return max;
}

// печатает count строк
void va_print_all(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        printf("  [%d] %s\n", i, va_arg(args, char *));
    }
    va_end(args);
}

// логгер с форматом как у printf
// vprintf принимает уже готовый va_list — это стандартный способ пробросить аргументы дальше
void va_log(const char *level, const char *fmt, ...) {
    printf("[%s] ", level);
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);   // передаём va_list в стандартную функцию
    va_end(args);
    printf("\n");
}

// печатает подсказку по использованию программы
void print_usage(const char *prog) {
    printf("Usage:\n");
    printf("  %s sum <n1> <n2> ...    sum of numbers\n", prog);
    printf("  %s max <n1> <n2> ...    max of numbers\n", prog);
    printf("  %s print <w1> <w2> ...  print all words\n", prog);
    printf("  %s demo                 run built-in demo\n", prog);
}

// встроенное демо всех вариадических функций
void run_demo(void) {
    printf("--- Variadic: sum ---\n");
    printf("sum(1,2,3)       = %d\n", va_sum(3, 1, 2, 3));
    printf("sum(10,20,30,40) = %d\n", va_sum(4, 10, 20, 30, 40));

    printf("\n--- Variadic: max ---\n");
    printf("max(5,1,9,3)     = %d\n", va_max(4, 5, 1, 9, 3));
    printf("max(100,200,50)  = %d\n", va_max(3, 100, 200, 50));

    printf("\n--- Variadic: print strings ---\n");
    va_print_all(4, "apple", "banana", "cherry", "date");

    printf("\n--- Variadic: custom log (uses vprintf) ---\n");
    va_log("INFO",  "Program started, pid = %d", 1234);
    va_log("WARN",  "Value is too big: %d", 9999);
    va_log("ERROR", "File not found: %s", "data.txt");
}

// --- обработка параметров командной строки ---
// argc — количество аргументов (включая имя программы)
// argv — массив строк: argv[0] — имя программы, argv[1] — первый аргумент и т.д.
int main(int argc, char *argv[]) {
    printf("--- Command line args ---\n");
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }
    printf("\n");

    // если нет аргументов — показываем подсказку
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }

    if (strcmp(argv[1], "demo") == 0) {
        run_demo();
        return 0;
    }

    if (argc < 3) {
        printf("Error: need at least one number or word\n");
        print_usage(argv[0]);
        return 1;
    }

    // количество чисел/слов = все аргументы минус программа и команда
    int count = argc - 2;

    if (strcmp(argv[1], "sum") == 0) {
        printf("Sum of %d numbers:\n", count);
        int total = 0;
        for (int i = 2; i < argc; i++) {
            int n = atoi(argv[i]);   // atoi конвертирует строку в int
            printf("  + %d\n", n);
            total += n;
        }
        printf("Result = %d\n", total);
        // демонстрируем va_sum на первых трёх аргументах
        printf("\nSame via va_sum(3 args): %d\n",
               va_sum(3, atoi(argv[2]), atoi(argv[3 < argc ? 3 : 2]), atoi(argv[4 < argc ? 4 : 2])));
    }
    else if (strcmp(argv[1], "max") == 0) {
        printf("Max of %d numbers:\n", count);
        int max = atoi(argv[2]);
        for (int i = 2; i < argc; i++) {
            int n = atoi(argv[i]);
            printf("  %d\n", n);
            if (n > max) max = n;
        }
        printf("Result = %d\n", max);
    }
    else if (strcmp(argv[1], "print") == 0) {
        printf("Words (%d):\n", count);
        for (int i = 2; i < argc; i++) {
            printf("  [%d] %s\n", i - 2, argv[i]);
        }
    }
    else {
        printf("Error: unknown command \"%s\"\n", argv[1]);
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
