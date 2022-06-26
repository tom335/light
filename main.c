#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYS_PATH       "/sys/class/backlight/intel_backlight/"
#define MAX_BRIGHTNESS "max_brightness"
#define BRIGHTNESS     "brightness"

char* concat(const char *s1, const char *s2)
{
    char* result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // TODO check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int get_max_brightness() {
    char* max_file_name = concat(SYS_PATH, MAX_BRIGHTNESS);
    FILE* max_file_ptr;
    int max_brightness;

    max_file_ptr = fopen(max_file_name, "r");

    if (max_file_ptr == NULL)
       exit(1);

    fscanf(max_file_ptr, "%d", &max_brightness);
    fclose(max_file_ptr);

    return max_brightness;
}

void set_brightness(int arg_bright, int max_brightness) {
    char* bright_file_name = concat(SYS_PATH, BRIGHTNESS);

    // calculates the amount of brightness based on the maximum
    int calc_brightness = (arg_bright * max_brightness) / 100;

    FILE* bright_file_ptr = fopen(bright_file_name, "w");

    if (bright_file_ptr == NULL) {
        printf("Error: cannot open the brightness file\n");
        exit(1);
    } else {
        fprintf(bright_file_ptr, "%d", calc_brightness);
        fclose(bright_file_ptr);
    }
}

int main(int argc, const char *argv[])
{
    if (argc == 2) {
        int arg_bright = atoi(argv[1]);
        int max_brightness = get_max_brightness();

        set_brightness(arg_bright, max_brightness);
    } else {
        // prints the current brightness
    }

    return 0;
}
