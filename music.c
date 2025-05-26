#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define MUSIC_DIR "Music"

void list_music_files(char files[][256], int *count)
{
    DIR *dr = opendir(MUSIC_DIR);
    if (dr == NULL)
    {
        printf("Error! Could not open %s directory.\n", MUSIC_DIR);
        *count = 0;
        return;
    }

    struct dirent *de;
    *count = 0;
    while ((de = readdir(dr)) != NULL)
    {
        if (strstr(de->d_name, ".mp3") || strstr(de->d_name, ".wav"))
        {
            strncpy(files[*count], de->d_name, 255);
            files[*count][255] = '\0'; // safety null terminate
            (*count)++;
            if (*count >= 100)
                break; // max 100 files
        }
    }
    closedir(dr);
}

void play_music_file(const char *filename)
{
    char fullpath[300];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", MUSIC_DIR, filename);

    printf("Playing %s...\n", fullpath);
    char command[350];
    // Change "play" to the appropriate player for your OS
    snprintf(command, sizeof(command), "start \"\" \"%s\"", fullpath);
    system(command);
}

void play_music()
{
    char files[100][256];
    int count = 0;

    list_music_files(files, &count);

    if (count == 0)
    {
        printf("No music files found in the %s directory.\n", MUSIC_DIR);
        return;
    }

    printf("=== Music Files ===\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i + 1, files[i]);
    }

    int current = 0;
    char input[50];
    while (current < count)
    {
        play_music_file(files[current]);

        printf("\nPlaying next file? (y/n), or enter number to jump to file, or 'exit' to quit: ");
        fgets(input, sizeof(input), stdin);
        // Remove trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0)
        {
            break;
        }
        else if (strcmp(input, "y") == 0 || strcmp(input, "Y") == 0 || strlen(input) == 0)
        {
            // play next file
            current++;
        }
        else
        {
            int choice = atoi(input);
            if (choice >= 1 && choice <= count)
            {
                current = choice - 1; // jump to selected file
            }
            else
            {
                printf("Invalid input, continuing with next file.\n");
                current++;
            }
        }
    }

    printf("Music playback ended.\n");
    printf("Press Enter to return...");
    getchar();
}
