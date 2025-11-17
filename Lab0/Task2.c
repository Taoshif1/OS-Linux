#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int src, dest;
    char buf[256];
    int n;

    src = open("input.txt", O_RDONLY);
    if (src < 0) {
        perror("Error opening source");
        return 1;
    }

    dest = open("target.txt", O_WRONLY | O_APPEND);
    if (dest < 0) {
        perror("Error opening target");
        close(src);
        return 1;
    }

    while ((n = read(src, buf, sizeof(buf))) > 0) {
        write(dest, buf, n);
    }

    close(src);
    close(dest);

    printf("Append complete.\n");
    return 0;
}
