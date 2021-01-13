# BrandOS
Lightweight x86_64 based operating system written in assembly and c

# Build Instructions

## dependencies:

#### I will take this excerpt on how to compile gcc from  [cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial):
**IMPORTANT: you may get errors if the gcc version you are compiling does not match your current gcc version**<br>
to check your current gcc version:<br>
    
    gcc --version

> Required packages  
> -----------------  
> First, install the required packages. On linux, use your package distribution. On a Mac, [install brew](http://brew.sh/) if  
> you didn't do it on lesson 00, and get those packages with `brew install` 
> - gmp
> - mpfr
> - libmpc
> - gcc
> 
> Yes, we will need `gcc` to build our cross-compiled `gcc`, > especially on a Mac where gcc has been deprecated for `clang`
> 
> Once installed, find where your packaged gcc is (remember, not > clang) and export it. For example:
> 
> ```
> export CC=/usr/local/bin/gcc-4.9
> export LD=/usr/local/bin/gcc-4.9
> ```
> 
> We will need to build binutils and a cross-compiled gcc, and we > will put them into `/usr/local/i386elfgcc`, so
> let's export some paths now. Feel free to change them to your > liking.
> 
> ```
> export PREFIX="/usr/local/i386elfgcc"
> export TARGET=i386-elf
> export PATH="$PREFIX/bin:$PATH"
> ```
> 
> binutils
> --------
> 
> Remember: always be careful before pasting walls of text from > the internet. I recommend copying line by line.
> 
> ```sh
> mkdir /tmp/src
> cd /tmp/src
> curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.24.tar.gz # > If the link 404's, look for a more recent version
> tar xf binutils-2.24.tar.gz
> mkdir binutils-build
> cd binutils-build
> ../binutils-2.24/configure --target=$TARGET --enable-interwork > --enable-multilib --disable-nls --disable-werror > --prefix=$PREFIX 2>&1 | tee configure.log
> make all install 2>&1 | tee make.log
> ```
> 
> gcc
> ---
> ```sh
> cd /tmp/src
> curl -O https://ftp.gnu.org/gnu/gcc/gcc-4.9.1/gcc-4.9.1.tar.bz2
> tar xf gcc-4.9.1.tar.bz2
> mkdir gcc-build
> cd gcc-build
> ../gcc-4.9.1/configure --target=$TARGET --prefix="$PREFIX" > --disable-nls --disable-libssp --enable-languages=c > --without-headers
> make all-gcc 
> make all-target-libgcc 
> make install-gcc 
> make install-target-libgcc 
> ```
> 
> That's it! You should have all the GNU binutils and the > compiler at `/usr/local/i386elfgcc/bin`, prefixed by > `i386-elf-` to avoid
> collisions with your system's compiler and binutils.
> 
> You may want to add the `$PATH` to your `.bashrc`. From now on, > on this tutorial, we will explicitly use the prefixes when using
> the cross-compiled gcc.

    sudo apt-get install nasm
<!-- tsk -->
    sudo apt-get install qemu-system
<!-- tsk -->
    make
<!-- tsk -->
    make run
