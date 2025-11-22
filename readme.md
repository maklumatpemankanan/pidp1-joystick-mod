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

bit 0 = Joystick up
bit 1 = Joystick down
bit 2 = Joystick left
bit 3 = Joystick right
bit 4 = Joystick button

********************
on the arduino-ide you must change the wifi data to connect to your local wifi
and set the correct ip address for the ppd1_host (its the computer who runs the pdp1-simulator)

*********************
communication port is 7700

you can start your modded pidp1 simulator from the terminal 
cd /opt/pidp1-joystick/bin/pdp1control.sh start 

you must call the pdp1control with the full path to start with the modded configuration (in these case with joystick support)


***********************************
small program on the pdp1 to test the joystick : joy.mac

joy

/small program to test if the joystick works

10/
go,	cli
	iot 15
	jmp go
	hlt

start 10


