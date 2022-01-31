# config.make.  Generated from config.make.in by configure.
# Don't edit this file.  Put configuration parameters in configparms instead.

version = 2.13
release = stable

# Installation prefixes.
install_root =
prefix = /usr
exec_prefix = ${prefix}
datadir = ${datarootdir}
libdir = ${exec_prefix}/lib
slibdir = /lib
localedir = 
sysconfdir = /etc
libexecdir = ${exec_prefix}/libexec
rootsbindir = /sbin
infodir = ${datarootdir}/info
includedir = ${prefix}/include
datarootdir = ${prefix}/share

# Should we use and build ldconfig?
use-ldconfig = yes

# Maybe the `ldd' script must be rewritten.
ldd-rewrite-script = no

# System configuration.
config-machine = arm
base-machine = arm
config-vendor = cas
config-os = linux-gnueabi
config-sysdirs =  ports/sysdeps/arm/elf ports/sysdeps/unix/sysv/linux/arm/eabi/nptl ports/sysdeps/unix/sysv/linux/arm/eabi ports/sysdeps/unix/sysv/linux/arm/nptl ports/sysdeps/unix/sysv/linux/arm ports/sysdeps/unix/sysv/linux nptl/sysdeps/unix/sysv/linux nptl/sysdeps/pthread sysdeps/pthread sysdeps/unix/sysv/linux sysdeps/gnu sysdeps/unix/common sysdeps/unix/mman sysdeps/unix/inet ports/sysdeps/unix/sysv nptl/sysdeps/unix/sysv sysdeps/unix/sysv ports/sysdeps/unix/arm ports/sysdeps/unix nptl/sysdeps/unix sysdeps/unix sysdeps/posix ports/sysdeps/arm/eabi ports/sysdeps/arm/fpu ports/sysdeps/arm/nptl ports/sysdeps/arm sysdeps/wordsize-32 sysdeps/ieee754/flt-32 sysdeps/ieee754/dbl-64 sysdeps/ieee754 sysdeps/generic/elf sysdeps/generic
cflags-cpu = 
asflags-cpu = 

config-cflags-sse4 = 
config-cflags-avx = 
config-asflags-i686 = 

defines =  -D_LIBC_REENTRANT
sysincludes = -nostdinc -isystem /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/bin/../lib/gcc/arm-cas-linux-gnueabi/4.6.2/include -isystem /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/bin/../lib/gcc/arm-cas-linux-gnueabi/4.6.2/include-fixed -isystem /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/include
c++-sysincludes = -isystem /usr/lib/gcc/x86_64-linux-gnu/4.6/../../../../include/c++/4.6 -isystem /usr/lib/gcc/x86_64-linux-gnu/4.6/../../../../include/c++/4.6/x86_64-linux-gnu -isystem /usr/lib/gcc/x86_64-linux-gnu/4.6/../../../../include/c++/4.6/backward
all-warnings = 

elf = yes
have-z-combreloc = yes
have-z-execstack = yes
have-initfini = 
have-Bgroup = yes
have-as-needed = no
libgcc_s_suffix = 
need-nopic-initfini = 
with-fp = yes
with-cvs = no
old-glibc-headers = no
unwind-find-fde = no
have-cpp-asm-debuginfo = 
enable-check-abi = no
have-forced-unwind = yes
have-fpie = yes
gnu89-inline-CFLAGS = -fgnu89-inline
have-ssp = no
have-selinux = no
have-libaudit = 
have-libcap = 
have-cc-with-libunwind = no
fno-unit-at-a-time = -fno-toplevel-reorder -fno-section-anchors
bind-now = no
have-hash-style = yes

static-libgcc = -static-libgcc

versioning = yes
oldest-abi = default
no-whole-archive = -Wl,--no-whole-archive
exceptions = -fexceptions
multi-arch = no

mach-interface-list = 

have-bash2 = yes
have-ksh = yes

sizeof-long-double = 0

experimental-malloc = 

nss-crypt = no

# Configuration options.
build-static = yes
build-shared = yes
build-pic-default= no
build-profile = no
build-omitfp = no
build-bounded = no
build-static-nss = no
add-ons = ports nptl libidn
add-on-subdirs =  libidn
sysdeps-add-ons =  ports nptl
cross-compiling = yes
force-install = yes

# Build tools.
CC = arm-cas-linux-gnueabi-gcc
CXX = g++
BUILD_CC = gcc
CFLAGS = -g -O2
ASFLAGS-config =  -Wa,--noexecstack
AR = /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/bin/../lib/gcc/arm-cas-linux-gnueabi/4.6.2/../../../../arm-cas-linux-gnueabi/bin/ar
NM = /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/bin/../lib/gcc/arm-cas-linux-gnueabi/4.6.2/../../../../arm-cas-linux-gnueabi/bin/nm
RANLIB = :
MAKEINFO = makeinfo
AS = $(CC) -c
MIG = 
PWD_P = /bin/pwd
BISON = /usr/bin/bison
AUTOCONF = autoconf
OBJDUMP = /home/uidj7648/Workspace/toyota-1.19.3/release/fs/devel/usr/bin/../lib/gcc/arm-cas-linux-gnueabi/4.6.2/../../../../arm-cas-linux-gnueabi/bin/objdump

# Installation tools.
INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_INFO = /usr/sbin/install-info
LN_S = ln -s
MSGFMT = msgfmt

# Script execution tools.
BASH = /bin/bash
KSH = /bin/bash
AWK = gawk
PERL = /usr/bin/perl

# Additional libraries.
LIBGD = no

# Package versions and bug reporting configuration.
PKGVERSION = (EGLIBC) 
REPORT_BUGS_TO = <http://www.eglibc.org/issues/>

# More variables may be inserted below by configure.

override stddef.h = # The installed <stddef.h> seems to be libc-friendly.
