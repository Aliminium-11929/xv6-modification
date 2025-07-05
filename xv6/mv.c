#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char *argv[])
{
    int from, to, n;
    char buf[512];

    if (argc != 3) {
        printf(2, "Usage: mv source target\n");
        exit();
    }

    from = open(argv[1], O_RDONLY);
    if (from < 0) {
        printf(2, "mv: cannot open %s\n", argv[1]);
        exit();
    }

    to = open(argv[2], O_CREATE | O_WRONLY);
    if (to < 0) {
        printf(2, "mv: cannot create %s\n", argv[2]);
        close(from);
        exit();
    }

    while ((n = read(from, buf, sizeof(buf))) > 0) {
        if (write(to, buf, n) != n) {
        printf(2, "mv: write error\n");
        close(from);
        close(to);
        unlink(argv[2]);
        exit();
        }
    }

    close(from);
    close(to);

    // Delete the original file
    if (unlink(argv[1]) < 0) {
        printf(2, "mv: failed to remove original file %s\n", argv[1]);
    }

    exit();
}
