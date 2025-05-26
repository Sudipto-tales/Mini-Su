#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "textpad.h"

void launch_textpad() {
    clear_screen();
    directory();
    printf("=== TextPad ===\n");
    printf("Type something (type 'exit' to save & return):\n");

    char filename[256];
    printf("Enter filename to save your note (without extension): ");
    fgets(filename, sizeof(filename), stdin);
    // Remove trailing newline
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }

    // Build full file path
    char fullpath[300];
    snprintf(fullpath, sizeof(fullpath), "Notes/%s.txt", filename);

    FILE *file = fopen(fullpath, "w");
    if (!file) {
        printf("Error opening file %s!\n", fullpath);
        printf("Press Enter to return...");
        getchar();
        return;
    }

    char line[256];
    while (1) {
        fgets(line, sizeof(line), stdin);
        if (strncmp(line, "exit", 4) == 0 && (line[4] == '\n' || line[4] == '\0')) break;
        fprintf(file, "%s", line);
    }

    fclose(file);
    printf("Note saved to %s\n", fullpath);
    printf("Press Enter to return...");
    getchar();
}

void directory() {
    struct dirent *de;
    DIR *dr = opendir("Notes");  // Use "Notes" if you want to list files in that folder

    if (dr == NULL) {
        printf("Error !! Could Not Open Directory\n");
        return;
    }

    printf("=== Files in Notes Directory ===\n");
    while ((de = readdir(dr)) != NULL) {
        // Skip "." and ".."
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            printf("%s\n", de->d_name);
        }
    }

    closedir(dr);
}
