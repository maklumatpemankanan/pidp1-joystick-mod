This is a modification of the pidp1 software from oscar vermeulen:<br>
https://github.com/obsolescence/pidp1<br>
this modification adds 2 9-pin-joystick (like from the atari 2600 or c64) to the pidp1 over wifi.<br>
<br>
Its a quick and dirty mod, but it works (2025 11 22)<br>

******************************************

Install joystick-modification <br>

make a new folder in /opt as root<br>

>sudo mkdir /opt/pidp1-joystick<br>

change owner of the directory manually<br>

>sudo chown $USER:$USER /opt/pidp1-joystick

copy all data from your origin pidp1 directory into the new directory,
you can do this in the file browser or in the terminal :<br>
>cp -r /opt/pidp1/* /opt/pidp1-joystick/<br>
<br>
backup the following files :<br>
<br>
>/opt/pidp1-joystick/src/blncolnlights/pdp1/Makefile<br>
>/opt/pidp1-joystick/src/blncolnlights/pdp1/main.c<br>
>/opt/pidp1-joystick/src/blncolnlights/pdp1/pdp1.c<br>
>/opt/pidp1-joystick/src/blncolnlights/pdp1/pdp1.h<br>
>/opt/pidp1-joystick/bin/pdp1control.sh<br>
<br>
copy the new files to the right directorys<br>
the folder structure in the repository is the same like in the destination-folder<br>
<br>
enter the directory on the terminal<br>
>cd /opt/pidp1-joystick/src/blincolnlights/pdp1<br>
<br>
and make the emulator with the new joystick implementation<br>
>make pdp1<br>
<br>
now you can turn on your esp32 and when the esp32 is connected to the pdp1-simulator<br>
and you call iot 15 the bits of the joystick appears in the io register.<br>
<br>
bit 0 = Joystick A up<br>
bit 1 = Joystick A down<br>
bit 2 = Joystick A left<br>
bit 3 = Joystick A right<br>
bit 4 = Joystick A button<br>
<br>
bit 8  = Joystick B up<br>
bit 9  = Joystick B down<br>
bit 10 = Joystick B left<br>
bit 11 = Joystick B right<br>
bit 12 = Joystick B button<br>
<br>
you can start your modded pidp1 simulator from the terminal <br>
>/opt/pidp1-joystick/bin/pdp1control.sh start <br>
<br>
you must call the pdp1control with the full path to start with the modded configuration (in these case with joystick support)<br>
<br>
********************<br>
communication port is 7700<br>
***********************************<br>
<br>
Install the Hardware <br>
<br>
just pick up a esp32 controller, 2 subd-9 male connectors and some cables.<br>
<br>
joystick A<br>
Subd    color   label   gpio<br>
1       purple  up      18<br>
2       grey    down    5<br>
3       white   left    17<br>
4       black   right   16<br>
6       blue    button  19<br>
8       green   vcc     3.3<br>
<br>
joystick B<br>
Subd    color   label   gpio<br>
1       purple  up      25<br>
2       grey    down    26<br>
3       white   left    27<br>
4       black   right   14<br>
6       blue    button  33<br>
8       green   vcc     3.3<br>
<br>
in the arduino-ide in the wifi-joystick.ino you must change the wifi data to connect to your local wifi and set the correct ip address for the ppd1_host (its the computer who runs the pdp1-simulator)<br>
<br>
updload the wifi_joystick.ino to the esp32 and see whats the serial monitor displays.<br>
the esp32 only connects to the pidp1 when the pidp1 is in run-state, the power switch must be ON !<br>
<br>
don't power off the esp32 when the socket is connected with the pidp1 - this freezes the pidp1!<br>
<br>
the joystick_test.ino is for debugging and displays only data in the serial monitor<br>
***********************************<br>
Test Program<br>
***********************************<br>
the program calls the iot 15 to get the value of the joysticks,<br>
you can't see anything in the io-register, because the pidp1 is to fast.<br>
<br>
small program on the pdp1 to test the joystick : program/joy.mac<br>
***********************************<br>
