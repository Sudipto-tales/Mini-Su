#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "functions.h"
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int get_user_choice(const char *prompt, int min, int max)
{
    int choice;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d%*c", &choice) == 1 && choice >= min && choice <= max)
            return choice;
        printf("Invalid input. Try again.\n");
        while (getchar() != '\n'); // flush
    }
}

void ensure_notes_directory() {
    struct stat st = {0};
    if (stat("Notes", &st) == -1) {
#ifdef _WIN32
        mkdir("Notes");
#else
        mkdir("Notes", 0755);
#endif
    }
}
