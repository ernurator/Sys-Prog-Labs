#include "iobench.h"

int main() {
    // opens a file called `data` with the O_SYNC
    int fd = open("data", O_WRONLY | O_CREAT | O_TRUNC | O_SYNC, 0666);
    
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // writes the characer '6' to the file
    size_t size = 5120000;
    const char* buf = "6";
    double start = tstamp();

    size_t n = 0;
    while (n < size) {
        ssize_t r = write(fd, buf, 1);
        if (r != 1) {
            perror("write");
            exit(1);
        }

        // with some frequency (defined in iobench.h), prints out
        // how long it takes to complete the write.
        n += r;
        if (n % PRINT_FREQUENCY == 0) {
            report(n, tstamp() - start);
        }
    }

    close(fd);
    report(n, tstamp() - start);
    fprintf(stderr, "\n");
}
