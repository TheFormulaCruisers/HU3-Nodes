# Full node code
 The node is a PCB on which the sensors in the car are connected. The nodes are connected to the C3.
The node needs to read the sensors connected to it, process the raw data from the sensors and send the processed data to the C3.
When an error occurs, the node will send an error message to the C3.


## Getting Started

In order to have a working node, we must tested every function individually and have put them all together. 
This includes:
* The CAN_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/CAN_test ).
* The ADC_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/ADC_test )
* The input_Capture_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/Input_Capture_test )


## Built With

* Atmel Studio 7.0 - upload C code.

