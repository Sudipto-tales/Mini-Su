#include <stdio.h>
#include <time.h>
#include <string.h>
#include "kernel.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define TIME_STR_LEN 9
#define DIGIT_LINES 3

// Big digits representation (3 lines per digit)
const char *digits[10][DIGIT_LINES] = {
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

// Colon representation for each line
const char *colon[DIGIT_LINES] = {"  ", " .", " ."};

// Prints a single big digit or colon
void print_big_digit(char ch, int line, int show_colon)
{
    if (ch >= '0' && ch <= '9')
    {
        printf("%s", digits[ch - '0'][line]);
    }
    else if (ch == ':')
    {
        printf("%s", show_colon ? colon[line] : "  ");
    }
    else
    {
        printf("    ");
    }
}

// Launch the animated digital clock
void launch_clock()
{
    int show_colon = 1;

    while (1)
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);

        clear_screen();
        printf("=== Digital Clock ===\n\n");

        char time_str[TIME_STR_LEN];
        snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

        for (int line = 0; line < DIGIT_LINES; line++)
        {
            for (size_t i = 0; i < strlen(time_str); i++)
            {
                print_big_digit(time_str[i], line, show_colon);
                printf("  ");
            }
            printf("\n");
        }

        printf("\nPress Ctrl+C to exit clock.\n");

        show_colon = !show_colon;

#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }
}

// Print static digital clock header (no blinking)
void print_digital_clock_header()
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char time_str[TIME_STR_LEN];
    snprintf(time_str, sizeof(time_str), "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

    for (int line = 0; line < DIGIT_LINES; line++)
    {
        for (size_t i = 0; i < strlen(time_str); i++)
        {
            print_big_digit(time_str[i], line, 1); // Always show colon
            printf("  ");
        }
        printf("\n");
        Sleep(1);
    }
    printf("\n");
}