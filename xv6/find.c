#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char* fmtname(char *path) {
    static char buf[DIRSIZ + 1];
    char *p;

    // Find last slash
    for (p = path + strlen(path); p >= path && *p != '/'; p--);
    p++;

    if (strlen(p) >= DIRSIZ)
        return p;

    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), 0, DIRSIZ - strlen(p));
    return buf;
}

void find(char *path, char *target) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        printf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        printf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (st.type != T_DIR) {
        if (strcmp(fmtname(path), target) == 0)
        printf(1, "%s\n", path);
        close(fd);
        return;
    }

    // It's a directory
    if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
        printf(1, "find: path too long\n");
        close(fd);
        return;
    }

    if (strcmp(path, "/") == 0) {
        strcpy(buf, "/");
        p = buf + 1;  // points just after the slash
    } else {
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
    }


    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0)
        continue;
        if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (stat(buf, &st) < 0) {
        printf(1, "find: cannot stat %s\n", buf);
        continue;
        }

        if (st.type == T_DIR) {
        find(buf, target); // recurse
        } else if (strcmp(de.name, target) == 0) {
        printf(1, "%s\n", buf);
        }
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf(2, "Usage: find path target\n");
        exit();
    }

    find(argv[1], argv[2]);
    exit();
}
