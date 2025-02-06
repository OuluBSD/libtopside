# LittleKernel

This kernel was started in 2015 (or 2014) by following a tutorial made by James O'Molloy (http://www.jamesmolloy.co.uk/tutorial_html/). It was imported to libtopside in 2022.


## Issues

### [Known bugs in the tutorial](https://wiki.osdev.org/James_Molloy%27s_Tutorial_Known_Bugs)
The original tutorial is a very good package for first time kernel programmer. Especially, if
you are a guy who used DOS and Amiga computers back in the early 90s, when "everyone" used floppies.
It has some problems though, which we should be aware.

High-level parts of the kernel should be compilable to a normal linux/windows executable.
Built-in virtual machine abstraction should be same as hardware abstraction.
Tasks should use user-space threading, when virtual-machine abstraction is used.

## Compiling
We are using a regular gcc for now, because we are excluding all native libraries and it has
everything we need. The best practice is to use only what you need.

Copy build method file to your U++ ide configuration folder (but check your 'theide' folder).
	cp GCC_K32.bm ~/.config/u++/theide/


Compile the program normally. After that, run as root or sudoable:
```
./update_image.sh /your/compiled/executable && ./run_qemu.sh
```
