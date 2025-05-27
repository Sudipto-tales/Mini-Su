#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "clock.h"
#include "functions.h"
#include "config.h"
#include "textpad.h"


void show_notes_directory() {
    DIR *dr = opendir("Notes");
    if (!dr) {
        printf("Error: Could not open Notes directory.\n");
        return;
    }

    printf("=== Files in Notes Directory ===\n");
    struct dirent *de;
    while ((de = readdir(dr)) != NULL) {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("- %s\n", de->d_name);
        }
    }
    closedir(dr);
}

void launch_textpad() {
    clear_screen();
    print_digital_clock_header();
    ensure_notes_directory();
    show_notes_directory();

    printf("\n=== TextPad ===\n");
    printf("Enter filename with extension (e.g., program.c, notes.html): ");
    
    char filename[256];
    fgets(filename, sizeof(filename), stdin);

    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    if (strlen(filename) == 0) {
        printf("❌ Invalid filename. Returning to menu.\n");
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    // Create full path
    char fullpath[300];
    snprintf(fullpath, sizeof(fullpath), "Notes/%s", filename);

    FILE *file = fopen(fullpath, "w");
    if (!file) {
        printf("❌ Error: Unable to write to file %s\n", fullpath);
        printf("Press Enter to continue...");
        getchar();
        return;
    }

    printf("Start typing content. Type `exit` on a new line to save and return.\n\n");

    char line[1024];
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strncmp(line, "exit", 4) == 0 && (line[4] == '\n' || line[4] == '\0')) {
            break;
        }
        fputs(line, file);
    }

    fclose(file);
    printf("\n✅ File saved as: %s\n", fullpath);
    printf("Press Enter to return...");
    getchar();
}
