#Compiling

## Frequently used systens

### In Windows

#### With Visual C++ compiler
1. Install [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/)
2. Install [Ultimate++](https://www.ultimatepp.org/) and TheIDE should recognize Visual Studio compiler automaticallya nd make build method MSVS22
3. Git clone this repository to C:\git\. ```git clone https://github.com/OuluBSD/libtopside```
   Also, you probably want to switch to bleeding edge branch with ```git checkout bleedingedge```
4. Create 2 new assemblies with ```C:\git\libtopside\src;C:\git\libtopside\reference;C:\git\libtopside\tutorial;C:\git\libtopside\tests;C:\git\libtopside\alt;C:\upp/uppsrc``` and ```C:\git\libtopside\src;C:\git\libtopside\reference;C:\git\libtopside\uppsrc_reference;C:\git\libtopside\tests;C:\git\libtopside\uppsrc;C:\upp/uppsrc```
5. Install vcpkg separately from Visual Studio. Use PowerShell and follow [VCPKG Getting Started](https://vcpkg.io/en/getting-started.html).
6. Install dependencies in PowerShell: ```./vcpkg install glew:x64-windows sdl2:x64-windows sdl2-ttf:x64-windows sdl2-image:x64-windows openssl:x64-windows libssh[crypto]:x64-windows assimp:x64-windows```
7. In TheIDE, open Build methods and add following directories to MSVS22x64. To INCLUDE: ```C:\git\vcpkg\installed\x64-windows\include``` To LIB: ```C:\git\vcpkg\installed\x64-windows\lib```
   Add C++ standard 17 as requirement, by adding ```/std:c++17``` to Common Options.
8. In TheIDE and Built Methods, add ```C:\git\vcpkg\installed\x64-windows\bin``` to PATH
   ```C:\git\vcpkg\installed\x64-windows\lib``` to INCLUDE and
   ```C:\git\vcpkg\installed\x64-windows\lib``` to LIB.
9. If you can't execute the built exe, then copy vcpkg .dll files to your build directory.

#### With GCC or Clang installed by MSYS2
1. Git clone this repository to C:\git\. ```git clone https://github.com/OuluBSD/libtopside```
   Also, you probably want to switch to bleeding edge branch with ```git checkout bleedingedge```
2. Install [MSYS2](https://www.msys2.org/wiki/MSYS2-installation/)
3. Install required packages in C:\msys64\msys2.exe shell 
 - ```pacman -S --needed base-devel mingw-w64-clang-x86_64-toolchain``` and select 1
 - ```pacman -S mingw-w64-clang-x86_64-openjpeg mingw-w64-clang-x86_64-glew mingw-w64-clang-x86_64-assimp mingw-w64-clang-x86_64-fluidsynth mingw-w64-clang-x86_64-portaudio mingw-w64-clang-x86_64-portmidi mingw-w64-clang-x86_64-SDL2_ttf mingw-w64-clang-x86_64-SDL2_image mingw-w64-clang-x86_64-assimp```
 
   For GCC instead of Clang: in C:\msys64\mingw64.exe shell
 - ```pacman -S --needed base-devel mingw-w64-x86_64-toolchain```
 - ```pacman -S mingw-w64-x86_64-openjpeg mingw-w64-x86_64-glew mingw-w64-x86_64-assimp mingw-w64-x86_64-fluidsynth mingw-w64-x86_64-portaudio mingw-w64-x86_64-portmidi mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-assimp```
4. Copy ```C:\git\libtopside\script\msys2\MSYS_CLANGx64.bm``` to ```C:\upp```
Also, Check and change the .bm file include path for latest version ```C:\msys64\clang64\lib\clang\15.0.7\include```
5. In TheIDE, open Build Methods and add ```-std=c++17``` to CLANG's Common C++ Options

### In Linux

#### Ubuntu

1. Install dependencies
```
apt install libglew-dev libsdl2-ttf-dev libsdl2-gfx-dev libsdl2-dev libsdl2-image-dev libhidapi-libusb0 libhidapi-dev libv4l-dev libopencv-core-dev libopencv-imgproc-dev libopencv-highgui-dev libvorbis-dev libopencv-shape-dev  freeglut3-dev libavdevice-dev libfluidsynth-dev libxxf86vm-dev libportmidi-dev
```
2. Clone and build libtopside using cmake
```
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
git checkout bleedingedge
mkdir build
cd build
cmake ..
make
```

### In FreeBSD

1. Install dependencies
```
pkg install upp sndio ffmpeg hidapi sdl2 sdl2_ttf sdl2_image opencv glew freeglut portmidi portaudio
```
2. Clone and build libtopside using cmake
```
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
git checkout bleedingedge
```

2. Open TheIDE and add 2 assemblies
```/home/user/libtopside/src;/home/user/libtopside/reference;/home/user/libtopside/tutorial;/home/user/libtopside/tests;/home/user/libtopside/alt;C:/upp/uppsrc```
and
```/home/user/libtopside/src;/home/user/libtopside/reference;/home/user/libtopside/uppsrc_reference;/home/user/libtopside/tests;/home/user/libtopside/uppsrc;C:/upp/uppsrc```
3. Open package, e.g. Shell, and press F7 to build.



## Extra systems

### In Windows

#### UWP Visual C++ compiler
Theide build method:
```
Common options:
/Zc:wchar_t /sdl /await /D HAS_CPPWINRT /D "_UNICODE" /D "UNICODE" /D "_DEBUG" /D "WINAPI_FAMILY=WINAPI_FAMILY_APP" /D "__WRL_NO_DEFAULT_LIB__" /RTC1 /Gd /EHsc /TP /std:c++latest /FU"D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.35.32215\lib\x86\store\references\platform.winmd"

C++ options:
/ZW:nostdlib
```
CMake:
```
cmake -G "Visual Studio 17 2022" -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0 ..
```

### In FreeBSD

#### Emscripten
Install emscripten and make compatibility symbolic link for linker, because TheIDE doesn't support emscripten yet (only regular ar).

```
pkg install emscripten
mkdir /usr/local/bin/embin
ln -s /usr/local/bin/emar /usr/local/bin/embin/ar
```

Duplicate your existing CLANG build method in TheIDE and add ```/usr/local/bin/embin``` directory to your BIN directory list as **first**.

To enable exceptions, add ```-fwasm-exceptions``` to the build method's Common options and Common link options. By default, exception catching is disabled in Emscripten.


### In Linux

#### Emscripten
Download and install Emscripten SDK.
Duplicate your existing CLANG build method in TheIDE and add emsdk bin directory to your BIN directory list as **first**.
Add ```-fwasm-exceptions -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2 -sUSE_BZIP2=1 -sUSE_LIBPNG -sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1``` to the build method's Common options.
Add ```-fwasm-exceptions -sUSE_BZIP2=1 -sUSE_LIBPNG -sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1  --embed-file /home/user/libtopside/share/eon/tests/00a_audio_gen.eon@/tests/``` to the build method's Common link options.
Set up lightthd server and symlink new files to the web root. Create html file with some hello world emscripten example.

