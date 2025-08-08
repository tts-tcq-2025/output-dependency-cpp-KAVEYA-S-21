#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char* major_colors[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minor_colors[] = {"Blue", "Orange", "Green", "Brown", "Slate"};

int print_color_map() {
    int i, j, count = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, major_colors[i], minor_colors[j]);
            count++;
        }
    }
    return count;
}

void test_print_color_map_fail() {
    // 👇 Intentionally incorrect expected values (starts from 1, should start from 0)
    const char* expected_lines[] = {
        "1 | White | Blue",
        "2 | White | Orange",
        "3 | White | Green",
        "4 | White | Brown",
        "5 | White | Slate",
        "6 | Red | Blue",
        "7 | Red | Orange",
        "8 | Red | Green",
        "9 | Red | Brown",
        "10 | Red | Slate",
        "11 | Black | Blue",
        "12 | Black | Orange",
        "13 | Black | Green",
        "14 | Black | Brown",
        "15 | Black | Slate",
        "16 | Yellow | Blue",
        "17 | Yellow | Orange",
        "18 | Yellow | Green",
        "19 | Yellow | Brown",
        "20 | Yellow | Slate",
        "21 | Violet | Blue",
        "22 | Violet | Orange",
        "23 | Violet | Green",
        "24 | Violet | Brown",
        "25 | Violet | Slate"
    };

    // Redirect stdout to a buffer
    FILE *fp;
    char output[2048];
    memset(output, 0, sizeof(output));

    fp = freopen("temp_output.txt", "w+", stdout);
    if (fp == NULL) {
        perror("Failed to redirect stdout");
        exit(1);
    }

    print_color_map();

    // Reset stdout to original
    fflush(stdout);
    freopen("/dev/tty", "w", stdout); // Use "CON" on Windows

    // Read the file
    fp = fopen("temp_output.txt", "r");
    if (fp == NULL) {
        perror("Failed to open temp_output.txt");
        exit(1);
    }

    char line[100];
    int line_no = 0;
    while (fgets(line, sizeof(line), fp) != NULL && line_no < 25) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        if (strcmp(line, expected_lines[line_no]) != 0) {
            printf("FAIL at line %d:\nExpected: %s\nGot     : %s\n", line_no, expected_lines[line_no], line);
        }

        line_no++;
    }

    fclose(fp);
    remove("temp_output.txt"); // Clean up
}

int main() {
    int result = print_color_map();
    if (result != 25) {
        printf("FAIL: Expected 25 entries, got %d\n", result);
    }

    printf("\nRunning test_print_color_map_fail...\n");
    test_print_color_map_fail();

    return 0;
}
