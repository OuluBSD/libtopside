![Banner](https://raw.githubusercontent.com/OuluBSD/libtopside/main/doc/banner_210516.jpg)

Libtopside is alternative to a subset of Ultimate++ framework.


## How to compile

### In FreeBSD
This is an example to build the MP3Player project in the reference directory. Modify it to your needs. System-wide installation doesn't exist.

You might want to test other packages in examples and reference directories. However, note that they probably won't build, because this whole repository is in very alpha state still.

Instead of these commands, you should use U++ TheIDE editor and create new assembly with the same directories that are in the following umk command. Packages with the description string should compile.

```
pkg install upp git
git clone https://github.com/OuluBSD/libtopside.git
cd libtopside
umk examples,reference,tutorial,ai,ecs,accel,video,audio,compiler,local,alt,lib MP3Player CLANG -budsH4 ~/
```
