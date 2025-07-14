# Mini GPU Linux Kernel Driver Project

This project simulates a minimal GPU-like interface using a Linux character device driver and `ioctl` system calls. The kernel module listens for shape-drawing commands from a user-space program and logs them to the kernel log buffer (`dmesg`).

---

## Project Features

- Linux kernel character device driver (`/dev/mini_gpu`)
- Communicates with user-space via `ioctl` system calls
- Supports drawing basic shapes like **RECTANGLE** and **CIRCLE**
- Demonstrates device file operations (`open`, `read`, `release`)
- Logs drawing operations to kernel log buffer (`dmesg`)
- Modular structure for easy extension

---

## Project Structure

mini_gpu_driver/
├── kernel_module/ # 

Contains the Linux kernel driver
│ ├── mini_gpu.c
│ ├── mini_gpu.h
│ └── Makefile
├── user_program/ # User-space programs
│ ├── test_gpu_user.c
│ └── test_gpu_ioctl_user.c
├── .gitignore
└── README.md

# Build and run instructions
## 1. Build Kernel Module

```bash
cd kernel_module
make
sudo insmod mini_gpu.ko

2. Run User Program

cd ../user_program
gcc test_gpu_ioctl_user.c -o test_gpu_ioctl_user
./test_gpu_ioctl_user

3. View Kernel Output

sudo dmesg | tail -20


Sample Output

Terminal Output:

Sent RECTANGLE draw command to kernel
Sent CIRCLE draw command to kernel

Kernel Log (dmesg):

mini_gpu: Device opened (1 times)
mini_gpu: Drawing RECTANGLE at (10, 10) size (100 x 50)
mini_gpu: Drawing CIRCLE at (50, 50) with diameter 40
mini_gpu: Device successfully closed


Future Enhancements

    Add real-time shape rendering using a Python GUI with ioctl

    Add support for more complex shapes and transformations

    Integrate with 3D simulation tools (e.g., OpenGL backend)

    Extend ioctl to accept dynamic user-defined parameters

 Skills Demonstrated

    Linux Kernel Development (character devices, insmod, rmmod)

    ioctl communication protocol between user and kernel space

    C programming in kernel and user space

    Device file I/O handling and kernel logging

License
This project is licensed under the MIT License.

Contributing
Pull requests are welcome. For major changes, open an issue first to discuss what you would like to change.

Maintainer:
Riya <3
