#ifndef JSON_UTILS
#define JSON_UTILS

#define FILENAME "out/data.json"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void json_begin() {
    FILE *file = fopen(FILENAME, "w");
    fprintf(file, "{\n");
    fclose(file);
}

void json_end() {
    FILE *file = fopen(FILENAME, "a");
    fprintf(file, "}\n");
    fclose(file);
}

void json_begin_time(int n) {
    FILE *file = fopen(FILENAME, "a");
    fprintf(file, "\t\"%d\": {\n", n);
    fclose(file);
}

void json_end_time(bool last) {
    FILE *file = fopen(FILENAME, "a");
    if (!last) fprintf(file, "\t},\n");
    else fprintf(file, "\t}\n");
    fclose(file);
}

void json_save_times(int *times, int t, char *label, bool last) {
    FILE *file = fopen(FILENAME, "a");

    fprintf(file, "\t\t\"%s\": [", label);
    for (int i = 0; i < t; i++) {
        fprintf(file, "%d", times[i]);
        if (i < t - 1) fprintf(file, ", ");
    }
    if (!last) fprintf(file, "],\n");
    else fprintf(file, "]\n");
    fclose(file);
}

#endif