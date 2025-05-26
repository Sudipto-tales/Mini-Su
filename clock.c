#include <stdio.h>
#include <time.h>
#include <string.h>
#include "kernel.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// Big digits representation (3 lines per digit)
const char *digits[10][3] = {
    {" __ ", "|  |", "|__|"}, // 0
    {"    ", "   |", "   |"}, // 1
    {" __ ", " __|", "|__ "}, // 2
    {" __ ", " __|", " __|"}, // 3
    {"    ", "|__|", "   |"}, // 4
    {" __ ", "|__ ", " __|"}, // 5
    {" __ ", "|__ ", "|__|"}, // 6
    {" __ ", "   |", "   |"}, // 7
    {" __ ", "|__|", "|__|"}, // 8
    {" __ ", "|__|", " __|"}  // 9
};

void print_big_digit(char ch, int line) {
    if (ch >= '0' && ch <= '9') {
        printf("%s", digits[ch - '0'][line]);
    } else if (ch == ':') {
        // Colon pattern (blinking can be implemented)
        if (line == 0) printf("  ");
        else if (line == 1) printf(" .");
        else if (line == 2) printf(" .");
    } else {
        printf("    ");
    }
}

void launch_clock() {
    int show_colon = 1;

    while (1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        clear_screen();
        printf("=== Digital Clock ===\n\n");

        // Format time as HH:MM:SS
        char time_str[9];
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

        // Print each line of big digits
        for (int line = 0; line < 3; line++) {
            for (int i = 0; i < strlen(time_str); i++) {
                if (time_str[i] == ':') {
                    // Blink colon every second
                    if (show_colon)
                        print_big_digit(':', line);
                    else
                        printf("  ");
                } else {
                    print_big_digit(time_str[i], line);
                }
                printf("  "); // spacing between digits
            }
            printf("\n");
        }

        printf("\nPress Ctrl+C to exit clock.\n");

        show_colon = !show_colon; // toggle colon visibility for blinking effect

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }
}
