# Setup Platform & Run you own kernel(include process schedule)

In this chapter, we will leran to setup platform to write your own Linux OS kernel, it's based on Linux Kernel 4.4.0 source code.

## Steps

All these are done in Ubuntu v16.04 4.4.0-75-generic x86_64 platform.

Step1: install qemu:

    sudo apt install qemu

Step2: test qemu:

    sudo qemu-system-x86_64 -kernel /boot/vmlinuz-$(uname -r) -initrd /boot/initrd.img-$(uname -r) -m 512M [-append "init=/sbin/init"]

Step3: for conveniet:

    sudo ln -s /usr/bin/qemu-system-i386 /usr/bin/qemu

Step4: get the kernel source:

    apt-get source linux-image-$(uname -r)

 so for me, the file will be **linux_4.4.0.orig.tar.gz** and others(don't need care)(you can also use other version kernel, but believe me, it will have many troubles.)

Step5: decompress the file:

    tar xf linux_4.4.0.orig.tar.gz

 (actually, apt-get source linux-image... will do it for us, and will get dir **linux-4.4.0**)

Step6: apply patch:

    cd linux-4.4.0 && patch -p1 < ../mykernel_for_linux.4.4.0sc.patch
    cp -R ../mykernel .  # we will add process schedule here

Step7: generate default config file:

    make defconfig

Step8: menu config, choose what you need or not:

    make menuconfig

    (NOTICE: please unselect the first option <64-bit kernel>, we only build 32-bit kernel)

Step9: make:

    make all && make modules

 (will generate arch/x86/boot/bzImage)

Step10: generate **initramfs**:

    cd arch/x86/boot/ && mkinitramfs -o initrd.img-$(uname -r) $(uname -r)

 (will generate initrd.img-4.4.0-75-generic in arch/x86/boot)

Step11: Now, we can run our kernel:

    qemu -kernel bzImage -initrd initrd.img-4.4.0-75-generic -m 512M [-append "init=/sbin/init"]

## Tips

Tip1: How to generate patch file

    diff -Naur linux-4.4.0 linux-4.4.0.new/ > mykernel_for_linux.4.4.0sc.patch

Tip2: Steps explains

[Compiling Linux kernel and running it using QEMU](https://nostillsearching.wordpress.com/2012/09/22/compiling-linux-kernel-and-running-it-using-qemu/) (NOTICE: you'd better download the same version kernel source code which you are using(uanme -r), or you may cause many problems)
