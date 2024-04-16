# TAP User-space Application
### 1. Introduction
The user-space application serves as a medium to facilitate the exchange of ethernet frames between different cores on the SoC (R5 and A72 as of now).  
To achieve this, a TAP device is used to read from and write to, the Linux Network Stack.  
Ethernet frames are copied from/to the shared memory region to allow other cores to access it.  
### 2. Installation  
There are two approaches to installing the user-space application on Linux.  
###### A) Compile and Install on EVM  
The first approach is to compile and install on the EVM, described as follows:  
Copy the following project files to the EVM's root file system:  
J7ic.conf    launch_tap.service    Makefile    tapfirmware.c    tapfirmware.h    tapif.c    tapif.sh  
Then, power on the EVM and run the following commands from the directory containing the above files,  
in order to compile on the EVM and install the files on the EVM:  
```shell
    $ touch *
    $ make install
```
Next, run:  
```shell
    $ systemctl enable launch_tap.service
```
to ensure that the systemd service launch_tap.service starts up automatically on boot.  
With this, on the next boot, the user-space application should be running automatically in the background.  
###### B) Cross-Compile for EVM and install on SD-card  
The second approach is to compile on PC for the EVM.  
An SD card is assumed to be used for booting the EVM.  
In the directory containing the following files on the PC:  
J7ic.conf    launch_tap.service    Makefile    tapfirmware.c    tapfirmware.h    tapif.c    tapif.sh  

Run:
```shell
    $ ./setuptools.sh
    $ make CROSS_COMPILE=<aarch64-none-linux-gnu install dir>/bin/aarch64-none-linux-gnu- install DESTDIR=<Path to the root file system on SD card>
```
Here,\<aarch64-none-linux-gnu install dir> is the absolute path where the ARM64 A72 Linux compiler was installed using setuptools.sh.
For example,
if the ARM64 A72 Linux compiler was installed in \<PSDK_RTOS_PATH>/ethfw/apps/tap/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu then the CROSS_COMPILE argument should be set as following
make CROSS_COMPILE=\<PSDK_RTOS_PATH>/ethfw/apps/tap/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu

and \<Path to the root file system on SD card> is the path to the SD card's root file system when mounted on the PC.  
For example,
 if the SD card is mounted at:  
```
    /media/username
```
And the root file system is at:  
```
    /media/username/root
```
Then, for the given example, the command to cross-compile and install would be:  
```shell
    $ make CROSS_COMPILE=aarch64-none-linux-gnu- install DESTDIR=/media/username/root
```
Now, power on the EVM and boot from the SD card.  
Next, run:  
```shell
    $ systemctl enable launch_tap.service
```
to ensure that the systemd service launch_tap.service starts up automatically on boot.  
With this, on the next boot, the user-space application should be running automatically in the background.  
### 3. Debugging
By default, the systemd service: launch_tap.service will run the shell script tapif.sh during boot up.  
However, it is possible to relaunch the application either for testing purposes or in  
case of errors during automatic startup.  
To manually launch the application, navigate to the directory containing the tapif.sh file and the tapif executable.  
Both tapif.sh and tapif should be present in the same directory as per the installation.  
Then, run:  
```shell
    $ bash tapif.sh
```
to run the shell script which shall initialize the TAP device and launch the user-space application.
