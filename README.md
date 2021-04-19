# liboulu
Liboulu is an unfinished collection of libraries that enable modern games and programs. 

![Banner](https://raw.githubusercontent.com/OuluBSD/liboulu/main/doc/banner_210419.jpg)

The intention is to follow U++ conventions, but still make a standalone solution that works even without U++ and only with standard C libraries.
This solution is certainly too radical compared to current industrial solutions, but we aim to prove the usefulness of this solution in the long run in the future. 

The best advantages of this solution:
- you write less but understand more
- easier and faster debugging
- the most modern architectural choices of what exists

The biggest challenges:
- cannot use ready-made libraries if they have too many dependencies
- no compatibility with native GUI libraries and experiences
- no ready-made solutions that could be considered advice 



### How to compile

#### In FreeBSD
This is an example. Modify it to your needs.System-wide installation doesn't exist.

You might want to test packages in examples and reference directories. However, note that they probably won't build, because this whole repository is in very alpha state.

You should use TheIDE editor and create new assembly with the same directories that are in the following umk command. Packages with the description string should compile.
```
pkg install upp
git clone https://github.com/OuluBSD/liboulu.git
cd liboulu
umk \
	examples,reference,tutorial,ai,ecs,fusion,video,audio,compiler,local,alt,uppsrc,/usr/local/share/upp/uppsrc \
	BuggyCar GCC \
	-v +GUI,ALTCORE,VIRTUALGUI3DALT,SDL2GUI3DALT ~/
```
