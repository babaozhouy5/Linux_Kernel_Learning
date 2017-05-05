## Setup Platform

It is a platform to write your own Linux OS kernel, it's based on Linux Kernel 4.4.0 source code.

### Steps

All these are done in Ubuntu v16.04 4.4.0-75-generic x86_64 platform.

- install qemu:


    sudo apt install qemu

- test qemu:


    sudo qemu-system-x86_64 -kernel /boot/vmlinuz-$(uname -r) -initrd /boot/initrd.img-$(uname -r) -m 512M [-append "init=/sbin/init"]

- for conveniet:


    sudo ln -s /usr/bin/qemu-system-i386 /usr/bin/qemu

- get the kernel source:


    apt-get source linux-image-$(uname -r)

 so for me, the file will be **linux_4.4.0.orig.tar.gz** and others(don't need care)(you can also use other version kernel, but believe me, it will have many troubles.)

- decompress the file:


    tar xf linux_4.4.0.orig.tar.gz

 (actually, apt-get source linux-image... will do it for us, and will get dir **linux-4.4.0**)

- apply patch:


    cd linux-4.4.0 && patch -p1 < ../mykernel_for_linux.4.4.0sc.patch

- generate default config file:


    make defconfig

- menu config, choose what you need or not:


    make menuconfig

- make:


    make all && make modules

 (will generate arch/x86/boot/bzImage)

- generate **initramfs**:


    cd arch/x86/boot/ && mkinitramfs -o initrd.img-$(uname -r) $(uname -r)

 (will generate initrd.img-4.4.0-75-generic in arch/x86/boot)

- Now, we can run our kernel:


    qemu -kernel bzImage -initrd initrd.img-4.4.0-75-generic -m 512M [-append "init=/sbin/init"]

### Tips

- How to generate patch file


    diff -Naur linux-4.4.0 linux-4.4.0.new/ > mykernel_for_linux.4.4.0sc.patch

- Steps explains

    [Compiling Linux kernel and running it using QEMU](https://nostillsearching.wordpress.com/2012/09/22/compiling-linux-kernel-and-running-it-using-qemu/) (NOTICE: you'd better download the same version kernel source code which you are using(uanme -r), or you may cause many problems)
