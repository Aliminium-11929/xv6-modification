#include "types.h"
#include "stat.h"
#include "user.h"

int main(void)
{
    uint32 info[3];
    if (sysinfo(info)<0){
        printf(2, "Error: argptr() function failure.");
        exit();
    }
    printf(1, "System Uptime: %lu ticks.\nTotal Processes: %lu processes.\nFree Memory: %lu KiloBytes.\n", info[0], info[1], info[2]);
    exit();
}