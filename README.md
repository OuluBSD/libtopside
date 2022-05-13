![Banner](https://raw.githubusercontent.com/OuluBSD/libtopside/main/doc/banner_210516.jpg)

Libtopside is an alternative to a subset of Ultimate++ framework.


## How to compile

### In FreeBSD
This is an example to build the AtomShell package. Modify it to your needs. System-wide installation doesn't exist.

You might want to test other packages in examples and reference directories. However, note that they probably won't build, because this whole repository is in very alpha state still.

Instead of these commands, you may use U++ TheIDE editor and create new assembly with the same directories that are in the following umk command. Packages with the description string should compile.

```
sudo pkg install upp git
sudo pkg install ffmpeg sdl2 sdl2_mixer sdl2_image sdl2_ttf opencv
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
umk examples,reference,tutorial,accel,ai,ecs,serial,parallel,video,audio,compiler,local,alt,lib AtomShell ~/libtopside/script/CLANG_FreeBSD.bm -budsH4 +GUI,SHARED,FFMPEG,SCREEN,OGL,SDL2,OPENCV ~/

Test run e.g:   ~/AtomShell -e play_audio_file.eon -MACHINE_TIME_LIMIT=3 -FILE=/home/user/some.mp3
```
