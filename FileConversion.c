#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// Function to convert file to upper case
void convert_to_upper_case(const char* file_path) {
    FILE* file = fopen(file_path, "r+");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {
        fputc(toupper(c), file);
    }

    fclose(file);
}

int main() {
    // File sizes to test
    int file_sizes[] = {200, 400, 600, 800, 1000};  // MB

    // Perform conversion for each file size
    int num_sizes = sizeof(file_sizes) / sizeof(file_sizes[0]);
    for (int i = 0; i < num_sizes; i++) {
        int size = file_sizes[i];
        char file_path[20];
        sprintf(file_path, "input_%dmb.txt", size);

        // Create text file of given size (filled with random characters)
        FILE* file = fopen(file_path, "w");
        if (file == NULL) {
            perror("Failed to create file");
            continue;
        }
        for (int j = 0; j < size * 1024 * 1024; j++) {
            fputc('a', file);
        }
        fclose(file);

        // Measure execution time
        clock_t start_time = clock();
        convert_to_upper_case(file_path);
        clock_t end_time = clock();

        // Calculate and print execution time
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("File size: %dMB, Execution time: %.2f seconds\n", size, execution_time);
    }

    return 0;
}
