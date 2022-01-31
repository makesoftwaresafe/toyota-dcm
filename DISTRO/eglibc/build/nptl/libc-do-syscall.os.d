$(common-objpfx)nptl/libc-do-syscall.os: \
 ../ports/sysdeps/unix/sysv/linux/arm/eabi/libc-do-syscall.S \
 ../include/libc-symbols.h \
 $(common-objpfx)config.h \
 ../sysdeps/wordsize-32/symbol-hacks.h

../include/libc-symbols.h:

$(common-objpfx)config.h:

../sysdeps/wordsize-32/symbol-hacks.h:
