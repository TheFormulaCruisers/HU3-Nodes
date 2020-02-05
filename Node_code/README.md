# Full node code
 The node is a PCB on which the sensors in the car are connected. The nodes are connected to the C3.
The node needs to read the sensors connected to it, process the raw data from the sensors and send the processed data to the C3.
When an error occurs, the node will send an error message to the C3.


## Getting Started

In order to have a working node, we must test every function individually and put them all together. 
This includes:
* The CAN_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/CAN_test ).
* The ADC_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/ADC_test )
* The input_Capture_test ( https://github.com/TheFormulaCruisers/HU3-Nodes/tree/master/Input_Capture_test )


## Instructions

In order to upload the code to the node there are 2 tasks that has to be done for every node before uploading the code. 


* ID.
Each and every Node needs a unique ID. this ID will be used in order to communicate to the C3. The C3 uses this unique ID to give priority to certain nodes. The ID should have a 16 bit value. for further information regarding the CAN-bus and the ID visit 

* Function.
Before uploading your code, the nodes needs to be able to know what functions it is doing and what data to send. Therefor the functions are first defined in this code as 
  * define ADC_Active1.
  * define ADC_Active2.
  * define Input_Capture.

The specification, requirements and the software of the nodes allow a Maximum of 3 ADC functions or a combination of 2 ADC functions and 1 Input capture function per node. So before uploading the code make sure which function/s you are using. you can disable a function by commenting out the defined function ( // define ADC_Active2).

## Additions
in addition to the current code, some nodes require the C3 to send data to the node. this can easily be added to the code with the Addition of a function. The CAN headers have already functions ready for data transmission to and from the C3.

## Detailed description
For the detailed description visit https://betafactory.atlassian.net/wiki/spaces/FCHU3/pages/1503363671/7.3.2.6+WOC+-+Nodes for the code flow. further more the code has been commented for a step by step walkthrough.

## Built With

* Atmel Studio 7.0 - upload C code.

