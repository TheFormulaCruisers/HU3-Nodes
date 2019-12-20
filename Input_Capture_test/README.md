# Input Capture

Input capture function is used in many applications such as:  
  * Pulse width measurement.  
  * Period measurement.  
  * Capturing the time of an event.


## Getting Started

In order to have a working node, we must first test it.
In this case each function tasked to the nodes are tested individually and afterwards will be used collectively for the overall code.
In this particular test we’re merely measuring the  period length with the input flag capture method, this way we can test the rising or falling edge detection. 


### Prerequisites

This code was made in Atmel Studio 7.0
We're using an ATMEGA32M1

To measure the input we first need an input that generates a pulse. You can use a pulse generator, oscilloscope or in this case an Arduino with a simple code.You require an ISP cable to upload code to the nodes, this takes away the possibility to debug your code. 
Further more there are not enough pins for an LCD display available. 
Luckily we have 4 LED’s which we can work with and monitor the state of our code and nodes.

 
### Installing

Because we are using pin PD4(ICP1A) which is also used for the ISP communication, you must first disconnect the ISP cable before you are able to get any readings from the PD4 pin and vice versa, you must disconnect the input pin before you are able to upload any new codes onto the nodes. Once you have connected the ISP cable, you must also connect your nodes with a 5v power source and a ground. run your code with your programmer(AVR Dragon).

## Running the tests

Initialize the TCCR1A and TCCR1B for proper timer mode (any mode other than 8, 10, 12, 14), to select the edge (Positive or Negative).
Monitor the ICF1A flag in TIFR register to see if edge is arrived. Upon the arrival of the edge, the TCNT1 value is loaded in to ICR1 register automatically by controller.  

Prescalar : we are using a 16MHz  microchip, the timer counter used is  16 bit long. Meaning the clock makes 2^16 = 65536 ticks before overflowing. 16 MHz = 6.25^-8 seconds per tick.
Thus if we set the prescalar to 1, it  takes 65536 * 6.25^-8 = 0.004096 seconds per overflow = 4096 microseconds. Which is more than enough to conduct our tests. Making sure our input pulse does not exceed the amount of time per overflow we can safely test our input capture without the complications with the timer, such as the second edge detection having a smaller value than the first one.

Because we lack an LCD display and are using an ISP cable we can not monitor the exact value of the calculated by our nodes but we are able to freely change and adjust our input pulse length. 
This means that we can add conditions to our code and LED’s.
As soon as the period is longer than 1000 microseconds, turn led1 on.
As soon as the period is longer than 2000 microseconds, turn led2 on.
And so on.
Because we can monitor the value of our input pulse we can adjust to just below and above our condition value and check if the node reacts correctly on our input pulse.



## Built With

* [Atmel Studio 7.0](https://atmel-studio.software.informer.com/7.0/) - upload C code.
 


## Acknowledgement
 Docent : DHr Jesse op den Bouw  
(1) https://www.electronicwings.com/avr-atmega/atmega1632-timer-input-capture-mode  
(2) http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7647-Automotive-Microcontrollers-ATmega16M1-32M1-64M1-32C1-64C1_datasheet.pdf

