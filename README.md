#AMBIOS
Team 19
<br/>
Konstantino Sparakis
<br/>
Zach Sarkis
<br/>
<br/>
<br/>
## Project Final Report
<br/>
<br/>
###Demo
Follow the link for a small video demo:
https://instagram.com/p/2MbthKAfAg/

###Introduction
&#09;We originaly set out to create a full ambient lighting system for computer monitors. An ambient lighting for computer monitor works in the following way oyu analyze the colors of the computer screen, you get the most prominent color and then you send this color to microprocessor that changes led strips to this color. It looks cool and along with this it is actualy scientificly proven to ease the stress of staring at a computer monitor in a dark room. So what we set out to originaly create was a windows application that would take screenshots of the screen, analyze them and send the hex value of the most prominent hex color to the MSP430G2553 microproccesor which in turn would change 6 seperate LED strips to the colors on the screen.
      
<br/>
<br/>
![](http://icdn2.digitaltrends.com/image/antumbra-ambient-light-670x410.jpg)
<br/>
<br/>

<br />
&#09;After many hours working on the client application for windows, to capture live color of the screen and send it to the microprocessor, it became evident that with the amount of time given yes we could have writen an application to send predefined color to a microprocessor and yes we could screenshot the screen and analyze the rgb distibution of pixels, but it would be tremendously slow and mess with the actual computers performance. We found a better away to acomplish this as outlined in this blog: 
      <br />
      <br />
      http://www.floschnell.de/computer-science/super-fast-screen-capture-with-windows-8.html
      <br />
      <br />
      The author uses the DirectX drivers api functions to capture the screen as a data stream and analyze that data stream. This was too complicated and we did not have the time to create a full working solution from scratch. So we opted out to the following.

<br />
<br />
###What is Ambios?
&#09;Ambios is a MSP430 firmware proggram that communicates with Prismatik, through a com port, and controls an led strip and changes its color according to Prismatiks output.Prismatik is an open source software released with the light pack. It brings advance features like selecting the areas of the screen you want to capture, controlling the brightness, and extra features with plugins. Also one the greatest thing about Prismatik is that it is cross plateform and hence works on linux, windows and Mac OSX.
<br />
&#09;As explained in the introduction the act of captruing screen data and analyzing it was complicated and needed a lot of time which we did not have. Since this Prismatik software existed we decided instead of spending so much time creating something from scratch, we should get our MSP430 microprocessor to work along with this open source software Prismatik. And this is what we have accomplished.
<br/>
<br/>
-----------------------------------
###Design
#### Prismatiks Communication Protocol
The MSP4302553 board has the capability to communicate with a computer using its UART over the com port. Prismatik was originally built to soley communicate with Lightpack which is a ambient lighting product. This communication is done as a Human Interfaced Device over the USB so this mode was not compatible but luckily there is a mode made for communicating with an audrino over the com port. We took advantage of this. We set Prismatik up to communicate to com port 3 where the MSP430 board was at a 9600 baud rate. Note a baud rate of 9600 is the MSP430G2553 max speed for the usb UART communication. We used a a tool to sniff all data being sent to the MSP430 board and figured out the communication protocol used by Prismatik looking at patterns and testing the diffrent hex values to see if they represented the right color on the screen.
<br />
Prismatik sends data as characters with the following hex values:
<br/>
<br />
      ```
      FF 00 00 00
      ```
<br />
<br />
FF signals the start of a new line of data.
(00 00 00) represents the (R, G, B) hex values of the color to be displayed on the first strip. Since you are allowed to add as many strips as you want in prismatik the data expands accounting for all the rgb values in order of led strip. In ambios we built our project under the assumption that you are using six led strips, so an example of the data sent to the board with this setup would be:
<br />
<br />
      ```
      FF (00 00 00) (00 00 00) (00 00 00) (00 00 00) (00 00 00) (00 00 00)
      ```
<br />
<br />
Note that we added paranthesis just for visual purposes but Prismatik does not actualy send the data with paranthesis. Each seperate parenthesis represents the RGB value of a seperate LED strip. Also something peculiar we discovered is that it seems that Prismatik never sends FF other than as a new data line so white for example will come in as F7 F7 F7, but this is not 100 perecent confirmed.

####Led Strip Control
So now that we are able to to capture the color of the screen at relatively high speeds of about 18 frames per second with Prismatik and communicate this to the MSP430 Board we need to interpret it and light up the led accordingly. This got a little tricky as the data comes in at one character at a time. We acomplish this using some states and global counting variables reseting when it recieves the new data hex of FF and saving the RGB colors in an array accounting for all 30 LEDs in the strip
<br />
We used the Audafruit NeoPixel Digital LED Strip which comes all connected as 30 LEDs. Unfortuetly the MSP4302553 Board can only support up to 30 LEDs and not the 60 LED version of the Neopixel because of memory restrictions of the array size that can fit on the board. We found that the NeoPixel LED Strip was definetly not the best LED strip for this project, it will sometimes display a random color regardless of what you send it, especialy when updating it at high speeds. Along with this in our case the first LED in the strip broke and just always displayed Green. Possibly at a later date we will update the project to use a diffrent LED strip.
<br />
We originaly planned to cut the 30 LED strip into 6 seperate LED Strips containing 5 LED strips and connecting these to its ouwn output pin on the MSP430 Board. But the NeoPixel has a very strict timming protocol and following it using an output pin turning it on and off accounting for the cycles and the time it takes proved to be unsucessful after much trial and error, getting it to display white but other color on the led strip. We eneded up cutting the one 30 LED strip into 6 seperate LED Strips of 5 LEDS each and sodering and connecting them all in line using 4 pin disconectable plug so that it would be easier to place on a computer monitors back. This lead to the use of only one output pin setup with the high speed communication protocol SPI on the MSP430 board. The NeoPixel communication protocol requires you send 24 bits consisting of RGB vlaues to one LED at a time, since they are linked in series it goes one by one filling up the led strip with colors. Each bit of 0 or 1 has a diffrent time value of High vs Low which the driver on the Neopixel would recognize. Once you have filled up all the LEDs you you need a low signal of 800 Cycles on the MSP430 Board to be sent for the colors to be sent. For more on the timeing protocol look at its data sheet:
<br />
<br />
http://www.adafruit.com/datasheets/WS2812.pdf
<br />
<br />

####Circuit Design
![](https://raw.githubusercontent.com/Giles-ECE-BU/Team19/master/Ambios_circuit.png?token=AEOE92MvGmAnRo9amiHZY28ChQQ0-wkGks5VSY6awA%3D%3D)
<br/>
<br/>
----------------------
### Setup And Instalation
####Step 1: (Buying Supplies)<br/>
Buy all the supplies in the supply list. Also make sure to buy a soldering kit if you do not already have one or you can just use a breadboard.
<br />
<br />
####Step 2: (Making the Circuit)<br/>
We need an external power source of 5v and 2 Amps to power the led strip using the connector in the supply list you can connect this 2.1 mm power supply to a circuit or breadboard. Cut the led strip into 6 pieces each containing 5 LEDS and solder the 4 pin JST plugs all facing the same direction for connectivity. Make sure to use a capacitor between the + and - of the power source.
<br /><br />
####Step 3: (Setting up the MSP430 Board)<br />
In order for the UART usb communication to work you need to turn the black pins horrizontally. Watch this video on how to do that.
<br />
http://instagram.com/p/2C7z2aqT26/
<br />
<br />
####Step 4: (Installation of Firmware)<br />
Install the code onto the msp430 board using code composer which you can download for free on the TI website. Or you can use any other method known to you for installing the code on the board.
<br />
<br />
####Step 5: (Installing and Setting up Prismatik)
<br />
Install Prismatik from this link:
<br/>
http://lightpack.tv/downloads
<br/>
<br/>
On setting up the device within Prismatik make sure to select the ardulight
<br/>
![](https://raw.githubusercontent.com/Giles-ECE-BU/Team19/master/imgs/setup1.png?token=AEOE91ulS3IOs9ycvn9Jkr0kul-EBSTAks5VSZ31wA%3D%3D)
<br/>
<br/>
Then make sure to add the com port which your device is connected in as and the baud rate is 9600
<br />
![](https://raw.githubusercontent.com/Giles-ECE-BU/Team19/master/imgs/setup2.png?token=AEOE960LF_JYCRq13Lwu_OevadhJiQIOks5VSZ5UwA%3D%3D)
<br />
<br />
On setting up the screen make sure to create 6 seperate Boxes to read in data from.
<br />
<br />
####Step 6:
Connect your led strip board, circuit, power supply, computer and msp430 board .... and enjoy the view.
<br />
<br />
----------------------
###Problems
We have discovered there is an issue with the communication after 100 or so packets being sent communication seems to stop between the MSP430 board and windows and the issue seems to be on the windows side. This also doesnt always occur only on certain occasions. Also the Neopixel led as discussed above does not seem to have been the best LED strip for this project but it will make do for now.

###Conclusion
All in all, this project was very challenging and required alot of compromise. In the end we were able to create a working Ambient Lighting system to our delight. Using Prismatik our firmware allows anybody to easily build their own Ambient lighting system using a MSP430 Board that will work on Mac, Windows and Linux!

###Supply List
<br/>

| Quantity        |   Item                                             | Price  |    Web Link                            |
| :-------------: | :------------------------------------------------: | :----: | :------------------------------------: |
|  1              | MSP430G2553                                        | $15.00 | http://www.ti.com/product/msp430g2553  |
| 6               | 4-pin JST SM Plug + Recepacle Cable Set            | $9.00  | http://www.adafruit.com/products/578   |
| 1               | Adafruit Perma-Proto Mint Tin Size BreadBoard      | $5.95  | http://www.adafruit.com/products/723   |
| 1               | Breadboard - friendly 2.1 mm DC barrel jack        | $0.95  | http://www.adafruit.com/products/373   |
| 1               | NeoPixel Digital RGB LED Strip - White 30 LED - 1M | $16.95 | https://www.adafruit.com/products/1376 | 
| 1               | 5V 2A Switching power supply                       | $7.95  | http://www.adafruit.com/product/276    |
| 1               | 1000UF, 35v Capacitor                              | $2.00  |             ~                          |
| 1               | Soldering Wiring set                               | $6.99  |             ~                          |
