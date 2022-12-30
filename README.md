![Banner](https://raw.githubusercontent.com/OuluBSD/libtopside/main/doc/banner_210516.jpg)

libtopside is a research project that both extends Ultimate++ and is an alternative implementation focused on 3D VR GUI and AI. 

## How to compile

### In Linux (u++ method)
Follow [Ultimate++](https://www.ultimatepp.org/) installation instructions. Finally, you should have ```umk``` and ```theide``` executables at your command.

Install git, sdl2, sdl2-image, sdl2-ttf, ffmpeg, opencv, portaudio, portmidi, assimp, freeglut, glew, ode, hidapi, hidapi-libusb, x11, v4l2, libpng.

```
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd ~/libtopside
umk examples,reference,tutorial,ai,alt,audio,compiler,ecs,lib,local,parallel,script,serial,tests EcsShell ~/libtopside/script/CLANG_Linux.bm -budsH4 +SCREEN,SDL2,OGL,FFMPEG,OPENCV,VR,LOCALHMD,FLUIDSYNTH,BUILTIN_PORTAUDIO,BUILTIN_ASSIMP ~/

Test run e.g:   ~/EcsShell -e play_audio_file.eon -MACHINE_TIME_LIMIT=10 -FILE=~/libtopside/share/sounds/8_bit_mentality.mp3
```


### In Linux (using cmake)

Install cmake, git, sdl2, sdl2-image, sdl2-ttf, ffmpeg, opencv, portaudio, portmidi, assimp, freeglut, glew, ode, hidapi, hidapi-libusb, x11, v4l2, libpng.

```
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
mkdir build
cd build
cmake ..
make
```


### In FreeBSD
This is an example to build the EcsShell package. Modify it to your needs. System-wide installation doesn't exist.

You might want to test other packages in examples and reference directories. However, note that they probably won't build, because this whole repository is in very alpha state still.

Instead of these commands, you may use U++ TheIDE editor and create new assembly with the same directories that are in the following umk command. Packages with the description string should compile.

```
sudo pkg install upp git
sudo pkg install ffmpeg sdl2 sdl2_mixer sdl2_image sdl2_ttf opencv
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd ~/libtopside
umk examples,reference,tutorial,ai,alt,audio,compiler,ecs,lib,local,parallel,script,serial,tests EcsShell ~/libtopside/script/CLANG_FreeBSD.bm -budsH4 +SCREEN,SDL2,OGL,FFMPEG,OPENCV,VR,LOCALHMD,FLUIDSYNTH,BUILTIN_PORTAUDIO,BUILTIN_ASSIMP ~/

Test run e.g:   ~/EcsShell -e play_audio_file.eon -MACHINE_TIME_LIMIT=10 -FILE=~/libtopside/share/sounds/8_bit_mentality.mp3
```
