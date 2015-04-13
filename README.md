#AMBIOS
Team 19
<br/>
Konstantino Sparakis - U47131572
<br/>
Zach Sarkis - U
<br/>
<br/>
<br/>
## Project Proposal
<br/>
<br/>
###What is Ambios?
We want to create an Ambient Lighting System for a computer monitor. A basic summary of what an Ambient lighting system is, is that it captures the average HEX color at each corner of a display as the display colors change, it then lights up an led behind the monitor with that color, making it a lot less stressful for our eyes to look at a bright monitor in the dark, as well as just simply looking cool. Although this maybe costly, it puts our microprocessor to use into something we will be using for our personal enjoyment for many years to come.
<br/>
<br/>
![](http://icdn2.digitaltrends.com/image/antumbra-ambient-light-670x410.jpg)
<br/>
<br/>
###Design:
The overall design is simple, there is a client app that will send color information to the microprocessor in term the microprocessor will change the led strip to the specified colors.
<br />
This client to microprocessor communication will happen over the UART implementing a baud rate of 9600, interrupt handler and communication over the serial port. We will have to create our own communication protocol to send the RGB values to a specific strip.
<br />
The led strip has a very timing strict protocol for sending the RGB values to each individual led. There currently exists a simple driver on github for the MSP430 board but this will only light up a single led strip, and I plan to cut the meter long strip into 6 small strips that can be placed easily onto the monitor in the following positions:
<br/>
top right corner,<br/>
top left corner,<br/>
Left side,<br/>
right side,<br/>
bottom right corner,<br/>
and bottom left corner.<br/>
<br />
so we will have to create our own driver using a watchdog timer to control all 6 strips separately, following the strict timing requirements of the led strips communication protocol.
<br />
We will also be soldering this system together so that we can use this final project for our personal enjoyment without having to worry about anything getting disconnected.
<br />
<br />
###Stretch Goals:
If we are able to finish with extra time, we would like to implement a client side code that captures a screen image every 60hz, which the refresh rate of most modern monitors, cut the image into pieces retaining to the corners and calculate the average RGB hex value of each piece, then sending the data to the micro controller which will update the led strips. In affect having an automatic full functional Ambient lighting system, but this is our stretch goal.
We would also like to 3D print a box/container for this system to be placed inside permanently with protection.
<br/>
<br/>
Supply List:
| Quantity  | Item |  Price   | Web Link |
| ------------- | ------------- | ---------- | --------- |
|  1 | MSP430G2553 | $15.00 | http://www.ti.com/product/msp430g2553 |
| 6 | 4-pin JST SM Plug + Recepacle Cable Set | $9.00 | http://www.adafruit.com/products/578 |
| 1 | Adafruit Perma-Proto Mint Tin Size BreadBoard | $5.95 | http://www.adafruit.com/products/723 |
| 1 | Breadboard - friendly 2.1 mm DC barrel jack | $0.95 | http://www.adafruit.com/products/373 |
| 1 | NeoPixel Digital RGB LED Strip - White 30 LED - 1M | $16.95 | https://www.adafruit.com/products/1376 | 
| 1 | 5V 2A Switching power supply | $7.95 | http://www.adafruit.com/product/276 |
| 1 | 1000UF, 35v Capacitor | $2.00 | http://www.radioshack.com/nte-vht1000m35-cap-1000uf-35v-105*c-radial-lead/55047747.html |
| 1 | Soldering Wiring set | $6.99 | http://www.radioshack.com/solderless-breadboard-jumper-wire-kit/2760173.html#q=jumper%2Bwires&start=10 |
