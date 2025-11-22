This is a modification of the pidp1 software from oscar vermeulen:
https://github.com/obsolescence/pidp1
this modification adds 2 9-pin-joystick (linke from the atari 2600 or c64) to the pidp1 over wifi.

Its a quick and dirty mod, but it works (2025 11 22)

******************************************

Install joystick-modification 

make a new folder in /opt as root

sudo mkdir /opt/pidp1-joystick

change owner of the directory manually

sudo chown $USER:$USER /opt/pidp1-joystick

copy all data from your origin pidp1 directory into the new directory,
you can do this in the file browser or in the terminal :
cp -r /opt/pidp1/* /opt/pidp1-joystick/

backup the following files :

/opt/pidp1-joystick/src/blncolnlights/pdp1/Makefile
/opt/pidp1-joystick/src/blncolnlights/pdp1/main.c
/opt/pidp1-joystick/src/blncolnlights/pdp1/pdp1.c
/opt/pidp1-joystick/src/blncolnlights/pdp1/pdp1.h
/opt/pidp1-joystick/bin/pdp1control.sh

copy the new files to the right directorys
the folder structure in the repository is the same like in the destination-folder

enter the directory on the terminal
cd /opt/pidp1-joystick/src/blincolnlights/pdp1

and make the emulator with the new joystick implementation
make pdp1

now you can turn on your esp32 and when the esp32 is connected to the pdp1-simulator
and you call iot 15 the bits of the joystick appears in the io register.

bit 0 = Joystick A up
bit 1 = Joystick A down
bit 2 = Joystick A left
bit 3 = Joystick A right
bit 4 = Joystick A button

bit 8  = Joystick B up
bit 9  = Joystick B down
bit 10 = Joystick B left
bit 11 = Joystick B right
bit 12 = Joystick B button

you can start your modded pidp1 simulator from the terminal 
/opt/pidp1-joystick/bin/pdp1control.sh start 

you must call the pdp1control with the full path to start with the modded configuration (in these case with joystick support)

********************
communication port is 7700

***********************************

Install the Hardware 

just pick up a esp32 controller, 2 subd-9 male connectors and some cables.

joystick A
Subd    color   label   gpio
1       purple  up      18
2       grey    down    5
3       white   left    17
4       black   right   16
6       blue    button  19
8       green   vcc     3.3

joystick B
Subd    color   label   gpio
1       purple  up      25
2       grey    down    26
3       white   left    27
4       black   right   14
6       blue    button  33
8       green   vcc     3.3


in the arduino-ide in the wifi-joystick.ino you must change the wifi data to connect to your local wifi and set the correct ip address for the ppd1_host (its the computer who runs the pdp1-simulator)

updload the wifi_joystick.ino to the esp32 and see whats the serial monitor displays.
the esp32 only connects to the pidp1 when the pidp1 is in run-state, the power switch must be ON !

don't power off the esp32 when the socket is connected with the pidp1 - this freezes the pidp1!

***********************************
Test Program
***********************************
the program calls the iot 15 to get the value of the joysticks,
you can't see anything in the io-register, because the pidp1 is to fast.

small program on the pdp1 to test the joystick : joy.mac
***********************************

joy

/small program to test if the joystick works

10/
go,	cli
	iot 15
	jmp go
	hlt

start 10


