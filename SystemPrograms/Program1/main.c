#include <stdio.h>
#include <string.h>

int main(void) {
    char name[50];
    int age, choice, i;
    int arr[5];
    int sum = 0;
    char upper[50];

    printf("Enter your name: ");
    scanf("%49s", name);
    printf("Enter your age: ");
    scanf("%d", &age);

    printf("\nHello, %s! You are %d years old.\n", name, age);

    if (age >= 18) {
        printf("You are adult.\n");
    } else if (age >= 13) {
        printf("You are teen.\n");
    } else {
        printf("You are child.\n");
    }

    printf("\nEnter day number (1-7): ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: printf("Monday\n"); break;
        case 2: printf("Tuesday\n"); break;
        case 3: printf("Wednesday\n"); break;
        case 4: printf("Thursday\n"); break;
        case 5: printf("Friday\n"); break;
        case 6: printf("Saturday\n"); break;
        case 7: printf("Sunday\n"); break;
        default: printf("Wrong number\n");
    }

    printf("\nEnter 5 numbers:\n");
    for (i = 0; i < 5; i++) {
        printf("  arr[%d] = ", i);
        scanf("%d", &arr[i]);
        sum += arr[i];
    }
    printf("Sum = %d\n", sum);
    printf("Average = %d\n", sum / 5);

    printf("\nMax = %d\n", arr[0]);
    for (i = 1; i < 5; i++) {
        if (arr[i] > arr[0]) {
            arr[0] = arr[i];
        }
    }
    printf("Max after loop = %d\n", arr[0]);

    printf("\nCount down:\n");
    i = 5;
    while (i > 0) {
        printf("%d ", i);
        i--;
    }
    printf("\n");

    printf("\nName length: %zu\n", strlen(name));
    for (i = 0; name[i] != '\0'; i++) {
        if (name[i] >= 'a' && name[i] <= 'z') {
            upper[i] = name[i] - 32;
        } else {
            upper[i] = name[i];
        }
    }
    upper[i] = '\0';
    printf("Upper: %s\n", upper);

    return 0;
}
