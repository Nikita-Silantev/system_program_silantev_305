#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int id;
    char title[30];
    double value;
};

void print_record(struct Record *r) {
    printf("  [%d] %s = %.2f\n", r->id, r->title, r->value);
}

void double_value(struct Record *r) {
    r->value *= 2.0;
}

void halve_value(struct Record *r) {
    r->value /= 2.0;
}

typedef void (*RecordFunc)(struct Record *);

void apply_all(struct Record *arr, int count, RecordFunc fn) {
    for (int i = 0; i < count; i++) {
        fn(&arr[i]);
    }
}

void apply_then_show(struct Record *r,
                     RecordFunc transform,
                     void (*show)(struct Record *, RecordFunc, void (*)(struct Record *)),
                     void (*printer)(struct Record *)) {
    show(r, transform, printer);
}

void run_and_print(struct Record *r, RecordFunc fn, void (*printer)(struct Record *)) {
    fn(r);
    printer(r);
}

void write_binary(struct Record *arr, int count, const char *filename) {
    FILE *f = fopen(filename, "wb");
    if (f == NULL) {
        printf("Error: cannot open %s\n", filename);
        return;
    }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(arr, sizeof(struct Record), count, f);
    fclose(f);
    printf("Written %d records to %s\n", count, filename);
}

struct Record *read_binary(const char *filename, int *count) {
    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        printf("Error: cannot open %s\n", filename);
        return NULL;
    }
    fread(count, sizeof(int), 1, f);
    struct Record *arr = malloc(sizeof(struct Record) * (*count));
    if (arr == NULL) {
        printf("Error: malloc failed\n");
        fclose(f);
        return NULL;
    }
    fread(arr, sizeof(struct Record), *count, f);
    fclose(f);
    return arr;
}

int main(void) {
    printf("--- Memory: malloc / realloc / free ---\n");
    int n = 4;
    int *arr = malloc(sizeof(int) * n);
    if (arr == NULL) {
        printf("malloc failed\n");
        return 1;
    }
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 5;
    }
    printf("Array (%d): ", n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    n = 7;
    int *tmp = realloc(arr, sizeof(int) * n);
    if (tmp == NULL) {
        printf("realloc failed\n");
        free(arr);
        return 1;
    }
    arr = tmp;
    for (int i = 4; i < n; i++) {
        arr[i] = (i + 1) * 5;
    }
    printf("After realloc (%d): ", n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    free(arr);
    printf("Memory freed ok\n");

    printf("\n--- Records ---\n");
    int count = 3;
    struct Record *records = malloc(sizeof(struct Record) * count);
    if (records == NULL) {
        printf("malloc failed\n");
        return 1;
    }

    records[0].id = 1;
    strcpy(records[0].title, "Item One");
    records[0].value = 10.0;

    records[1].id = 2;
    strcpy(records[1].title, "Item Two");
    records[1].value = 25.5;

    records[2].id = 3;
    strcpy(records[2].title, "Item Three");
    records[2].value = 7.0;

    printf("Before:\n");
    apply_all(records, count, print_record);

    printf("\nDouble all:\n");
    apply_all(records, count, double_value);
    apply_all(records, count, print_record);

    printf("\n--- Function pointer chain ---\n");
    printf("Halve record[0] via 3-level chain:\n");
    apply_then_show(&records[0], halve_value, run_and_print, print_record);

    printf("\n--- Binary file ---\n");
    write_binary(records, count, "records.bin");
    free(records);

    int loaded_count = 0;
    struct Record *loaded = read_binary("records.bin", &loaded_count);
    if (loaded != NULL) {
        printf("Read back %d records:\n", loaded_count);
        apply_all(loaded, loaded_count, print_record);
        free(loaded);
        printf("Loaded memory freed ok\n");
    }

    return 0;
}
