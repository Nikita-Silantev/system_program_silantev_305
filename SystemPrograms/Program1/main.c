#include <stdio.h>
#include <string.h>

int main(void) {
    char name[50];
    int age, choice, i;
    int arr[5];
    int sum = 0;
    char upper[50];

    // --- линейный ввод-вывод ---
    printf("Enter your name: ");
    scanf("%49s", name);   // 49 чтобы не выйти за границу массива
    printf("Enter your age: ");
    scanf("%d", &age);

    printf("\nHello, %s! You are %d years old.\n", name, age);

    // --- ветвление if / else if / else ---
    if (age >= 18) {
        printf("You are adult.\n");
    } else if (age >= 13) {
        printf("You are teen.\n");
    } else {
        printf("You are child.\n");
    }

    // --- выбор switch ---
    printf("\nEnter day number (1-7): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: printf("Monday\n");    break;
        case 2: printf("Tuesday\n");   break;
        case 3: printf("Wednesday\n"); break;
        case 4: printf("Thursday\n");  break;
        case 5: printf("Friday\n");    break;
        case 6: printf("Saturday\n");  break;
        case 7: printf("Sunday\n");    break;
        default: printf("Wrong number\n");
    }

    // --- массивы + цикл for ---
    printf("\nEnter 5 numbers:\n");
    for (i = 0; i < 5; i++) {
        printf("  arr[%d] = ", i);
        scanf("%d", &arr[i]);
        sum += arr[i];   // считаем сумму на ходу
    }
    printf("Sum = %d\n", sum);
    printf("Average = %d\n", sum / 5);

    // поиск максимума через for
    for (i = 1; i < 5; i++) {
        if (arr[i] > arr[0]) {
            arr[0] = arr[i];
        }
    }
    printf("Max = %d\n", arr[0]);

    // --- цикл while: обратный отсчёт ---
    printf("\nCount down:\n");
    i = 5;
    while (i > 0) {
        printf("%d ", i);
        i--;
    }
    printf("\n");

    // --- строки ---
    printf("\nName length: %zu\n", strlen(name));

    // перевод в верхний регистр вручную: разница между 'a' и 'A' равна 32
    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            upper[i] = name[i] - 32;
        } else {
            upper[i] = name[i];
        }
    }
    upper[i] = '\0';   // завершаем строку
    printf("Upper: %s\n", upper);

    return 0;
}
