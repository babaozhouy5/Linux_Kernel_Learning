# Create our own rootfs & Debug linux kernel

In this chapter, we will create a rootfs which contains a **init** program, it has these commands----`help`, `version`, `quit`, `time`, `time-asm`. And then we will try to debug linux kernel with gdb debug tools. It just follows https://github.com/mengning/menu

## Create our own rootfs

    cd menu
    gcc -o init linktable.c menu.c test.c -m32 -static -lpthread
    cd ../rootfs && cp ../menu/init .
    find . | cpio -o -Hnewc | gzip -9 > ../rootfs.img # HERE it is :)

Now, we have created our own rootfs (rootfs.img).

## Debug linux kernel (linux-4.4.0 is our kernel source code)

Step1: We need reconfig linux kernel to make it compile with debug infos

    cd linux-4.4.0 && make defconfig
    make menuconfig # we must select Kernel hacking -> Compile-time checks and compiler options -> Compile the kernel with debug info (may different in other version kernel)
    make all # just wait it finishes

Step2: we will start kernel with gdb

    qemu -kernel linux-4.4.0/arch/x86/boot/bzImage -initrd rootfs.img -m 512M -s -S
    # -S: freeze CPU at startup (use `c` to start execution)
    # -s: shorthand for `-gdb tcp::1234`, if you don't want use 1234 port, you can use
    #     `-gdb tcp::xxxx` to replace `-s` option

Step3: open another shell window and just debug :)

    $ gdb
    (gdb) file linux-4.4.0/vmlinux # load symbol table, must before `target remote`
    (gdb) target remote:1234 # link `gdb` & `gdbserver`
    (gdb) break start_kernel # set break point, can use before `target remote`, type `c` and `enter` key let qemu to continue
    (gdb) # do something you want, let's say type `next`
