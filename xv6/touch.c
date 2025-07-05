#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
    int fd;

    if (argc < 2) {
    printf(2, "Usage: touch <file>...\n");
    exit();
    }

    for (int i = 1; i < argc; i++) {
    // Try to open file for writing; create if it doesn't exist
    fd = open(argv[i], O_CREATE | O_WRONLY);
    if (fd < 0) {
        printf(2, "touch: cannot create %s\n", argv[i]);
        continue;
    }
    close(fd);
    }

    exit();
}
