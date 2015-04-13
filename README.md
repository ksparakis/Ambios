#AMBIOS
Team 19
Konstantino Sparakis - U47131572
Zach Sarkis - 
--------------
## Project Proposal


###Design:
The overall design is simple, there is a client app that will send color information to the microprocessor in term the microprocessor will change the led strip to the specified colors.
<br />
This client to microprocessor communication will happen over the UART implementing a baud rate of 9600, interrupt handler and communication over the serial port. I will have to create my own communication protocol to send the RGB values to a specific strip.
<br />
The led strip has a very timing strict protocol for sending the RGB values to each individual led. There currently exists a simple driver on github for the MSP430 board but this will only light up a single led strip, and I plan to cut the meter long strip into 6 small strips that can be placed easily onto the monitor in the following positions:
top right corner,
top left corner,
Left side,
right side,
bottom right corner,
and bottom left corner.
<br />
so I will have to create my own driver using a watchdog timer to control all 6 strips separately, following the strict timing requirements of the led strips communication protocol.
<br />
I will also be soldering this system together so that I can use this final project for my personal enjoyment without having to worry about anything getting disconnected.
<br />
<br />

###Stretch Goals:
If I am able to finish with extra time, I would like to implement a client side code that captures a screen image every 60hz, which the refresh rate of most modern monitors, cut the image into pieces retaining to the corners and calculate the average RGB hex value of each piece, then sending the data to the micro controller which will update the led strips. In affect having an automatic full functional Ambient lighting system, but this is my stretch goal.
I would also like to 3D print a box/container for this system to be placed inside permanently with protection.
