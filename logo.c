#include <stdio.h>
#include <unistd.h>
#ifdef _WIN32
#include <windows.h>
#endif

void lazy_print(const char *text, int delay_ms) {
    for (int i = 0; text[i] != '\0'; i++) {
        putchar(text[i]);
        fflush(stdout);
#ifdef _WIN32
        Sleep(delay_ms);
#else
        usleep(delay_ms * 1000);
#endif
    }
}

void show_banner() {
    FILE *file = fopen("banner.txt", "r");
    if (file == NULL) {
        printf("Could not load banner.\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        lazy_print(line, 0.1);  // 1ms per character, adjust for slower/faster effect
    }

    fclose(file);
}

void show_home_banner() {
    FILE *file = fopen("banner1.txt", "r");
    if (file == NULL) {
        printf("Could not load banner.\n");
        return;
    }

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        lazy_print(line, 0.5);  // 1ms per character, adjust for slower/faster effect
    }

    fclose(file);
}
