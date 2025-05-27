#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MUSIC_DIR "Music"
#define MAX_FILES 100
#define MAX_FILENAME_LEN 256

// Function to list music files and store them in the provided array
int list_music_files(char files[][MAX_FILENAME_LEN]) {
    DIR *dir = opendir(MUSIC_DIR);
    if (dir == NULL) {
        perror("Error opening Music directory");
        return 0;
    }

    struct dirent *entry;
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < MAX_FILES) {
        if (strstr(entry->d_name, ".mp3") || strstr(entry->d_name, ".wav")) {
            strncpy(files[count], entry->d_name, MAX_FILENAME_LEN - 1);
            files[count][MAX_FILENAME_LEN - 1] = '\0';  // Null-terminate
            count++;
        }
    }

    closedir(dir);
    return count;
}

// Function to play a music file using OS-specific command
void play_music_file(const char *filename) {
    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", MUSIC_DIR, filename);

    printf("\n▶ Playing: %s\n", fullpath);

    char command[600];

#ifdef _WIN32
    snprintf(command, sizeof(command), "start \"\" \"%s\"", fullpath);
#elif __APPLE__
    snprintf(command, sizeof(command), "open \"%s\" >/dev/null 2>&1", fullpath);
#else
    snprintf(command, sizeof(command), "xdg-open \"%s\" >/dev/null 2>&1", fullpath);
#endif

    system(command);
}

// Function to display the list of music files
void show_song_list(char files[][MAX_FILENAME_LEN], int count) {
    printf("\n🎵 Available Songs:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, files[i]);
    }
}

// Function to play all songs with user interaction
void play_all_songs() {
    char files[MAX_FILES][MAX_FILENAME_LEN];
    int count = list_music_files(files);

    if (count == 0) {
        printf("No music files found in '%s' directory.\n", MUSIC_DIR);
        return;
    }

    int current = 0;
    char input[50];

    while (current < count) {
        play_music_file(files[current]);

        printf("\nNext song? (y/n), enter number to jump, or 'exit': ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Trim newline

        if (strcmp(input, "exit") == 0) {
            break;
        } else if (strcmp(input, "y") == 0 || strlen(input) == 0) {
            current++;
        } else {
            int jump = atoi(input);
            if (jump >= 1 && jump <= count) {
                current = jump - 1;
            } else {
                printf("Invalid input. Skipping to next song.\n");
                current++;
            }
        }
    }

    printf("\nMusic session ended. Press Enter to return...");
    getchar();
}

// Function to play a specific song
void play_specific_song() {
    char files[MAX_FILES][MAX_FILENAME_LEN];
    int count = list_music_files(files);

    if (count == 0) {
        printf("No music files found in '%s' directory.\n", MUSIC_DIR);
        return;
    }

    show_song_list(files, count);

    printf("\nEnter song number to play: ");
    int choice;
    if (scanf("%d%*c", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid selection.\n");
        while (getchar() != '\n');
        return;
    }

    play_music_file(files[choice - 1]);

    printf("\nPress Enter to return...");
    getchar();
}

// Entry function to run music player menu
void play_music() {
    while (1) {
        printf("\n=== 🎶 MUSIC PLAYER ===\n");
        printf("1. Play All Songs\n");
        printf("2. Play a Specific Song\n");
        printf("3. Exit\n");
        printf("Choose an option: ");

        int option;
        if (scanf("%d%*c", &option) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (option) {
            case 1:
                play_all_songs();
                break;
            case 2:
                play_specific_song();
                break;
            case 3:
                printf("Goodbye!\n");
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
