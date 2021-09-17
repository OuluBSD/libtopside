![Banner](https://raw.githubusercontent.com/OuluBSD/libtopside/main/doc/banner_210516.jpg)

Libtopside is an alternative to a subset of Ultimate++ framework.


## How to compile

### In FreeBSD
This is an example to build the AtomShell package. Modify it to your needs. System-wide installation doesn't exist.

You might want to test other packages in examples and reference directories. However, note that they probably won't build, because this whole repository is in very alpha state still.

Instead of these commands, you may use U++ TheIDE editor and create new assembly with the same directories that are in the following umk command. Packages with the description string should compile.

```
sudo pkg install upp git
cd ~
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
umk examples,reference,tutorial,ai,serial,video,audio,compiler,local,alt,lib AtomShell ~/libtopside/script/CLANG_FreeBSD.bm -budsH4 +GUI,SHARED ~/

Test run e.g:   ~/AtomShell -e tests/04a_sdl_audio.eon -MACHINE_TIME_LIMIT=3
```
