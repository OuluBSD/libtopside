### In Windows (UWP)
Theide build method:
```
Common options:
/Zc:wchar_t /sdl /D "_UNICODE" /D "UNICODE" /D "_DEBUG" /D "WINAPI_FAMILY=WINAPI_FAMILY_APP" /D "__WRL_NO_DEFAULT_LIB__" /RTC1 /Gd /EHsc /TP /std:c++latest /FU"D:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.35.32215\lib\x86\store\references\platform.winmd"

C++ options:
/ZW:nostdlib
```
CMake:
```
cmake -G "Visual Studio 17 2022" -DCMAKE_SYSTEM_NAME=WindowsStore -DCMAKE_SYSTEM_VERSION=10.0 ..
```


### In Ubuntu
```
apt install libglew-dev libsdl2-ttf-dev libsdl2-gfx-dev libsdl2-dev libsdl2-image-dev libhidapi-libusb0 libhidapi-dev libv4l-dev libopencv-core-dev libopencv-imgproc-dev libopencv-highgui-dev libvorbis-dev libopencv-shape-dev  freeglut3-dev libavdevice-dev libfluidsynth-dev libxxf86vm-dev libportmidi-dev

cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
mkdir build
cd build
cmake ..
make
```

### In FreeBSD
```
apt install upp sndio ffmpeg hidapi sdl2 sdl2_ttf sdl2_image opencv glew freeglut portmidi portaudio
```


### Emscripten (in FreeBSD)
Install emscripten and make compatibility symbolic link for linker, because TheIDE doesn't support emscripten yet (only regular ar).

```
pkg install emscripten
mkdir /usr/local/bin/embin
ln -s /usr/local/bin/emar /usr/local/bin/embin/ar
```

Duplicate your existing CLANG build method in TheIDE and add ```/usr/local/bin/embin``` directory to your BIN directory list as **first**.

To enable exceptions, add ```-fwasm-exceptions``` to the build method's Common options and Common link options. By default, exception catching is disabled in Emscripten.


### Emscripten (in Linux)
Download and install Emscripten SDK.
Duplicate your existing CLANG build method in TheIDE and add emsdk bin directory to your BIN directory list as **first**.
Add ```-fwasm-exceptions -sUSE_SDL=2 -sUSE_SDL_TTF=2 -sUSE_SDL_IMAGE=2 -sUSE_BZIP2=1 -sUSE_LIBPNG -sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1``` to the build method's Common options.
Add ```-fwasm-exceptions -sUSE_BZIP2=1 -sUSE_LIBPNG -sUSE_FREETYPE=1 -sUSE_HARFBUZZ=1  --embed-file /home/user/libtopside/share/eon/tests/00a_audio_gen.eon@/tests/``` to the build method's Common link options.
Set up lightthd server and symlink new files to the web root. Create html file with some hello world emscripten example.

