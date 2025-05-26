#include <stdio.h>
#include "trashbin.h"

void launch_trashbin() {
    clear_screen();
    printf("=== TrashBin ===\n");
    printf("TrashBin is empty.\n");
    printf("Press Enter to go back...");
    getchar();
}