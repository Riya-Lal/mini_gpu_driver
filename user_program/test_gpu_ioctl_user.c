#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "../kernel_module/mini_gpu.h"

int main() {
    int fd = open("/dev/mini_gpu", O_RDWR);
    if (fd < 0) {
        perror("Failed to open /dev/mini_gpu");
        return 1;
    }

    struct gpu_command cmd;

    // Send a RECTANGLE command
    cmd.shape = GPU_SHAPE_RECTANGLE;
    cmd.x = 10;
    cmd.y = 10;
    cmd.width = 100;
    cmd.height = 50;

    if (ioctl(fd, GPU_IOCTL_DRAW_SHAPE, &cmd) < 0) {
        perror("IOCTL failed for RECTANGLE");
    } else {
        printf("Sent RECTANGLE draw command to kernel\n");
    }

    // Send a CIRCLE command
    cmd.shape = GPU_SHAPE_CIRCLE;
    cmd.x = 50;
    cmd.y = 50;
    cmd.width = 40;   // width = diameter
    cmd.height = 0;   // not used

    if (ioctl(fd, GPU_IOCTL_DRAW_SHAPE, &cmd) < 0) {
        perror("IOCTL failed for CIRCLE");
    } else {
        printf("Sent CIRCLE draw command to kernel\n");
    }

    close(fd);
    return 0;
}

