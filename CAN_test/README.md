The CAN_test is a copy of the AT90CAN128 software. for further information got to https://github.com/TheFormulaCruisers/HU3-AT90CAN128 .

### The Atmega32M1 

the Atmega32M1 comes shipped from the factory with the wrong clock settings, 
these need to be changed first before testing the software. Please read the following instructions.

### Changing the Atmega32M1 Clock.
The Atmega32M1 comes factory shipped with an internal 8MHz RC clock and an eight times clock divider. This makes for a very slow and inaccurate clock. The node is equipped with a 16MHz crystal. To make this the system clock some fuses have to be changed.


This tutorial is Atmel Studio 7 and Atmega32M1 specific but should be possible in any Atmel studio version or microcontroller IDE but the menu's could be in different places.

1. Launch Atmel studio.


2. Connect power to the node.


3. Connect the Atmega32M1 via a programmer/debugger.


4. Click Tools in the taskbar up top.


5. Go to "Device programming".


6. At tool, select the programmer/debugger.


7. At device, select the Atmega32M1.


8. At interface, select ISP.


9. Click Apply, there should be a bar with menu's coming up. If not, recheck steps 1-7.


10. At device signature, click read. With the Atmega32M1 device signature should state; 0x1E9584. Target voltage should be about 5,0V. If this doesn't happen there is something wrong.
This could be a number of things;
  *  The node doesn't have power.
  * The ISP header is connected incorrectly.
  * There is a shortcut on the board due to soldering.
  * You should get an error message you can always google!
  
  
11. In the left menu bar, click on Fuses. The top list is a list of all the Fuses laid out in an easy to read way. The bottom list is the same but displayed as the Fuse Registers.


12. Check the state of the Fuse Register. There are 3 possibilities.
Factory default:
* EXTENDED 0xFF
* HIGH 0xD7
* LOW 0x62

Already set to 16MHz external cristal:
* EXTENDED 0xFF
* HIGH 0xD7
* LOW 0xEE 

Settings have been changed before and could be anything.

13. When it has already been set to 16MHz external crystal you can close the device programming and go upload or debug your code.
If the fuses are on Factory default or anything else but the 16MHz external crystal please continue following the steps.


14. At the Fuse Restisters put the value of LOW to 0xEE.


15. Click Program. Please keep Auto read and Verify after programming checked.


16. You should get a popup called Fuse warnings. If it only says SUT_CKSEL click continue. If there are other unintended fuses listed please abort and check the Fuse value's again.


17. If everything worked it should output:
Starting operation verify registers
Verify register EXTENDED...OK \
Verify register HIGH...OK \
Verify register LOW...OK \
Verify registers ... OK \
and the Fuse Register LOW value should be 0xEE. \
(You can get an error popup after clicking continue. It still could have changed. If they haven't changed please try again.)


18. You are now ready to close the device programming and go upload or debug your code.

