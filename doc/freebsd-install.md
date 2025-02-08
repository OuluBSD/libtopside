# Installing in FreeBSD

## Install dependencies
Install normal Ultimate++ TheIDE using the package manager.

```
pkg install upp
```

Install dependency libraries:

```
pkg install glew ffmpeg assimp sdl2 sdl2_ttf sdl2_image hidapi OpenHMD opencv
```

Install the latest clang, but check your latest version:

```
pkg install `pkg search llvm | grep -v lite | grep "LLVM and Clang" | sort | tail -1 | awk '{print $1}'`
```

Create assembly with reference, src and either alt or U++'s uppsrc.
Open reference/Shell package, build it and execute it.


## Update the build method
Open TheIDE. At menu bar, choose Setup->Build methods. Update your CLANG configuration

- Set compiler name (depending on your clang version) e.g. ```clang++19```
- Add ```/usr/local/bin``` to build method's *PATH* list.
- Add ```/usr/local/include/opencv4``` to build method's include list

