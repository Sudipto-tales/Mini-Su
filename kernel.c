#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kernel.h"
#include "logo.h"
#include "textpad.h"
#include "trashbin.h"
#include "clock.h"
#include "music.h"


void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void play_music();
void show_home() {
    clear_screen();
    show_home_banner();
    printf("\n\n=== Mini OS Home ===\n\n");
    printf("1. Open TextPad\n");
    printf("2. Open TrashBin\n");
    printf("3. Show Clock\n");
    printf("4. Play Music\n");
    printf("5. Exit\n");
    printf("Choose option: ");
}

void start_kernel() {

    while (1) {
        show_home();

        int choice = 0;
        scanf("%d%*c", &choice);

        if (choice == 1) {
            launch_textpad();
        } else if (choice == 2) {
            launch_trashbin();
        } else if (choice == 3) {
            launch_clock();
        } else if (choice == 4) {
            play_music();
        } else if (choice == 5) {
            break;
        } else {
            printf("Invalid option.\n");
        }

    }

    printf("Goodbye!\n");
}
