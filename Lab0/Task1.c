#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

int main() {
    int fd;
    char buf[256];
    int r;

    long chars = 0, words = 0, lines = 0;
    int inWord = 0;

    fd = open("input.txt", O_RDONLY);
    if (fd < 0) {
        perror("File open error");
        return 1;
    }

    while ((r = read(fd, buf, sizeof(buf))) > 0) {
        for (int i = 0; i < r; i++) {
            char c = buf[i];
            chars++;

            if (c == '\n') lines++;

            if (isspace(c)) {
                inWord = 0;
            } else if (!inWord) {
                words++;
                inWord = 1;
            }
        }
    }

    close(fd);

    printf("Chars: %ld\nWords: %ld\nLines: %ld\n", chars, words, lines);

    return 0;
}
