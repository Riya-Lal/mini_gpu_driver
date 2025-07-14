#ifndef MINI_GPU_H
#define MINI_GPU_H

#include <linux/ioctl.h>

#define GPU_MAGIC 'G'

//shape types
#define GPU_SHAPE_RECTANGLE 0
#define GPU_SHAPE_CIRCLE    1

//IOCTL command to draw a shape
#define GPU_IOCTL_DRAW_SHAPE _IOW(GPU_MAGIC, 0, struct gpu_command)

//Data structure for passing shape parameters
struct gpu_command {
	int shape; // 0=rectangle, 1=circle
	int x;
	int y;
	int width;
	int height;
};

#endif
