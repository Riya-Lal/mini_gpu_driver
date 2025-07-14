#ifndef MINI_GPU_H
#define MINI_GPU_H

#include <linux/ioctl.h>

#define GPU_MAGIC 'g'

enum gpu_shape_type {
    GPU_SHAPE_RECTANGLE = 1,
    GPU_SHAPE_CIRCLE    = 2,
    GPU_SHAPE_LINE      = 3,
    GPU_SHAPE_TRIANGLE  = 4
};

//Data structure for passing shape parameters
struct gpu_command {
	int shape; // 1=rectangle, 2=circle
	int x;
	int y;
	int width;
	int height;
};

//IOCTL command to draw a shape
#define GPU_IOCTL_DRAW_SHAPE _IOW(GPU_MAGIC, 0, struct gpu_command)

#endif
