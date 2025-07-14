import tkinter as tk
import fcntl
import os
import struct

# Constants
GPU_MAGIC = ord('g')
IOCTL_DRAW_SHAPE = 0

SHAPE_RECTANGLE = 1
SHAPE_CIRCLE = 2
SHAPE_LINE = 3
SHAPE_TRIANGLE = 4

# Define ioctl code manually (_IOW)
def _IOW(magic, number, size):
    IOC_WRITE = 1
    IOC_NRBITS = 8
    IOC_TYPEBITS = 8
    IOC_SIZEBITS = 14
    IOC_DIRBITS = 2

    IOC_NRSHIFT = 0
    IOC_TYPESHIFT = IOC_NRSHIFT + IOC_NRBITS
    IOC_SIZESHIFT = IOC_TYPESHIFT + IOC_TYPEBITS
    IOC_DIRSHIFT = IOC_SIZESHIFT + IOC_SIZEBITS

    return (IOC_WRITE << IOC_DIRSHIFT) | (magic << IOC_TYPESHIFT) | (number << IOC_NRSHIFT) | (size << IOC_SIZESHIFT)

def IOCTL_DRAW_SHAPE_CODE():
    return _IOW(GPU_MAGIC, IOCTL_DRAW_SHAPE, struct.calcsize('i4i'))

# Send draw command to kernel
def send_draw_command(shape_type, x, y, w, h):
    try:
        with open("/dev/mini_gpu", "wb", buffering=0) as dev:
            data = struct.pack('i4i', shape_type, x, y, w, h)
            fcntl.ioctl(dev, IOCTL_DRAW_SHAPE_CODE(), data)
    except Exception as e:
        print(f"Error sending IOCTL: {e}")

# ==== GUI ====
root = tk.Tk()
root.title("Mini GPU GUI with Framebuffer Simulation")

# Canvas to simulate framebuffer
canvas_width = 300
canvas_height = 300
canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="white")
canvas.pack(pady=10)

def draw_rectangle():
    x, y, w, h = 50, 50, 100, 60
    canvas.create_rectangle(x, y, x+w, y+h, fill="skyblue", outline="black")
    send_draw_command(SHAPE_RECTANGLE, x, y, w, h)

def draw_circle():
    x, y, r = 200, 100, 40
    canvas.create_oval(x-r, y-r, x+r, y+r, fill="lightgreen", outline="black")
    send_draw_command(SHAPE_CIRCLE, x, y, r, 0)

def draw_line():
    x1, y1, x2, y2 = 100, 200, 300, 200
    canvas.create_line(x1, y1, x2, y2, fill="red", width=2)
    send_draw_command(SHAPE_LINE, x1, y1, x2, y2)

def draw_triangle():
    x, y, base, height = 150, 250, 100, 60
    canvas.create_polygon(x, y, x+base, y, x+(base//2), y-height, fill="orange", outline="black")
    send_draw_command(SHAPE_TRIANGLE, x, y, base, height)

def erase_canvas():
    canvas.delete("all")

tk.Button(root, text="Draw Rectangle", command=draw_rectangle).pack(pady=5)
tk.Button(root, text="Draw Circle", command=draw_circle).pack(pady=5)
tk.Button(root, text="Draw Line", command=draw_line).pack(pady=3)
tk.Button(root, text="Draw Triangle", command=draw_triangle).pack(pady=3)
tk.Button(root, text="Erase Canvas", command=erase_canvas).pack(pady=8)

root.mainloop()
