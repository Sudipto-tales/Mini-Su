#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "kernel.h"
#include "logo.h"
#include "power.h"

#ifdef _WIN32
#include <windows.h>
#endif

#define SHUTDOWN_DELAY 1
#define RESTART_DELAY 2
#define GOODBYE_DELAY 1
#define WARNING_DELAY 3

int show_file_with_delay(const char *filename, int delay);
void power_screen();
void power_off();
void restart();

void power_screen()
{
    int choice;

    while (1)
    {
        printf("\n=== Power Off Screen ===\n");
        printf("1. Shutdown\n");
        printf("2. Restart\n");
        printf("3. Cancel\n");
        printf("Enter your choice: ");

        if (scanf("%d%*c", &choice) != 1)
        {
            printf("Invalid input. Try again.\n");
            while (getchar() != '\n'); // flush input buffer
            continue;
        }

        switch (choice)
        {
        case 1:
            power_off();
            exit(0); // Exit after shutdown
        case 2:
            restart();
            return; // Return to caller (likely home screen)
        case 3:
            show_home(); // Return to home
            return;
        default:
            printf("Invalid option. Please select 1, 2, or 3.\n");
        }
    }
}

void power_off()
{
    if (!show_file_with_delay("shutdown.txt", SHUTDOWN_DELAY))
    {
        printf("Could not load shutdown file.\n");
        return;
    }

    lazy_print("\n\nGood Bye !!", GOODBYE_DELAY);
    lazy_print("\n\nDo Not Power off your System.....", WARNING_DELAY);
}

void restart()
{
    if (!show_file_with_delay("restart.txt", RESTART_DELAY))
    {
        printf("Could not load restart file.\n");
        return;
    }

    lazy_print("\n\nDo Not Power off your System.....", RESTART_DELAY);
    show_home();
}

int show_file_with_delay(const char *filename, int delay)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
        return 0;

    char line[512];
    while (fgets(line, sizeof(line), file))
    {
        lazy_print(line, delay);
    }

    fclose(file);
    return 1;
}
