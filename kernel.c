#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "kernel.h"
#include "logo.h"
#include "textpad.h"
#include "clock.h"
#include "music.h"
#include "power.h"

#include "functions.h"
#include "config.h"

void show_home()
{
    clear_screen();
    show_home_banner();
    print_digital_clock_header();

    printf("\n\n=== %s Home ===\n\n", OS_NAME);
    printf("1. Open TextPad\n");
    printf("2. Show Clock\n");
    printf("3. Play Music\n");
    printf("4. Exit\n");
}

void start_kernel()
{
    int choice;

    while (1)
    {
        show_home();
        choice = get_user_choice("Choose option: ", 1, 4);

        switch (choice)
        {
        case 1:
            launch_textpad();
            break;
        case 2:
            launch_clock();
            break;
        case 3:
            play_music();
            break;
        case 4:
            power_screen();
            break;
        }
    }
}
