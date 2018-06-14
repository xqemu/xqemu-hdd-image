Copyright-Free Xbox HDD Image
=============================

This repository serves as a way to document how to create an Xbox HDD image,
mostly for use with [XQEMU](http://xqemu.com), free of any copyrighted content.

Download
--------
If you're in a hurry, you can [download a pre-built image here](http://fixme).

Do It Yourself
--------------
If you would like to create an image for yourself, containing your own files,
you can follow these instructions. This will involve building a dummy dashboard,
using [XboxHDM](https://www.reddit.com/r/originalxbox/wiki/xboxhdm#wiki_using_xboxhdm)
to create a helper bootable ISO, and a Qemu VM to run the ISO and create the
drive.

You'll want to start by building the dummy dashboard using
[nxdk](https://github.com/xqemu/nxdk). Make sure to update the Makefile with
the path to your nxdk install.

Next you'll want to run the `make-iso-*.sh` script that comes with **XboxHDM
v1.9**. This script will create a bootable ISO image. You can run XboxHDM
natively on Linux or Windows (not tested by me), but I chose to simply run it
inside of a Docker container:

	docker build -t xboxhdm .
	docker run --rm -it -v ${PWD}:/work xboxhdm

Create a working directory:

	mkdir /tmp/xboxhdm
	pushd /tmp/xboxhdm

Unzip XboxHDM:

	unzip /work/xboxhdm_v1.9.zip
	cd xboxhdm

Now copy over the dummy dash and create the empty `TDATA` and `UDATA` folders:

	cp /work/xboxdash.xbe linux/C/
	mkdir -p linux/E/TDATA linux/E/UDATA

Finally, run the tool and copy over the resulting file:

	./make-iso-lin.sh
	cp linux.iso /work

Now we should have a file called "linux.iso" in this directory. You could burn
this to a CD, and boot it on your PC after connecting a real HDD. We aren't
going to do that. Instead, to create a virtual disk image, we will use a virtual
machine: Qemu!

But before we can boot it, we need to create a virtual hard disk. Use `qemu-img`
to create an 8G qcow2 formatted image:

	qemu-img create -f qcow2 xbox.qcow2 8G

Now you have an empty virtual drive. Let's fire up our virtual machine:

	qemu-system-i386 \
		-drive index=0,media=disk,file=xbox.qcow2 \
		-drive index=1,media=cdrom,file=linux.iso

Next follow the on-screen instructions, which basically go as follows:
 - Enter 2 to boot in text mode
 - Type xboxhd at the command prompt to start the helper script
 - Enter 'yes' to confirm
 - Enter 1 to "build a new Xbox HD from scratch"
 - Continue to confirm through the warnings
 - Confirm building a new partition table, formatting partitions, and copying files
 - 8 to quit
 - Type `poweroff` at the command prompt

You should finally have a freshly minted, copyright-free Xbox hard disk image!