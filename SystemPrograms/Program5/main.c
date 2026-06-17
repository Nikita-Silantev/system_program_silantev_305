#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>      // open, O_CREAT, O_WRONLY и т.д.
#include <unistd.h>     // read, write, close, lseek, dup
#include <dirent.h>     // opendir, readdir, closedir
#include <sys/stat.h>   // stat, S_ISDIR, S_ISREG
#include <sys/types.h>

// --- рекурсивные функции ---

// база: n <= 1 возвращает 1, иначе n * factorial(n-1)
int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

// база: n <= 1 возвращает n
int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// рекурсивная сумма массива: берём первый элемент и рекурсируем на остаток
int sum_recursive(int *arr, int size) {
    if (size == 0) return 0;
    return arr[0] + sum_recursive(arr + 1, size - 1);
}

// рекурсивный обход каталога с отступами по глубине
void walk_dir(const char *path, int depth) {
    DIR *d = opendir(path);
    if (d == NULL) return;

    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        // пропускаем "." и ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        // отступ по глубине вложенности
        for (int i = 0; i < depth; i++) printf("  ");

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0 && S_ISDIR(st.st_mode)) {
            printf("[dir] %s\n", entry->d_name);
            walk_dir(fullpath, depth + 1);   // рекурсия в подкаталог
        } else {
            printf("[file] %s\n", entry->d_name);
        }
    }
    closedir(d);
}

// рекурсивный подсчёт файлов в каталоге и всех подкаталогах
int count_files_recursive(const char *path) {
    DIR *d = opendir(path);
    if (d == NULL) return 0;

    int count = 0;
    struct dirent *entry;
    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[512];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == 0) {
            if (S_ISREG(st.st_mode))       count++;                             // обычный файл
            else if (S_ISDIR(st.st_mode))  count += count_files_recursive(fullpath);  // каталог
        }
    }
    closedir(d);
    return count;
}

int main(void) {
    // --- работа с файловыми дескрипторами ---
    // open возвращает целочисленный дескриптор (fd), не FILE*
    printf("--- File descriptor: open / write / close ---\n");
    int fd = open("test.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) { printf("Error: open failed\n"); return 1; }
    printf("File opened, fd = %d\n", fd);

    const char *line1 = "Line one\n";
    const char *line2 = "Line two\n";
    const char *line3 = "Line three\n";
    write(fd, line1, strlen(line1));
    write(fd, line2, strlen(line2));
    write(fd, line3, strlen(line3));
    close(fd);
    printf("Written 3 lines, file closed\n");

    // --- чтение через дескриптор ---
    printf("\n--- open / read ---\n");
    fd = open("test.txt", O_RDONLY);
    if (fd >= 0) {
        char buf[256];
        int n = read(fd, buf, sizeof(buf) - 1);
        buf[n] = '\0';
        printf("Read %d bytes:\n%s", n, buf);
        close(fd);
    }

    // --- произвольный доступ через lseek ---
    printf("\n--- lseek: random access ---\n");
    fd = open("test.txt", O_RDONLY);
    if (fd >= 0) {
        // перемещаемся на 9 байт от начала файла и читаем 8 байт
        lseek(fd, 9, SEEK_SET);
        char buf[20];
        int n = read(fd, buf, 8);
        buf[n] = '\0';
        printf("Read from offset 9: \"%s\"\n", buf);

        // lseek до конца файла возвращает размер
        off_t size = lseek(fd, 0, SEEK_END);
        printf("File size = %lld bytes\n", (long long)size);
        close(fd);
    }

    // --- дублирование дескриптора через dup ---
    // dup создаёт новый дескриптор, который указывает на тот же файл
    // оба дескриптора разделяют одну позицию чтения
    printf("\n--- dup: copy file descriptor ---\n");
    fd = open("test.txt", O_RDONLY);
    if (fd >= 0) {
        int fd2 = dup(fd);
        printf("fd = %d, dup fd = %d\n", fd, fd2);
        char buf[10];
        read(fd,  buf, 5); buf[5] = '\0'; printf("Read via fd:  \"%s\"\n", buf);
        read(fd2, buf, 5); buf[5] = '\0'; printf("Read via dup: \"%s\"\n", buf);
        close(fd);
        close(fd2);
    }

    // --- рекурсия ---
    printf("\n--- Recursion ---\n");
    printf("factorial(7) = %d\n", factorial(7));
    printf("fibonacci(9) = %d\n", fibonacci(9));
    int arr[] = {1, 2, 3, 4, 5};
    printf("sum of {1,2,3,4,5} = %d\n", sum_recursive(arr, 5));

    // --- интерфейс каталогов ---
    printf("\n--- Directory listing ---\n");
    DIR *d = opendir(".");
    if (d != NULL) {
        struct dirent *entry;
        printf("Entries in current dir:\n");
        while ((entry = readdir(d)) != NULL) {
            if (entry->d_name[0] == '.') continue;   // скрытые файлы пропускаем
            printf("  %s\n", entry->d_name);
        }
        closedir(d);
    }

    // --- рекурсивный обход дерева каталогов ---
    printf("\n--- Recursive walk ---\n");
    walk_dir(".", 0);

    int total = count_files_recursive(".");
    printf("\nTotal files found: %d\n", total);

    return 0;
}
